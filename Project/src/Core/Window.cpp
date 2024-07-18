//
// Created by ianpo on 18/07/2024.
//

#include "Core/Window.hpp"

#include <glad/glad.h>

#define GLFW_INCLUDE_NONE 1

#include <GLFW/glfw3.h>

namespace PC {
	Window::Window(std::string name, uint32_t width, uint32_t height) : m_Name(std::move(name)), m_Width(width), m_Height(height) {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		GLFWwindow *window = glfwCreateWindow(static_cast<int>(m_Width), static_cast<int>(m_Height), m_Name.c_str(), nullptr, nullptr);
		if (!window) {
			return;
		}
		m_NativeWindow = window;
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);// Enable vsync
	}

	Window::~Window() {
		if (m_NativeWindow) {
			glfwDestroyWindow(reinterpret_cast<GLFWwindow *>(m_NativeWindow));
			glfwTerminate();
			m_NativeWindow = nullptr;
		}
	}

	bool Window::ShouldClose() const {
		return glfwWindowShouldClose(const_cast<GLFWwindow *>(GetNative<GLFWwindow>()));
	}

	void Window::Close() {
		glfwSetWindowShouldClose(const_cast<GLFWwindow *>(GetNative<GLFWwindow>()), true);
	}

	uint32_t Window::GetWidth() const {
		int width, height;
		glfwGetWindowSize(const_cast<GLFWwindow *>(GetNative<GLFWwindow>()), &width, &height);
		return width;
	}

	uint32_t Window::GetHeight() const {
		int width, height;
		glfwGetWindowSize(const_cast<GLFWwindow *>(GetNative<GLFWwindow>()), &width, &height);
		return height;
	}
	void Window::SwapBuffer() {
		glfwSwapBuffers(GetNative<GLFWwindow>());
	}
}