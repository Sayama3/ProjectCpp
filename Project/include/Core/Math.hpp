//
// Created by Sayama on 17/01/2024.
//

#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/hash.hpp>
#include <iostream>
#include <cmath>
#include <cstdint>

namespace PC
{
	class Math
	{
	public:
		/**
		 * Create a Transform matrix from a position, a rotation, and a scale.
		 * @param position The position as a 3D vector.
		 * @param rotation The rotation as a quaternion.
		 * @param scale The scale as a 3D vector.
		 * @return A 4x4 matrix representation of the Transform matrix.
		 */
		static glm::mat4 TRS(const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);
		static void TRS(glm::mat4& trs, const glm::vec3& position, const glm::quat& rotation, const glm::vec3& scale);

		template<typename T>
		static std::string to_string(const T& value)
		{
			return glm::to_string(value);
		}
	};

	template<>
	inline std::string Math::to_string<uint8_t>(const uint8_t& value) {return std::to_string(value);}
	template<>
	inline std::string Math::to_string<uint16_t>(const uint16_t& value) {return std::to_string(value);}
	template<>
	inline std::string Math::to_string<uint32_t>(const uint32_t& value) {return std::to_string(value);}
	template<>
	inline std::string Math::to_string<uint64_t>(const uint64_t& value) {return std::to_string(value);}
	template<>
	inline std::string Math::to_string<int8_t>(const int8_t& value) {return std::to_string(value);}
	template<>
	inline std::string Math::to_string<int16_t>(const int16_t& value) {return std::to_string(value);}
	template<>
	inline std::string Math::to_string<int32_t>(const int32_t& value) {return std::to_string(value);}
	template<>
	inline std::string Math::to_string<int64_t>(const int64_t& value) {return std::to_string(value);}
	template<>
	inline std::string Math::to_string<float_t>(const float_t& value) {return std::to_string(value);}
	template<>
	inline std::string Math::to_string<double_t>(const double_t& value) {return std::to_string(value);}

} // PC
inline std::ostream& operator << (std::ostream & os, const glm::mat4 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::mat3 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::mat2 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::vec4 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::vec3 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::vec2 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::vec1 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::ivec4 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::ivec3 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::ivec2 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::ivec1 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::bvec4 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::bvec3 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::bvec2 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::bvec1 value){
	return os << glm::to_string(value);
}
inline std::ostream& operator << (std::ostream & os, const glm::quat value){
	return os << glm::to_string(value);
}