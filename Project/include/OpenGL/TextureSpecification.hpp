//
// Created by ianpo on 06/07/2024.
//

#pragma once

#include <cstdint>

enum TextureFilter : uint8_t
{
	Nearest,
	Linear,
};

enum TextureWrapper : uint8_t
{
	Repeat,
	ClampToEdge,
	MirroredRepeat,
};

enum PixelFormat : uint8_t
{
	RED = 1,
	RG = 2,
	RGB = 3,
	RGBA = 4,
};

enum PixelType : uint8_t
{
	PX_8,
	PX_16,

	PX_8UI,
	PX_16UI,
	PX_32UI,

	PX_8I,
	PX_16I,
	PX_32I,

	PX_16F, // This is a Half Float.
	PX_32F,
};

struct TextureSpecification
{
	inline TextureSpecification() = default;
	inline ~TextureSpecification() = default;

	uint32_t width = 0, height = 0, channels = 0;

	TextureFilter filterMag = TextureFilter::Linear;
	TextureFilter filterMin = TextureFilter::Linear;

	TextureWrapper wrapperS = TextureWrapper::Repeat;
	TextureWrapper wrapperT = TextureWrapper::Repeat;

	PixelFormat pixelFormat = PixelFormat::RGBA;
	PixelType pixelType = PixelType::PX_8;

	bool generateMipMaps = true;
};