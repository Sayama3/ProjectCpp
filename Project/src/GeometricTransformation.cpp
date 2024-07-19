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
				auto orgX = x/newWidth * img.GetWidth();
				auto orgY = y/newHeight * img.GetHeight();
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
		uint32_t width = img.GetWidth();
		uint32_t height = img.GetHeight();
		uint32_t newWidth = img.GetWidth() * factor;
		uint32_t newHeight = img.GetHeight() * factor;
		Image image(newWidth, newHeight, img.GetChannels(), img.GetImageType(), 0);
		for (int x = 0; x < newWidth; ++x) {
			for (int y = 0; y < newHeight; ++y) {
				float org_x = float(x) / factor;
				float org_y = float(y) / factor;

				uint32_t o_0x= std::clamp(std::floor(org_x)+0, 0.0f, float(width-1));
				uint32_t o_1x= std::clamp(std::floor(org_x)+0, 0.0f, float(width-1));
				uint32_t o_2x= std::clamp(std::floor(org_x)+1, 0.0f, float(width-1));
				uint32_t o_3x= std::clamp(std::floor(org_x)+1, 0.0f, float(width-1));

				uint32_t o_0y = std::clamp(std::floor(org_y)+0, 0.0f, float(height-1));
				uint32_t o_1y = std::clamp(std::floor(org_y)+1, 0.0f, float(height-1));
				uint32_t o_2y = std::clamp(std::floor(org_y)+0, 0.0f, float(height-1));
				uint32_t o_3y = std::clamp(std::floor(org_y)+1, 0.0f, float(height-1));

				for (int chan = 0; chan < img.GetChannels(); ++chan) {
					float wholeA;
					float wholeB;
					float wholeC;
					auto a = std::lerp(std::modf(org_y, &wholeA), img(o_0x,o_0y, chan), img(o_1x,o_1y, chan));
					auto b = std::lerp(std::modf(org_y, &wholeB), img(o_2x,o_2y, chan), img(o_3x,o_3y, chan));
					auto c = std::lerp(std::modf(org_x, &wholeC), a, b);
					image(x,y,chan) = std::clamp(c, 0.0, 255.0);
				}
			}
		}
		return image;
	}

}
