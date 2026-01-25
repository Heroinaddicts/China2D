#ifndef __Log_h__
#define __Log_h__

#include "Header.h"

namespace China2D {
    class Log : public ILog, public SafeThread {
    public:
        virtual ~Log() {}

        static Log* GetInstance();

        // 通过 iLog 继承
        bool Initialize(Engine* const engine) override;
        bool Launch(Engine* const engine) override;
        void Release(Engine* const engine) override;

        void EarlyUpdate(Engine* const engine) override;
        void Update(Engine* const engine) override;
        void LaterUpdate(Engine* const engine) override;

		void FixedUpdate(Engine* const engine) override;

        __forceinline void SetMinLogLevel(const unsigned int level) override {
            _MinLogLevel = level;
        }

        __forceinline unsigned int GetMinLogLevel() const override {
            return _MinLogLevel;
        }

        void LogAsync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) override;
        void LogSync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) override;

        // 通过 SafeThread 继承
        void Run(void* context) override;

    private:
        XPool<LogContent> _LogContentPool;
        SafeQueue::SpscQueue<LogContent*> _LogContentQueue;
        SafeQueue::SpscQueue<LogContent*> _LogContentReleaseQueue;

        std::string _SyncLogFilePath;
        XFile _SyncLogFile;
        SpinLock _SycnLogLock;

        std::string _AsyncLogFilePath;
        XFile _AsyncLogFile;
        SpinLock _AsyncLogLock;

        unsigned int _MinLogLevel = eLogLevel::Debug;
    };
}

#endif //__Log_h__
