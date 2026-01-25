#include "PlatformGlfw.h"
#include "Engine.h"
#include <GLFW/glfw3.h>
#include "GlfwWindow.h"

namespace China2D {
	static void GlfwErrorCallback(int error, const char* desc) {
		// 先不接你的 Logger，后面你有日志系统再接入
		// fprintf(stderr, "GLFW Error %d: %s\n", error, desc);
		(void)error;
		(void)desc;
	}

	Api::IWindow* PlatformGlfw::CreateWindow(int w, int h, const std::string& title) {

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		GLFWwindow* handle = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
		if (!handle) {
			return nullptr;
		}

		const uint32_t id = EngineAllocID;
		GlfwWindow* window = txnew GlfwWindow(this, id, title, handle);
		_Windows.insert(window);
		return window;
	}

	void PlatformGlfw::ReleaseWindow(Api::IWindow* const window) {
		_Windows.erase(window);
	}

	bool PlatformGlfw::Initialize() {
		glfwSetErrorCallback(
			[](int error, const char* desc) {
				ErrorLog(g_Engine, "Glfw error, code %d, %s", error, desc);
			}
		);
		if (glfwInit() != GLFW_TRUE) {
			return false;
		}
		return true;
	}

	void PlatformGlfw::Shutdown() {
		glfwTerminate();
	}

	void PlatformGlfw::PullEvents() {
		for (auto it = _Windows.begin(); it != _Windows.end(); it++) {
			(*it)->PollEvents();
		}
	}
}
