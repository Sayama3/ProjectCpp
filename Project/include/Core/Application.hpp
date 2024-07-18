//
// Created by ianpo on 18/07/2024.
//

#pragma once

#include <string>
#include <cstdint>
#include <memory>
#include "Core/Window.hpp"
#include "ImGui/ImGuiContext.hpp"

namespace PC {
	struct ApplicationParameters {
		std::string name = "Project Cpp";
		uint32_t width = 1280, height = 720;
	};

	class Application {
	public:
		Application(ApplicationParameters params = ApplicationParameters());
		~Application();
		Application(const Application &) = delete;
		Application &operator=(const Application &) = delete;

	public:
		[[nodiscard]] bool ShouldUpdate();
		void BeginUpdate();
		void EndUpdate();

	private:
		ApplicationParameters m_Parameters;
		std::shared_ptr<Window> m_Window{nullptr};
		std::unique_ptr<ImGuiContext> m_ImGui{nullptr};
		bool m_GladIsInit{false};
	};
}