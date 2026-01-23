#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "China2DApi.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height); // 调整视口大小
}

int main() {
	// 初始化GLFW
	if (!glfwInit()) {
		return -1;
	}

	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Game Engine", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// 设置OpenGL上下文
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// 初始化GLEW
	if (glewInit() != GLEW_OK) {
		return -1;
	}

	// 渲染循环
	while (!glfwWindowShouldClose(window)) {
		// 输入处理
		glfwPollEvents();

		// 清除颜色缓冲区
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 渲染操作
		glBegin(GL_QUADS); // 开始绘制矩形
		glColor3f(1.0f, 0.0f, 0.0f); // 红色
		glVertex2f(-0.5f, -0.5f); // 左下角
		glVertex2f(0.5f, -0.5f); // 右下角
		glVertex2f(0.5f, 0.5f); // 右上角
		glVertex2f(-0.5f, 0.5f); // 左上角
		glEnd();

		// 交换缓冲区
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}
