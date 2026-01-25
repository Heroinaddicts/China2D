#ifndef __GlfwWindow_h__
#define __GlfwWindow_h__

#include "China2DApi.h"

namespace China2D {
	class GlfwWindow : public Api::IWindow {
	public:
		virtual ~GlfwWindow() {}

		void PollEvents() override;
		bool ShouldClose() const override;

		Size GetSize() const override;
		void Resize(const Size& size) override;

		void* GetNativeHandle() const override;
	};
}

#endif //__GlfwWindow_h__
