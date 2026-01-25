#include "RenderHIOpenGL.h"

namespace China2D {
	bool RenderHIOpenGL::Initialize() {
		return true;
	}

	Api::eRHI RenderHIOpenGL::GetBackend() const {
		return Api::eRHI();
	}

	void RenderHIOpenGL::Shutdown() {
	}

	Api::IRHISurface* RenderHIOpenGL::CreateSurface(Api::IWindow* window, const std::string& name) {
		return nullptr;
	}

	Api::IRenderMesh* RenderHIOpenGL::CreateRenderMesh(const std::string& name) {
		return nullptr;
	}

	Api::ITexture* RenderHIOpenGL::CreateTexture(const std::string& name) {
		return nullptr;
	}

	Api::IShader* RenderHIOpenGL::CreateShader(const std::string& name) {
		return nullptr;
	}

	void RenderHIOpenGL::Begin(Api::IRHISurface* surface) {
	}

	void RenderHIOpenGL::End(Api::IRHISurface* surface) {
	}
}
