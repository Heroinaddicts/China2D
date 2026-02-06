#ifndef __IRenderer_h__
#define __IRenderer_h__

#include "MultiSys.h"
#include "Structs.h"

namespace China2D {
	namespace Api {
        class IWindow;
		class ITexture;
        class IRenderMesh;

        class IRenderer {
        public:
            virtual ~IRenderer() {}

            virtual void BeginRender(IWindow* window) = 0;
            virtual void DrawTexture(ITexture* texture, const RectF& rect, const Color4& color) = 0;
            virtual void DrawMesh(IRenderMesh* mesh, const Matrix4x4& transform) = 0;
            virtual void EndRender() = 0;
        };
	}
}

#endif //__IRenderer_h__
