//
// Created by ianpo on 19/07/2024.
//

#pragma once

#include <cstdint>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <tuple>

static constexpr inline double PI =  3.1415926535897932384626433832795028841971693993751058209749445923078164062;
static constexpr inline double DegToRad = PI / 180.0;
static constexpr inline double RadToDeg = 180.0 / PI;

template<typename T>
struct Vector2 {
	Vector2() = default;
	~Vector2() = default;
	Vector2(T x, T y) : x(x), y(y) {}
	union {
		struct {T x, y;};
		std::array<T, 2> values;
	};

	T& operator[](uint32_t i) {return values[i];}
	const T& operator[](uint32_t i) const {return values[i];}
};

template<typename T>
struct Vector3 {
	Vector3() = default;
	~Vector3() = default;
	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
	union {
		struct {T x, y, z;};
		std::array<T, 3> values;
	};

	T& operator[](uint32_t i) {return values[i];}
	const T& operator[](uint32_t i) const {return values[i];}
};

template<typename T>
Vector2<T> Clamp(Vector2<T> vec, Vector2<T> min, Vector2<T> max) {
	for (uint32_t i = 0; i < 2; ++i) {
		vec[i] = std::clamp(vec[i], min[i], max[i]);
	}
	return vec;
}

using Vec2 = Vector2<float>;
using Vec2UI = Vector2<uint32_t>;

