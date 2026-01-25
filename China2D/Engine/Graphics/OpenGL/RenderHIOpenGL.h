#ifndef __RenderHIOpenGL_h__
#define __RenderHIOpenGL_h__

#include "IRenderHIPlatform.h"

namespace China2D {
	class RenderHIOpenGL : public IRenderHIPlatform {
	public:
		virtual ~RenderHIOpenGL() {}

		RenderHIOpenGL(const unsigned int id, const std::string& name) : _ID(id), _Name(name) {}

		bool Initialize() override;
		void Shutdown() override;

		Api::eRHI GetBackend() const override;
		Api::IRHISurface* CreateSurface(Api::IWindow* window, const std::string& name) override;
		Api::IRenderMesh* CreateRenderMesh(const std::string& name) override;
		Api::ITexture* CreateTexture(const std::string& name) override;
		Api::IShader* CreateShader(const std::string& name) override;

		void Begin(Api::IRHISurface* surface) override;
		void End(Api::IRHISurface* surface) override;
	private:
		const unsigned int _ID;
		const std::string _Name;
	};
}

#endif //__RenderHIOpenGL_h__
