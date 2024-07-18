//
// Created by ianpo on 18/07/2024.
//

#include "Core/Application.hpp"
#include "Core/Macro.hpp"
#include "Core/Logger.hpp"
#include "Core/Profiler.hpp"

#include "glad/glad.h"

#define GLFW_INCLUDE_NONE 1

#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
	PC_ERROR("GLFW Error {}: {}", error, description);
}
namespace PC {
	Application::Application(ApplicationParameters params) : m_Parameters(std::move(params)) {
		//Init Glfw
		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit()) {
			return;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

		// Init Window
		m_Window = std::make_shared<Window>(m_Parameters.name, m_Parameters.width, m_Parameters.height);
		if (!m_Window) return;

		// Init Opengl
		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		m_GladIsInit = status;
		PC_INFO("glad loading status: {}", status);
		if (!m_GladIsInit) return;
		PC_INFO("OpenGL Info:\n  Vendor: {}\n  Renderer: {}\n  Version: {}", (const char *) glGetString(GL_VENDOR), (const char *) glGetString(GL_RENDERER), (const char *) glGetString(GL_VERSION));

		// Init ImGui
		m_ImGui = std::make_unique<ImGuiContext>(m_Window);
	}

	Application::~Application() {
		m_ImGui.reset();
	}

	bool Application::ShouldUpdate() {
		return m_Window && !m_Window->ShouldClose();
	}

	void Application::BeginUpdate() {
		PC_FRAME_START();
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();
		m_ImGui->BeginFrame();
		m_ImGui->UseDockspace();
	}

	void Application::EndUpdate() {
		glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
		glClear(GL_COLOR_BUFFER_BIT);
		m_ImGui->EndFrame();
		m_Window->SwapBuffer();
	}
}