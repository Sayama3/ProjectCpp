//
// Created by Sayama on 17/01/2024.
//

#pragma once

#include "Core/Math.hpp"
#include "Renderer/VertexArray.hpp"

namespace PC {

	class Renderer {
	public:
		static void Init();
		static void Shutdown();
		static void SetClearColor(const glm::vec4 &color);
		static void Clear();
		static void DrawIndexed(const Ref<VertexArray> &vertexArray);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
	};

} // PC
