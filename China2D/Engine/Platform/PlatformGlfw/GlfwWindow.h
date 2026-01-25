#ifndef __GlfwWindow_h__
#define __GlfwWindow_h__

#include "China2DApi.h"
#include <GLFW/glfw3.h>
namespace China2D {
	class IBasePlatform;
	class GlfwWindow : public Api::IWindow {
	public:
		virtual ~GlfwWindow() {}

		GlfwWindow(IBasePlatform * const p, const uint32_t id, const std::string& name, GLFWwindow* handle)
			: Api::IWindow(id, name), _Handle(handle), _Platform(p) {}

		void PollEvents() override;
		bool ShouldClose() const override;

		Size GetSize() const override;
		void Resize(const Size& size) override;

		__forceinline void* GetNativeHandle() const override {
			return _Handle;
		}

		void Destroy() override;

	private:
		GLFWwindow* _Handle = nullptr;
		IBasePlatform* const _Platform;
	};
}

#endif //__GlfwWindow_h__
