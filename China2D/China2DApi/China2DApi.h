#ifndef __China2DApi_h__
#define __China2DApi_h__

#include "MultiSys.h"
#include "Vector2.h"
#include "Vector3.h"

namespace China2D {
	namespace Api {
		class IRR {
		public:
			virtual ~IRR() {}
			IRR(const unsigned int id, const std::string& name) : _ID(id), _Name(name) {}

			const unsigned int _ID;
			const std::string _Name;
		};

		class IVertexBuffer : public IRR {
		public:
			virtual ~IVertexBuffer() {}
		};

		class IIndexBuffer : public IRR {
		public:
			virtual ~IIndexBuffer() {}
		};

		class IRenderMesh : public IRR {
		public:
			virtual ~IRenderMesh() {}

			virtual void SetVertexData(const void* data, size_t size) = 0;
			virtual void SetIndexData(const void* data, size_t size) = 0;

			virtual IVertexBuffer* GetVertexBuffer() = 0;
			virtual IIndexBuffer* GetIndexBuffer() = 0;
		};

		class ITexture : public IRR {
		public:
			virtual ~ITexture() {}
		};

		class IShader : public IRR {
		public:
			virtual ~IShader() {}
		};


		class IWindow {
		public:
			virtual ~IWindow() {}
			virtual Size GetSize() const = 0;
			virtual void Resize(const Size& size) = 0;

// 			virtual IRenderMesh* CreateRenderMesh() = 0;
// 			virtual IIndexBuffer* CreateIndexBuffer() = 0;
// 			virtual ITexture* CreateTexture() = 0;
// 			virtual IShader* CreateShader() = 0;

			virtual void Destroy() = 0;
		};

		class IRenderHI {
		public:
			virtual ~IRenderHI() {}

			virtual bool Initialize() = 0;
			virtual bool Launch() = 0;
			virtual void Shutdown() = 0;

			virtual void SwapBuffers() = 0;
			virtual void Clear() = 0;

			virtual IWindow* CreateWindow(const int width, const int heigh, const std::string& name = "China2D") = 0;
		};

		class IEngine {
		public:
			virtual ~IEngine() {}

			virtual IRenderHI* GetRenderHI() = 0;

			virtual const char* GetLaunchParameter(const std::string& name) const = 0;

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
