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
	union {
		struct {T x, y;};
		std::array<T, 2> values;
	};

	T& operator[](uint32_t i) {return values[i];}
	const T& operator[](uint32_t i) const {return values[i];}
};

template<typename T>
struct Vector3 {
	union {
		struct {T x, y, z;};
		std::array<T, 3> values;
	};

	T& operator[](uint32_t i) {return values[i];}
	const T& operator[](uint32_t i) const {return values[i];}
};

using Vec2 = Vector2<float>;
using Vec2UI = Vector2<uint32_t>;

