#ifndef __IRenderer_h__
#define __IRenderer_h__

#include "MultiSys.h"
#include "Vector2.h"
#include "Vector3.h"

namespace China2D {
	namespace Api {
        class IRenderer {
        public:
            virtual ~IRenderer() {}

            virtual Size GetSize() const = 0;
            virtual void SetSize(const Size& size) = 0;
            virtual bool ShouldClose() const = 0;
            virtual void SetTitle(const std::string& title) = 0;
            virtual void* GetNativeHandle() const = 0;
        };
	}
}

#endif //__IRenderer_h__
