#ifndef __Renderer_h__
#define __Renderer_h__

#include "IRenderer.h"

namespace China2D {
	class Renderer : public Api::IRenderer {
	public:
		virtual ~Renderer() {}

        void Initialize();

		void BeginRender(Api::IWindow* window) override;
		void DrawTexture(Api::ITexture* texture, const RectF& rect, const Color4& color) override;
		void DrawMesh(Api::IRenderMesh* mesh, const Matrix4x4& transform) override;
		void EndRender() override;
	};
}

#endif //__Renderer_h__
