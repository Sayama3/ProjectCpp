//
// Created by ianpo on 20/07/2024.
//

#include "ImageHelper.hpp"
#include <algorithm>

Texture TextureHelper::ImageToTexture(const Image &image) {
	if(image.GetImageType() == ModelType::Gray) {
		return GetGreyTexture(image);
	} else {
		return GetUsualTexture(image);
	}
}

Texture TextureHelper::GetGreyTexture(const Image &image) {

	static constexpr uint32_t ChannelCount = 3;
	const uint32_t width = image.GetWidth();
	const uint32_t height = image.GetHeight();

	TextureSpecification spec;
	spec.width = width;
	spec.height = height;
	spec.channels = ChannelCount;

	spec.pixelFormat = PixelFormat::RGB;
	spec.pixelType = PixelType::PX_8;

	spec.generateMipMaps = true;

	std::vector<uint8_t> greyImage(width * height * ChannelCount);
	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			uint32_t sum{0};
			for (int c = 0; c < image.GetChannels(); ++c) {
				sum += image(x,y,c);
			}
			sum /= image.GetChannels();
			std::fill_n(greyImage.begin() + (y * width * ChannelCount + x * ChannelCount), ChannelCount, std::clamp(sum, 0u, 255u));
		}
	}
	Texture tex{spec, Buffer{greyImage.data(), greyImage.size()}};
	return tex;
}

Texture TextureHelper::GetUsualTexture(const Image &image) {
	return {image.GetTextureSpec(), const_cast<Image &>(image).GetImageBuffer()};
}
