#ifndef __Window_h__
#define __Window_h__

#include "China2DApi.h"

namespace China2D {
	class Window : public Api::IWindow {
	public:
		virtual ~Window() {}

		Size GetSize() const override;
		void SetSize(const Size& size) override;
		bool ShouldClose() const override;
		void SetTitle(const std::string& title) override;
		void* GetNativeHandle() const override;
		void Show() override;
		void Destroy() override;
	};
}

#endif //__Window_h__
