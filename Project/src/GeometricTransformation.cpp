//
// Created by ianpo on 19/07/2024.
//

#include "GeometricTransformation.hpp"

namespace GeometricTransformation {

	Image FlipHorizontal(const Image &img) {
		return Image();
	}
	Image FlipVertical(const Image &img) {
		return Image();
	}
	Image Rotate90(const Image &img) {
		return Image();
	}
	Image Crop(const Image &img, uint32_t top, uint32_t left, uint32_t bottom, uint32_t right) {
		return Image();
	}
	Image Translate(const Image &img, uint32_t decalX, uint32_t decalY) {
		return Image();
	}
	Image Resize(const Image &img, uint32_t newWidth, uint32_t newHeight) {
		return Image();
	}
	Image Shear(const Image &img, uint32_t decalX, uint32_t decalY) {
		return Image();
	}
	Image Rotate(const Image &img, float angleDegree, uint32_t centerX, uint32_t centerY) {
		return Image();
	}
	Image Remap(const Image &img, const std::vector<Vec2UI>& remap) {
		return Image();
	}
	Image Zoom(const Image &img, float factor) {
		return Image();
	}

}
