#ifndef __IWindow_h__
#define __IWindow_h__

#include "MultiSys.h"
#include "Vector2.h"
#include "Vector3.h"

namespace China2D {
    namespace Api {
        class IWindow {
        public:
            virtual ~IWindow() {}

            virtual Size GetSize() const = 0;
            virtual void SetSize(const Size& size) = 0;
            virtual bool ShouldClose() const = 0;
            virtual void SetTitle(const std::string& title) = 0;
            virtual void* GetNativeHandle() const = 0;
            virtual void Show() = 0;
            virtual void Destroy() = 0;
        };
    }
}

#endif //__IWindow_h__
