#include "Log.h"
#include "Engine.h"
#include "SafeSystem.h"

namespace China2D {
    RegistEngineComponent(Log);

    Log* Log::GetInstance() {
        static Log s_Instance;
        return &s_Instance;
    }
    bool Log::Initialize(Engine* const engine) {
        std::string path = SafeSystem::File::GetDirectoryOfCurrentExe();
        const char* logpath = engine->GetLaunchParameter("log");
        if (logpath) {
            path += "/" + std::string(logpath);
        }

        if (!SafeSystem::File::FolderExists(path)) {
            SafeSystem::File::CreateFolder(path);
        }

        _SyncLogFilePath = path + "/" + g_Engine->GetName() + "-sync-" + SafeString::Int64ToString(SafeSystem::Process::GetCurrentProcessID()) + ".log";
        _AsyncLogFilePath = path + "/" + g_Engine->GetName() + "-async-" + SafeString::Int64ToString(SafeSystem::Process::GetCurrentProcessID()) + ".log";

        if (!_SyncLogFile.Open(_SyncLogFilePath)) {
            return false;
        }

        if (!_AsyncLogFile.Open(_AsyncLogFilePath)) {
            return false;
        }

        Start();
        return true;
    }

    bool Log::Launch(Engine* const engine) {
        return true;
    }

    void Log::Release(Engine* const engine) {
    }

    void Log::EarlyUpdate(Engine* const engine) {
    }

    void Log::Update(Engine* const engine) {
    }

    void Log::LaterUpdate(Engine* const engine) {
        LogContent* lc = nullptr;
        UInt64 tick = SafeSystem::Time::GetMicroSecond();
        AUTO_LOCK(_AsyncLogLock);
        while (_LogContentReleaseQueue.Pull(lc)) {
            XPOOL_RELEASE(_LogContentPool, lc);
            if (SafeSystem::Time::GetMicroSecond() - tick > 1000) {
                break;
            }
        }
    }

    void Log::FixedUpdate(Engine* const engine) {

    }

    void Log::LogAsync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) {
        if (level < _MinLogLevel) {
            return;
        }

        AUTO_LOCK(_AsyncLogLock);
        LogContent* lc = XPOOL_CREATE(_LogContentPool, header, content, console, file, line, SafeSystem::Time::GetMilliSecond());
        _LogContentQueue.Push(lc);
    }

    void Log::LogSync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) {
		if (level < _MinLogLevel) {
			return;
		}

        UInt64 tick = SafeSystem::Time::GetMilliSecond();
        AUTO_LOCK(_SycnLogLock);
        std::string log = SafeSystem::Time::GetTimeStringByMillisecond(tick)
            + " " + header
            + " " + file
            + ":" + SafeString::Int64ToString(line)
            + " >> " + content + "\n";

        _SyncLogFile << log;
        _SyncLogFile.Save();
        if (console) {
            printf("%s", log.c_str());
        }
    }

    void Log::Run(void* context) {
        int count = 0;
        UInt64 tick = SafeSystem::Time::GetMilliSecond();
        while (!IsClose()) {
            LogContent* lc = nullptr;
            if (_LogContentQueue.Pull(lc)) {
                std::string content = SafeSystem::Time::GetTimeStringByMillisecond(lc->_Tick)
                    + " " + lc->_Head
                    + " " + lc->_File
                    + ":" + SafeString::Int64ToString(lc->_Line)
                    + " >> " + lc->_Content + "\n";
                _LogContentReleaseQueue.Push(lc);

                _AsyncLogFile << content;
                count++;
                if (lc->_Console) {
                    printf("%s", content.c_str());
                }
            }
            else {
                count = 0;
                SafeSystem::Time::MillisecondSleep(2);
            }

            UInt64 tick2 = SafeSystem::Time::GetMilliSecond();
            if (count > 0) {
                if (count >= 50 || tick2 - tick >= 50) {
                    _AsyncLogFile.Save();
                    tick = tick2;
                    count = 0;
                }
            }
        }
    }
}
