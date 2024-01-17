//
// Created by Sayama on 17/01/2024.
//

#pragma once

#include <string>
#include <vector>
#include "Core/Macros.hpp"
#include "Core/Logger.hpp"
#include "Core/Math.hpp"
#include "Events/Event.hpp"
#include "glad/glad.h"
#define GLFW_INCLUDE_NONE 1
#include "GLFW/glfw3.h"

namespace PC {

	using EventCallBackFn = std::function<void(PC::Event&)>;

	struct ApplicationSpecification
	{
		ApplicationSpecification(int argc, char** argv);
		~ApplicationSpecification();

		std::string name = "Cpp Project";
		uint32_t width = 1600;
		uint32_t height = 900;
		bool Minified = false;
		bool VSync = false;
		int argc;
		char** argv;
		EventCallBackFn EventCallback;
	};


	class Application
	{
	public:
		Application(const ApplicationSpecification& appSpec);
		~Application();

		void Run();
	private:
		void SwapBuffer();
		void SetVSync(bool enabled);

		inline static void GLFWErrorCallback(int error_code, const char* description) {
			PC_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
		}
	private:
		ApplicationSpecification m_AppSpec;
		GLFWwindow* m_Window;
		bool m_Running = true;
	};

} // PC
