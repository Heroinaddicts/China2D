#ifndef __XBuffer_h__
#define __XBuffer_h__

#include "SafeMemory.h"
#include "XLock.h"
#include <functional>
#include <atomic>
#include <thread>
#include <cassert>

namespace China2D {

    typedef std::function<int(const void* const data, const int size)> fXBuffReadCallback;

    class IBuffer {
    public:
        virtual ~IBuffer() {}

        virtual bool Read(const fXBuffReadCallback& callback) = 0;
        virtual void Write(const void* const data, const int len, const char* file, const int line) = 0;
        virtual void Clear() = 0;

        virtual const char* GetData() const = 0;
        virtual int GetDataSize() const = 0;
    };

    class XBuffer : public IBuffer {
    public:
        virtual ~XBuffer() {
            txfree(_Buff);
        }

        XBuffer(const int size, const int capacity)
            : _Size(size),
            _Capacity(capacity),
            _ReadIndex(0),
            _WriteIndex(0),
            _Readers(0),
            _Reallocing(false),
            _Version(0),
            _Writing(false),
            _Clearing(false)
        {
            _Buff = (char*)txmalloc(size);
        }

        __forceinline bool Read(const fXBuffReadCallback& callback) override {
            for (;;) {
                while (_Reallocing.load(std::memory_order_acquire) || _Clearing.load(std::memory_order_acquire)) {
                    std::this_thread::yield();
                }

                int version = _Version.load(std::memory_order_acquire);
                char* buf = _Buff.load(std::memory_order_acquire);

                int read = _ReadIndex.load(std::memory_order_relaxed);
                int write = _WriteIndex.load(std::memory_order_acquire);

                if (write <= read) {
                    return false;
                }

                int avail = write - read;

                _Readers.fetch_add(1, std::memory_order_acquire);

                if (version != _Version.load(std::memory_order_acquire)) {
                    _Readers.fetch_sub(1, std::memory_order_release);
                    continue;
                }

                int used = callback(buf + read, avail);
                XASSERT(used <= avail, "wtf");
                if (used == 0) {
                    _Readers.fetch_sub(1, std::memory_order_release);
                    return false;
                }

                int expected = read;
                bool ok = _ReadIndex.compare_exchange_strong(expected, read + used,
                    std::memory_order_release,
                    std::memory_order_relaxed);
                _Readers.fetch_sub(1, std::memory_order_release);

                if (ok) {
                    return true;
                }
                else {
                    // CAS 失败（可能 Clear/ReadOut 干预），重试整体流程
                    continue;
                }
            }
        }

        __forceinline void Write(const void* const data, const int len, const char* file, const int line) override {
            _Writing.store(true, std::memory_order_release);

            while (_Clearing.load(std::memory_order_acquire)) {
                std::this_thread::yield();
            }

            int write = _WriteIndex.load(std::memory_order_relaxed);
            int read = _ReadIndex.load(std::memory_order_acquire);
            int curSize = _Size.load(std::memory_order_acquire);
            int dataSize = write - read;

            int tail = 0;
            if (write < curSize) {
                tail = curSize - write;
            }
            else {
                tail = 0;
            }

            if (tail < len) {
                AUTO_LOCK(_Lock);
                write = _WriteIndex.load(std::memory_order_relaxed);
                read = _ReadIndex.load(std::memory_order_acquire);
                dataSize = write - read;
                curSize = _Size.load(std::memory_order_acquire);

                if (write < curSize) {
                    tail = curSize - write;
                }
                else {
                    tail = 0;
                }

                if (tail < len) {
                    _Reallocing.store(true, std::memory_order_release);

                    while (_Readers.load(std::memory_order_acquire) != 0) {
                        std::this_thread::yield();
                    }

                    write = _WriteIndex.load(std::memory_order_relaxed);
                    read = _ReadIndex.load(std::memory_order_relaxed);
                    dataSize = write - read;
                    curSize = _Size.load(std::memory_order_acquire);

                    if (curSize - dataSize < len) {
                        char* oldBuff = _Buff.load(std::memory_order_acquire);
                        int newSize = curSize;
                        do {
                            newSize += _Capacity;
                        } while (newSize - dataSize < len);

                        char* newBuff = (char*)txmalloc(newSize);
                        if (newBuff == nullptr) {
                            _Reallocing.store(false, std::memory_order_release);
                            _Writing.store(false, std::memory_order_release);
                            XASSERT(false && "txmalloc failed in XBuffer::Write", "txmalloc failed");
                            return;
                        }

                        if (dataSize > 0) {
                            SafeMemory::Memcpy(newBuff, newSize, oldBuff + read, dataSize);
                        }

                        _ReadIndex.store(0, std::memory_order_relaxed);
                        _WriteIndex.store(dataSize, std::memory_order_relaxed);

                        _Buff.store(newBuff, std::memory_order_release);
                        _Size.store(newSize, std::memory_order_release);

                        _Version.fetch_add(1, std::memory_order_release);

                        if (oldBuff != _Buff) {
                            txfree(oldBuff);
                        }
                    }
                    else {
                        char* buff = _Buff.load(std::memory_order_acquire);
                        if (dataSize > 0) {
                            SafeMemory::Memmove(buff, curSize, buff + read, dataSize);
                        }
                        _ReadIndex.store(0, std::memory_order_relaxed);
                        _WriteIndex.store(dataSize, std::memory_order_relaxed);
                        _Version.fetch_add(1, std::memory_order_release);
                    }

                    _Reallocing.store(false, std::memory_order_release);
                }
            }

            write = _WriteIndex.load(std::memory_order_relaxed);
            read = _ReadIndex.load(std::memory_order_acquire);
            curSize = _Size.load(std::memory_order_acquire);

            if (write + len > curSize) {
                AUTO_LOCK(_Lock);
                write = _WriteIndex.load(std::memory_order_relaxed);
                read = _ReadIndex.load(std::memory_order_relaxed);
                dataSize = write - read;
                int newSize = curSize;
                do { newSize += _Capacity; } while (newSize - dataSize < len);

                char* oldBuff2 = _Buff.load(std::memory_order_acquire);
                char* newBuff2 = (char*)txmalloc(newSize);
                if (newBuff2 == nullptr) {
                    _Writing.store(false, std::memory_order_release);
                    XASSERT(false && "txmalloc failed in XBuffer::Write fallback", "txmalloc failed");
                    return;
                }
                if (dataSize > 0) {
                    SafeMemory::Memcpy(newBuff2, newSize, oldBuff2 + read, dataSize);
                }
                _ReadIndex.store(0, std::memory_order_relaxed);
                _WriteIndex.store(dataSize, std::memory_order_relaxed);
                _Buff.store(newBuff2, std::memory_order_release);
                _Size.store(newSize, std::memory_order_release);
                _Version.fetch_add(1, std::memory_order_release);
                if (oldBuff2 != _Buff) txfree(oldBuff2);

                write = _WriteIndex.load(std::memory_order_relaxed);
                curSize = _Size.load(std::memory_order_acquire);
            }

            char* buffNow = _Buff.load(std::memory_order_acquire);
            XASSERT(write + len <= curSize, "XBuffer Write would overflow buffer");
            SafeMemory::Memcpy(buffNow + write, curSize - write, data, len);
            _WriteIndex.store(write + len, std::memory_order_release);
            _Writing.store(false, std::memory_order_release);
        }

