#include "GlfwWindow.h"

namespace China2D {
	void GlfwWindow::PollEvents() {
	}

	bool GlfwWindow::ShouldClose() const {
		return false;
	}

	Size GlfwWindow::GetSize() const {
		return Size();
	}

	void GlfwWindow::Resize(const Size& size) {
	}

	void* GlfwWindow::GetNativeHandle() const {
		return nullptr;
	}
}
