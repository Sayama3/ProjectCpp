//
// Created by Sayama on 17/01/2024.
//

#include "Core/Application.hpp"

#include "Events/Event.hpp"
#include "Events/MouseEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/ApplicationEvent.hpp"

namespace PC {
	enum GLFWKeyState : int {
		PRESS = GLFW_PRESS,
		RELEASE = GLFW_RELEASE,
		REPEAT = GLFW_REPEAT,
	};
	ApplicationSpecification::ApplicationSpecification(int argc, char** argv) : argc(argc), argv(argv)
	{
	}

	ApplicationSpecification::~ApplicationSpecification()
	{
	}

	Application::Application(const ApplicationSpecification& appSpec) : m_AppSpec(appSpec)
	{
		int success = glfwInit();
//            PC_CORE_ASSERT(success, "GLFW couldn't be initialized.")

		glfwSetErrorCallback(GLFWErrorCallback);

		m_Window = glfwCreateWindow(
				static_cast<int>(m_AppSpec.width),
				static_cast<int>(m_AppSpec.height),
				m_AppSpec.name.c_str(),
				nullptr,
				nullptr
		);

		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PC_CORE_INFO("glad loading status: {0}", status);

		PC_CORE_INFO("OpenGL Info:");
		PC_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		PC_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		PC_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

		glfwSetWindowUserPointer(m_Window, &m_AppSpec);
		SetVSync(m_AppSpec.VSync);

		// Set GLFW Callbacks
		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			ApplicationSpecification& data = *(ApplicationSpecification*)glfwGetWindowUserPointer(window);
			data.width = width;
			data.height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* window, int iconify)
		{
			ApplicationSpecification& data = *(ApplicationSpecification*)glfwGetWindowUserPointer(window);
			data.Minified = iconify == GLFW_TRUE;

			WindowMinifyEvent event(iconify == GLFW_TRUE);
			data.EventCallback(event);
			;        });

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			ApplicationSpecification& data = *(ApplicationSpecification*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			ApplicationSpecification& data = *(ApplicationSpecification*)glfwGetWindowUserPointer(window);

			switch ((GLFWKeyState)action) {
				case GLFWKeyState::PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFWKeyState::RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFWKeyState::REPEAT:
				{
					// Can be extract if we want the number of repeat/
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint){
			ApplicationSpecification& data = *(ApplicationSpecification*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(codepoint);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			ApplicationSpecification& data = *(ApplicationSpecification*)glfwGetWindowUserPointer(window);

			switch ((GLFWKeyState)action) {
				case GLFWKeyState::PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFWKeyState::RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset){
			ApplicationSpecification& data = *(ApplicationSpecification*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos){
			ApplicationSpecification& data = *(ApplicationSpecification*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event(static_cast<float>(xpos), static_cast<float>(ypos));
			data.EventCallback(event);
		});


	}

	Application::~Application() {

	}

	void Application::SwapBuffer()
	{
		glfwSwapBuffers(m_Window);
	}

	void Application::Run() {
		while (m_Running)
		{

		}
	}

	void Application::SetVSync(bool enabled) {
		//PC_PROFILE_FUNCTION();
		if (enabled) {
			glfwSwapInterval(1);
		}
		else{
			glfwSwapInterval(0);
		}

		m_AppSpec.VSync = enabled;
	}
} // PC