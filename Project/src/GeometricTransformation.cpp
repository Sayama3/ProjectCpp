//
// Created by ianpo on 19/07/2024.
//

#include "GeometricTransformation.hpp"
#include "Core/Logger.hpp"

namespace GeometricTransformation {

	Image FlipHorizontal(const Image &img) {
		Image image(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (int x = 0; x < img.GetWidth(); ++x) {
			for (int y = 0; y < img.GetHeight(); ++y) {
				auto invX = (img.GetWidth() - 1) - x;
				for (int c = 0; c < img.GetChannels(); ++c) {
					image(invX,y,c) = img(x,y,c);
				}
			}
		}
		return image;
	}
	Image FlipVertical(const Image &img) {
		Image image(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (int x = 0; x < img.GetWidth(); ++x) {
			for (int y = 0; y < img.GetHeight(); ++y) {
				auto invY = (img.GetHeight() - 1) - y;
				for (int c = 0; c < img.GetChannels(); ++c) {
					image(x,invY,c) = img(x,y,c);
				}
			}
		}
		return image;
	}
	Image Rotate90(const Image &img) {
		Image image(img.GetHeight(), img.GetWidth(), img.GetChannels(), img.GetImageType(), 0);
		for (int x = 0; x < img.GetWidth(); ++x) {
			for (int y = 0; y < img.GetHeight(); ++y) {
				auto invY = (img.GetHeight() - 1) - y;
				for (int c = 0; c < img.GetChannels(); ++c) {
					image(invY,x,c) = img(x,y,c);
				}
			}
		}
		return image;
	}
	Image Crop(const Image &img, uint32_t top, uint32_t left, uint32_t bottom, uint32_t right) {
		top = std::clamp(top, 0u, img.GetHeight() - 1);
		left = std::clamp(left, 0u, img.GetWidth() - 1);
		bottom = std::clamp(bottom, 0u, img.GetHeight() - 1);
		right = std::clamp(right, 0u, img.GetWidth() - 1);

		uint32_t newWidth = std::abs(int64_t(right) - int64_t(left));
		uint32_t newHeight = std::abs(int64_t(bottom) - int64_t(top));
		uint32_t xMin = std::min(top, bottom);
		uint32_t yMin = std::min(left, right);
		Image image(newWidth, newHeight, img.GetChannels(), img.GetImageType(), 0);
		for (int x = 0; x < newWidth; ++x) {
			for (int y = 0; y < newHeight; ++y) {
				for (int c = 0; c < img.GetChannels(); ++c) {
					image(x,y,c) = img(x+xMin,y+yMin,c);
				}
			}
		}
		return image;
	}
	Image Translate(const Image &img, uint32_t decalX, uint32_t decalY) {
		Image image(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (int x = 0; x < img.GetWidth(); ++x) {
			for (int y = 0; y < img.GetHeight(); ++y) {
				for (int c = 0; c < img.GetChannels(); ++c) {
					image(x,y,c) = img((x+decalX) % img.GetWidth(),(y+decalY) % img.GetHeight(),c);
				}
			}
		}
		return image;
	}

	Image Resize(const Image &img, uint32_t newWidth, uint32_t newHeight) {
		Image image(newWidth, newHeight, img.GetChannels(), img.GetImageType(), 0);
		for (int x = 0; x < newWidth; ++x) {
			for (int y = 0; y < newHeight; ++y) {
				uint32_t orgX = (float(x)/float(newWidth)) * img.GetWidth();
				uint32_t orgY = (float(y)/float(newHeight)) * img.GetHeight();
				for (int c = 0; c < img.GetChannels(); ++c) {
					image(x,y,c) = img(orgX,orgY,c);
				}
			}
		}
		return image;
	}
	Image Shear(const Image &img, float decalX, float decalY) {
		Image image(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		for (int x = 0; x < img.GetWidth(); ++x) {
			for (int y = 0; y < img.GetHeight(); ++y) {
				for (int c = 0; c < img.GetChannels(); ++c) {
					image(x,y,c) = img(uint32_t(float(x)+float(y)*decalX) % img.GetWidth(),uint32_t(float(y)+float(x)*decalY) % img.GetHeight(),c);
				}
			}
		}
		return image;
	}
	Image Rotate(const Image &img, float angle, uint32_t centerX, uint32_t centerY) {

		auto cos = std::cos(-angle * float(DegToRad));
		auto sin = std::sin(-angle * float(DegToRad));
		int64_t width = img.GetWidth();
		int64_t height = img.GetHeight();
		Image image(width, height, img.GetChannels(), img.GetImageType(), 0);
		for (int64_t x = 0; x < width; ++x) {
			for (int64_t y = 0; y < height; ++y) {
				int64_t localX = x - centerX;
				int64_t localY = y - centerY;
				int64_t orgX = int64_t(float(localX) * cos + float(localY) * -sin);
				int64_t orgY = int64_t(float(localX) * sin + float(localY) * cos);
				orgX += centerX;
				orgY += centerY;
				if (orgX >= 0 && orgX < width && orgY >= 0 && orgY < height)
				{
					for (uint8_t c = 0; c < img.GetChannels(); ++c) {
						image(x,y,c) = img(orgX, orgY,c);
					}
				}
			}
		}

		return image;
	}
	Image Remap(const Image &img, const std::vector<Vec2UI>& remap) {
		Image image(img.GetWidth(), img.GetHeight(), img.GetChannels(), img.GetImageType(), 0);
		if(remap.size() != img.GetWidth() * img.GetHeight()) {
			PC_ERROR("The remap table isn't large enough ({} instead of {}). Returning empty image.",remap.size(), img.GetWidth() * img.GetHeight());
			return {};
		}
		for (int x = 0; x < img.GetWidth(); ++x) {
			for (int y = 0; y < img.GetHeight(); ++y) {
				auto pos = remap[img.GetIndex(x,y)];
				for (int c = 0; c < img.GetChannels(); ++c) {
					image(x,y,c)= img(pos.x, pos.y, c);
				}
			}
		}
		return image;
	}
	Image Zoom(const Image &img, float factor) {
		const uint32_t width = img.GetWidth();
		const uint32_t height = img.GetHeight();

		const uint32_t newWidth = width * factor;
		const uint32_t newHeight = height * factor;

		Image image(newWidth, newHeight, img.GetChannels(), img.GetImageType(), 0);
		for (int x = 0; x < newWidth; ++x) {
			for (int y = 0; y < newHeight; ++y) {
				float orgX = float(x) / factor;
				float orgY = float(y) / factor;
				float minX = std::floor(orgX);
				float minY = std::floor(orgY);
				float maxX = std::clamp(minX + 1.0f, 0.0f, float(width - 1));
				float maxY = std::clamp(minY + 1.0f, 0.0f, float(height - 1));

				Vec2 org{orgX, orgY};
				Vec2UI org00 {uint32_t(minX), uint32_t(minY)};
				Vec2UI org01 {uint32_t(minX), uint32_t(maxY)};
				Vec2UI org10 {uint32_t(maxX), uint32_t(minY)};
				Vec2UI org11 {uint32_t(maxX), uint32_t(maxY)};

				float tX = maxX - orgX;
				float tY = maxY - orgY;

				for (int c = 0; c < image.GetChannels(); ++c) {
					float col00 = img(org00.x, org00.y, c);
					float col10 = img(org10.x, org10.y, c);
					float colT0 = std::lerp(col00, col10, tX);
					float col01 = img(org01.x, org01.y, c);
					float col11 = img(org11.x, org11.y, c);
					float colT1 = std::lerp(col01, col11, tX);
					float colTT = std::lerp(colT1, colT1, tY);
					image(x,y,c) = (uint8_t)std::clamp(colTT, 0.0f, 255.0f);
				}
			}
		}
		return image;
	}

}
