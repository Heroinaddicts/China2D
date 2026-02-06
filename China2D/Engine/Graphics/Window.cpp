#include "Window.h"

namespace China2D {
    Size Window::GetSize() const {
        return Size();
    }

    void Window::SetSize(const Size& size) {
    }

    bool Window::ShouldClose() const {
        return false;
    }

    void Window::SetTitle(const std::string& title) {
    }

    void* Window::GetNativeHandle() const {
        return nullptr;
    }

    void Window::Show() {
    }

    void Window::Destroy() {
    }
}
