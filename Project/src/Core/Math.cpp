//
// Created by Sayama on 17/01/2024.
//

#include "Core/Math.hpp"

namespace PC {
	glm::mat4 Math::TRS(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
	{
		// PROFILE_FUNCTION();
		glm::mat4 trs(1.0f);
		trs = glm::translate(trs, position); // Translation Matrix
		trs = trs * glm::toMat4(rotation); // Rotation Matrix
		trs = glm::scale(trs, scale); // Scale Matrix
		return trs; // Translation * Rotation * Scale => TRS Matrix.
	}

	void Math::TRS(glm::mat4& trs, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale)
	{
		// PROFILE_FUNCTION();
		trs = glm::translate(trs, position); // Translation Matrix
		trs = trs * glm::toMat4(rotation); // Rotation Matrix
		trs = glm::scale(trs, scale); // Scale Matrix
	}
} // PC