        __forceinline void ReadOut(const int len) {
            for (;;) {
                int read = _ReadIndex.load(std::memory_order_relaxed);
                int write = _WriteIndex.load(std::memory_order_acquire);
                int newRead = read + len;
                int avail = write - read;
                XASSERT(newRead <= write, "ReadOut overflow: trying to advance past write index");
                XASSERT(len <= avail, "ReadOut len exceeds available space (avail=%d, len=%d)", avail, len);
                if (_ReadIndex.compare_exchange_weak(read, newRead,
                    std::memory_order_release,
                    std::memory_order_relaxed)) {
                    return;
                }
                // CAS 失败则重试
            }
        }

        __forceinline void Clear() override {
            _Clearing.store(true, std::memory_order_release);
            while (_Writing.load(std::memory_order_acquire) || _Reallocing.load(std::memory_order_acquire) || _Readers.load(std::memory_order_acquire) != 0) {
                std::this_thread::yield();
            }

            _ReadIndex.store(0, std::memory_order_release);
            _WriteIndex.store(0, std::memory_order_release);
            _Version.fetch_add(1, std::memory_order_release);
            _Clearing.store(false, std::memory_order_release);
        }

        __forceinline const char* GetData() const override {
            for (;;) {
                int version = _Version.load(std::memory_order_acquire);
                char* buf = _Buff.load(std::memory_order_acquire);
                int read = _ReadIndex.load(std::memory_order_relaxed);
                if (version == _Version.load(std::memory_order_acquire)) {
                    return buf + read;
                }
                // 自旋重试
            }
        }

        __forceinline int GetDataSize() const override {
            for (;;) {
                int version = _Version.load(std::memory_order_acquire);
                int write = _WriteIndex.load(std::memory_order_acquire);
                int read = _ReadIndex.load(std::memory_order_relaxed);
                if (version == _Version.load(std::memory_order_acquire)) {
                    return write - read;
                }
            }
        }

    private:
        __forceinline int GetFreeSize() {
            int write = _WriteIndex.load(std::memory_order_relaxed);
            int read = _ReadIndex.load(std::memory_order_acquire);
            int curSize = _Size.load(std::memory_order_acquire);
            return curSize - (write - read);
        }

        __forceinline int GetTailSize() {
            int write = _WriteIndex.load(std::memory_order_relaxed);
            int curSize = _Size.load(std::memory_order_acquire);
            if (write < curSize) return curSize - write;
            return 0;
        }

    private:
        std::atomic<char*> _Buff;   // 当前有效缓冲地址

        std::atomic<int> _Size;      // 缓冲容量（原子，扩容写后对读可见）
        const int _Capacity;
        SpinLock _Lock;

        std::atomic<int> _ReadIndex;   // 绝对索引（单读线程写）
        std::atomic<int> _WriteIndex;  // 绝对索引（单写线程写）

        // 协调扩容与读者的变量
        std::atomic<int> _Readers;     // 当前正在 callback 的读者计数
        std::atomic<bool>  _Reallocing;   // 标志：正在搬移/扩容（阻止新读进入）
        std::atomic<int> _Version;     // 缓冲版本号，扩容/搬移/clear 后 +1

        // 新增：协调 Write 与 Clear 的标志（写入期间拒绝 Clear）
        std::atomic<bool> _Writing;       // 标志：写线程正在执行 Write（防止 Clear 并发）
        std::atomic<bool> _Clearing;      // 标志：正在执行 Clear（阻止读写进入）
    };
}

#endif //__XBuffer_h__
