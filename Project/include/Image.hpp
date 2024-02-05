//
// Created by Sayama on 05/02/2024.
//

#pragma once

#include <cmath>
#include <cstdint>
#include <vector>
#include <ostream>
#include <optional>

struct Vec2UI
{
	uint32_t x;
	uint32_t y;
};

enum class ImageType
{
	None = 0,
	Red = 1,
	RG = 2,
	RGB = 3,
	RGBA = 4,
};

class Image {
public:
	// Constructors
	Image();
	Image(uint32_t width, uint32_t height, uint32_t channels, ImageType imageType, uint8_t value);
	Image(uint32_t width, uint32_t height, uint32_t channels, ImageType imageType, const std::vector<uint8_t>& image);
	Image(uint32_t width, uint32_t height, uint32_t channels, ImageType imageType, const uint8_t* imageBuffer, uint64_t imageSize);
	Image(const Image&);
	Image& operator=(const Image&);
	~Image();

	// Getter Setters
	[[nodiscard]] uint32_t GetWidth() const;
	void SetWidth(uint32_t width);
	[[nodiscard]] uint32_t GetHeight() const;
	void SetHeight(uint32_t height);
	[[nodiscard]] uint32_t GetChannels() const;
	void SetChannels(uint32_t channels);
	[[nodiscard]] ImageType GetImageType() const;
	void SetImageType(ImageType imageType);

	uint8_t& at(uint32_t x, uint32_t y, uint32_t channel);
	[[nodiscard]] const uint8_t& at(uint32_t x, uint32_t y, uint32_t channel) const;

	uint8_t& operator() (uint32_t x, uint32_t y, uint32_t channel);
	const uint8_t& operator() (uint32_t x, uint32_t y, uint32_t channel) const;

	void CreateOpenGLTexture();
	void DeleteOpenGLTexture();
	void UpdateOpenGLTexture();
	bool HasOpenGLTexture() const;
	std::optional<uint32_t> GetRenderId() const;
private:
	void UpdateImage();
	void RecreateOpenGLTexture();

	[[nodiscard]] uint32_t GetIndex(uint32_t x, uint32_t y) const;
	[[nodiscard]] uint32_t GetIndex(Vec2UI pos) const;
	[[nodiscard]] Vec2UI GetPosition(uint32_t index) const;

	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_Channels;
	ImageType m_ImageType;
	std::vector<uint8_t> m_Image;
	std::optional<uint32_t> m_RenderId;
};

inline std::ostream& operator<<(std::ostream& os, const Image& img)
{
	os << img.GetWidth() << "x" << img.GetHeight() << "x" << img.GetChannels() << "(" << (uint32_t)img.GetImageType() << ")";
	return os;
}