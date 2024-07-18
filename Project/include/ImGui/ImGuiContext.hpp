//
// Created by ianpo on 18/07/2024.
//

#pragma once

#include "Core/Window.hpp"
#include <memory>
namespace PC {
	class ImGuiContext {
	public:
		ImGuiContext(std::weak_ptr<Window> window);
		~ImGuiContext();
		ImGuiContext(const ImGuiContext&) = delete;
		ImGuiContext& operator=(const ImGuiContext&) = delete;
	public:
		void UseDockspace();
		void BeginFrame();
		void EndFrame();
	private:
		std::weak_ptr<Window> m_Window;
	};
}
