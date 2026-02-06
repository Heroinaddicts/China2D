#ifndef __China2DApi_h__
#define __China2DApi_h__

#include "MultiSys.h"
#include "Structs.h"
#include "IModule.h"
#include "IWindow.h"
#include "IRenderer.h"
#include "IResourceManagerApi.h"
#include "ITaskManagerApi.h"

#include "SafeString.h"

namespace China2D {
	namespace Api {
		class IEngine {
		public:
			virtual ~IEngine() {}

			// 引擎初始化
			virtual const char* GetLaunchParameter(const std::string& name) const = 0;

			__forceinline int GetLaunchParameterInt32(const std::string& name) const {
				const char* value = GetLaunchParameter(name);
				if (!value) {
					return 0;
				}
				return SafeString::StringToInt32(value);
			}

			virtual bool Initialize() = 0;
			virtual void Shutdown() = 0;

			virtual IWindow* CreateWindow(const std::string& title, int width, int height) = 0;
			virtual IRenderer* GetRenderer2D() = 0;

			virtual IResourceManagerApi* GetResourceManagerApi() = 0;

			virtual void SetMinLogLevel(const unsigned int level) = 0;
			virtual unsigned int GetMinLogLevel() = 0;

			virtual void LogAsync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) = 0;
			virtual void LogSync(const unsigned int level, const char* header, const char* content, const bool console, const char* file, const int line) = 0;
		};

		__forceinline void __Log__(Api::IEngine* engine, const int level, const char* tag, const bool sync, const char* file, int line, const char* format, ...) {
			if (level < engine->GetMinLogLevel()) {
				return;
			}

			va_list args;
			va_start(args, format);
			va_list args_copy;
			va_copy(args_copy, args);

			int len = vsnprintf(nullptr, 0, format, args_copy);
			va_end(args_copy);

			if (len <= 0) {
				va_end(args);
				return;
			}

			char* log = (char*)txmalloc(len + 1);
			if (!log) {
				va_end(args);
				return;
			}

			vsnprintf(log, len + 1, format, args);
			va_end(args);

			sync ? engine->LogSync(level, tag, log, true, file, line) : engine->LogAsync(level, tag, log, true, file, line);
			txfree(log);
		}
	}
}

enum eLogLevel {
	Error = 10000,
	Trace = 1,
	Debug = 0
};

#define DebugLog(engine, format, ...) China2D::Api::__Log__(engine, eLogLevel::Debug, "Debug", false, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define TraceLog(engine, format, ...) China2D::Api::__Log__(engine, eLogLevel::Trace, "Trace", false, __FILE__, __LINE__, format, ##__VA_ARGS__)
#define ErrorLog(engine, format, ...) {China2D::Api::__Log__(engine, eLogLevel::Error, "Error", true, __FILE__, __LINE__, format, ##__VA_ARGS__); XASSERT(false, format, ##__VA_ARGS__);}


#endif //__China2DApi_h__
