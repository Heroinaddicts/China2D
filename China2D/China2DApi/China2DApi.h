#ifndef __China2DApi_h__
#define __China2DApi_h__

#include "MultiSys.h"
#include "Vector2.h"
#include "Vector3.h"

namespace China2D {
	namespace Api {
		enum class eIRRType {
			Surface,
			Mesh,
			Texture,
			Shader,
			VB,
			IB
		};

		class IRR {
		public:
			virtual ~IRR() {}
			IRR(const uint32_t id, const std::string& name) : _ID(id), _Name(name) {}

			virtual eIRRType GetRRType() const = 0;
			virtual void Destroy() = 0;

			const uint32_t _ID;
			const std::string _Name;
		};

		class IWindow : public IRR {
		public:
			virtual ~IWindow() {}

			virtual void PollEvents() = 0;
			virtual bool ShouldClose() const = 0;

			virtual Size GetSize() const = 0;
			virtual void Resize(const Size& size) = 0;

			virtual void* GetNativeHandle() const = 0;

		};

		class IRHISurface : public IRR {
		public:
			virtual ~IRHISurface() {}

			virtual IWindow* GetWindow() const = 0;

			virtual Size GetSize() const = 0;
			virtual void Resize(const Size& size) = 0;

			virtual void Clear() = 0;
			virtual void Present() = 0;

			virtual void Destroy() = 0;
		};

		class IVertexBuffer : public IRR {
		public:
			virtual ~IVertexBuffer() {}
			virtual void SetData(const void* data, size_t size) = 0;
		};

		class IIndexBuffer : public IRR {
		public:
			virtual ~IIndexBuffer() {}
			virtual void SetData(const void* data, size_t size) = 0;
		};

		class ITexture : public IRR {
		public:
			virtual ~ITexture() {}
		};

		class IShader : public IRR {
		public:
			virtual ~IShader() {}
		};

		class IRenderMesh : public IRR {
		public:
			virtual ~IRenderMesh() {}

			virtual void SetVertexData(const void* data, size_t size) = 0;
			virtual void SetIndexData(const void* data, size_t size) = 0;

			virtual IVertexBuffer* GetVertexBuffer() = 0;
			virtual IIndexBuffer* GetIndexBuffer() = 0;
		};

		enum class eRHI {
			OpenGL = 0,
			DirectX,
			Vulkan,
			Metal
		};

		class IRenderHI {
		public:
			virtual ~IRenderHI() {}

			virtual eRHI GetBackend() const = 0;

			virtual IRHISurface* CreateSurface(IWindow* window, const std::string& name) = 0;

			virtual IRenderMesh* CreateRenderMesh(const std::string& name) = 0;
			virtual ITexture* CreateTexture(const std::string& name) = 0;
			virtual IShader* CreateShader(const std::string& name) = 0;

			virtual void Begin(IRHISurface* surface) = 0;
			virtual void End(IRHISurface* surface) = 0;
		};

		enum class ePlatform {
			GLFW = 0,
			Android = 1,
			IOS = 2
		};

		class IPlatform {
		public:
			virtual ~IPlatform() {}

			virtual IWindow* CreateWindow(int w, int h, const std::string& title) = 0;
		};

		struct EngineDesc {
			eRHI RHI = eRHI::OpenGL;
			ePlatform Platform = ePlatform::GLFW;
		};

		class IEngine {
		public:
			virtual ~IEngine() {}

			virtual void SetEngineDesc(const EngineDesc& desc) = 0;
			virtual void Shutdown() = 0;

			virtual IPlatform* GetPlatform() const = 0;

			virtual IRenderHI* GetRenderHI() const = 0;
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
