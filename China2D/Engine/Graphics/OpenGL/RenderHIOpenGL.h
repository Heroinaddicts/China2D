#ifndef __RenderHIOpenGL_h__
#define __RenderHIOpenGL_h__

#include "China2DApi.h"

namespace China2D {
	class RenderHIOpenGL : public Api::IRenderHI {
	public:
		virtual ~RenderHIOpenGL() {}

		// Í¨¹ý IRenderHIOpenGL ¼Ì³Ð
		bool Initialize() override;
		bool Launch() override;
		void Shutdown() override;
		void SwapBuffers() override;
		void Clear() override;

// 		Api::IRenderMesh* CreateRenderMesh() override;
// 		Api::IIndexBuffer* CreateIndexBuffer() override;
// 		Api::ITexture* CreateTexture() override;
// 		Api::IShader* CreateShader() override;
	};
}

#endif //__RenderHIOpenGL_h__
