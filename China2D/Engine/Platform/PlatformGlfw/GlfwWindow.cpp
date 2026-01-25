#include "GlfwWindow.h"
#include "PlatformGlfw.h"
namespace China2D {
	void GlfwWindow::PollEvents() {
		glfwPollEvents();
	}

	bool GlfwWindow::ShouldClose() const {
		return _Handle ? (glfwWindowShouldClose(_Handle) != 0) : true;
	}

	Size GlfwWindow::GetSize() const {
		int w = 0, h = 0;
		if (_Handle) glfwGetWindowSize(_Handle, &w, &h);
		return Size(w, h);
	}

	void GlfwWindow::Resize(const Size& size) {
		if (_Handle) glfwSetWindowSize(_Handle, size._X, size._Y);
	}

	void GlfwWindow::Destroy() {
		if (_Handle) {
			glfwDestroyWindow(_Handle);
			_Handle = nullptr;
		}

		_Platform->ReleaseWindow(this);
		delete this; // 你要求显式控制：Destroy 即销毁对象
	}
}
