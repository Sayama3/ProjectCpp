//
// Created by Sayama on 17/01/2024.
//

#include "Core/Macros.hpp"
#include "Core/Logger.hpp"
#include "Core/Math.hpp"
#include "Renderer/Renderer.hpp"
#include "glad/glad.h"

namespace PC {
	void Renderer::Init() {
		// PC_PROFILE_FUNCTION();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::Shutdown() {
		// PC_PROFILE_FUNCTION();
	}

	void Renderer::SetClearColor(const glm::vec4 &color) {
		// PC_PROFILE_FUNCTION();
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::Clear() {
		// PC_PROFILE_FUNCTION();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::DrawIndexed(const Ref<VertexArray> &vertexArray) {
		// PC_PROFILE_FUNCTION();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
		// PC_PROFILE_FUNCTION();
		glViewport(static_cast<GLint>(x), static_cast<GLint>(y), static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	}
} // PC