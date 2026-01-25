#include "PlatformGlfw.h"
#include "Engine.h"
#include <GLFW/glfw3.h>

namespace China2D {
	static void GlfwErrorCallback(int error, const char* desc) {
		// 先不接你的 Logger，后面你有日志系统再接入
		// fprintf(stderr, "GLFW Error %d: %s\n", error, desc);
		(void)error;
		(void)desc;
	}

	Api::IWindow* PlatformGlfw::CreateWindow(int w, int h, const std::string& title) {
		return nullptr;
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
}
