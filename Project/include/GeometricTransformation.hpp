//
// Created by ianpo on 19/07/2024.
//

#pragma once

#include "Image.hpp"
#include "ImageIterator.hpp"
#include "Core/Math.hpp"
#include <cstdint>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <vector>
#include <tuple>

namespace GeometricTransformation
{
	[[nodiscard]] Image FlipHorizontal(const Image& img);
	[[nodiscard]] Image FlipVertical(const Image& img);
	[[nodiscard]] Image Rotate90(const Image& img);
	[[nodiscard]] Image Crop(const Image& img, uint32_t top, uint32_t left, uint32_t bottom, uint32_t right);
	[[nodiscard]] Image Translate(const Image& img, uint32_t decalX, uint32_t decalY);
	[[nodiscard]] Image Resize(const Image& img, uint32_t newWidth, uint32_t newHeight);
	[[nodiscard]] Image Shear(const Image& img, float decalX, float decalY);
	[[nodiscard]] Image Rotate(const Image& img, float angleDegree, uint32_t centerX, uint32_t centerY);
	[[nodiscard]] Image Remap(const Image& img, const std::vector<Vec2UI>& remap);
	[[nodiscard]] Image Zoom(const Image& img, float factor);
}