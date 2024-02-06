//
// Created by Sayama on 05/02/2024.
//

#include "Image.hpp"

#include <cassert>
#include <exception>
#include <stdexcept>
#include <string>
#include <format>
#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>

Image::Image() : m_Width(0), m_Height(0), m_Channels(0), m_ImageType(ImageType::None), m_Image(0)
{
	CreateOpenGLTexture();
}

Image::Image(const std::filesystem::path &path) : m_Width(0), m_Height(0), m_Channels(0), m_ImageType(ImageType::None), m_Image(0)
{
	if(!std::filesystem::exists(path))
	{
		std::cout << "The file '" << path << "' doesn't exist." << std::endl;
		return;
	}

	stbi_set_flip_vertically_on_load(false);
	std::string strPath = path.string();
	int width, height, channels;
	stbi_uc* data = stbi_load(strPath.c_str(), &width, &height, &channels, 0);

	if(data == nullptr)
	{
		std::cout << "The file '" << path << "' wasn't load correctly.\n" << stbi_failure_reason() << std::endl;
		return;
	}

	m_Width = width;
	m_Height = height;
	m_Channels = channels;
	m_ImageType = (ImageType)channels;
	m_Image.insert(m_Image.end(), data, data + (width * height * channels));
	stbi_image_free(data);
	CreateOpenGLTexture();
}

Image::Image(uint32_t width, uint32_t height, uint32_t channels, ImageType imageType, uint8_t value) : m_Width(width), m_Height(height), m_Channels(channels), m_ImageType(imageType), m_Image(width * height * channels)
{
	for (unsigned char & channel : m_Image) {
		channel = value;
	}
	CreateOpenGLTexture();
}

Image::Image(uint32_t width, uint32_t height, uint32_t channels, ImageType imageType, const std::vector<uint8_t>& image) : m_Width(width), m_Height(height), m_Channels(channels), m_ImageType(imageType), m_Image(image)
{
	assert(image.size() == width * height * channels);
	CreateOpenGLTexture();
}

Image::Image(uint32_t width, uint32_t height, uint32_t channels, ImageType imageType, const uint8_t *imageBuffer, uint64_t imageSize) : m_Width(width), m_Height(height), m_Channels(channels), m_ImageType(imageType), m_Image(imageBuffer, imageBuffer + imageSize)
{
	assert(imageSize == width * height * channels);
	CreateOpenGLTexture();
}

Image::Image(const Image & o) : m_Width(o.m_Width), m_Height(o.m_Height), m_Channels(o.m_Channels), m_ImageType(o.m_ImageType), m_Image(o.m_Image)
{
	for (int i = 0; i < m_Image.size(); ++i) {
		m_Image[i] = o.m_Image[i];
	}
	CreateOpenGLTexture();
}

Image& Image::operator=(const Image & o)
{
	m_Width = o.m_Width;
	m_Height = o.m_Height;
	m_Channels = o.m_Channels;
	m_ImageType = o.m_ImageType;
	m_Image = o.m_Image;

	if(HasOpenGLTexture()) RecreateOpenGLTexture();
	return *this;
}
Image::~Image()
{
	if(m_RenderId)
	{
		uint32_t renderId = m_RenderId.value();
		glDeleteTextures(1, &renderId);
	}
}


uint32_t Image::GetWidth() const
{
	return m_Width;
}

void Image::SetWidth(uint32_t width)
{
	//TODO: Resize the image.
	m_Width = width;
	UpdateImage();
}

uint32_t Image::GetHeight() const
{
	return m_Height;
}

void Image::SetHeight(uint32_t height)
{
	//TODO: Resize the image.
	m_Height = height;
	UpdateImage();
}

uint32_t Image::GetChannels() const
{
	return m_Channels;
}

void Image::SetChannels(uint32_t channels)
{
	//TODO: Resize the image.
	m_Channels = channels;
	UpdateImage();
}

ImageType Image::GetImageType() const
{
	return m_ImageType;
}

void Image::SetImageType(ImageType imageType)
{
	// TODO: What do I do ?
	m_ImageType = imageType;
}

void Image::UpdateImage()
{
	m_Image.resize(m_Width * m_Height * m_Channels);
	if(HasOpenGLTexture()) RecreateOpenGLTexture();
}

Vec2UI Image::GetPosition(uint32_t index) const {
	uint32_t x = index / (m_Height * m_Channels);
	uint32_t y = (index / m_Channels) % m_Height;
	return {x, y};
}

uint32_t Image::GetIndex(Vec2UI pos) const {return GetIndex(pos.x, pos.y);}

uint32_t Image::GetIndex(uint32_t x, uint32_t y) const {return x * m_Height * m_Channels + y * m_Channels;};

uint8_t &Image::at(uint32_t x, uint32_t y, uint32_t channel) {
	if(x >= m_Width) {throw std::out_of_range(std::format("the value x({0}) is outside the limits [0, {1}[", x, m_Width));}
	if(y >= m_Height) {throw std::out_of_range(std::format("the value y({0}) is outside the limits [0, {1}[", x, m_Height));}
	if(channel >= m_Channels) {throw std::out_of_range(std::format("the value channel({0}) is outside the limits [0, {1}[", x, m_Channels));}
	return m_Image[GetIndex(x,y) + channel];
}

const uint8_t &Image::at(uint32_t x, uint32_t y, uint32_t channel) const {
	if(x >= m_Width) {throw std::out_of_range(std::format("the value x({0}) is outside the limits [0, {1}[", x, m_Width));}
	if(y >= m_Height) {throw std::out_of_range(std::format("the value y({0}) is outside the limits [0, {1}[", x, m_Height));}
	if(channel >= m_Channels) {throw std::out_of_range(std::format("the value channel({0}) is outside the limits [0, {1}[", x, m_Channels));}
	return m_Image[GetIndex(x,y) + channel];
}

uint8_t &Image::operator()(uint32_t x, uint32_t y, uint32_t channel) {
	return m_Image[GetIndex(x,y) + channel];
}

const uint8_t &Image::operator()(uint32_t x, uint32_t y, uint32_t channel) const {
	return m_Image[GetIndex(x,y) + channel];
}

void Image::CreateOpenGLTexture()
{
	if(m_RenderId.has_value())
	{
		std::cout << "Texture Already Created." << std::endl;
		return;
	}

	GLenum internalFormat = 0;
	GLenum dataFormat = 0;

	uint32_t rendererID;
	if(m_Channels == 4) { internalFormat = GL_RGBA8; dataFormat = GL_RGBA; }
	else if(m_Channels == 3) { internalFormat = GL_RGB8; dataFormat = GL_RGB; }
	else if(m_Channels == 2) { internalFormat = GL_RG8; dataFormat = GL_RG; }
	else if(m_Channels == 1) { internalFormat = GL_R8; dataFormat = GL_RED; }

	glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
	glTextureStorage2D(rendererID, 1, internalFormat, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height));

	//TODO: Add parameter on the Texture API to be able to change this type of parameters.
	glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTextureSubImage2D(rendererID, 0, 0, 0, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height), dataFormat, GL_UNSIGNED_BYTE, m_Image.data());

	m_RenderId = rendererID;
}

void Image::DeleteOpenGLTexture() {
	if(m_RenderId)
	{
		uint32_t renderId = m_RenderId.value();
		glDeleteTextures(1, &renderId);
		m_RenderId = {};
	}
}

void Image::RecreateOpenGLTexture()
{
	DeleteOpenGLTexture();
	CreateOpenGLTexture();
}

void Image::UpdateOpenGLTexture()
{
	if(m_RenderId)
	{
		GLenum internalFormat = 0;
		GLenum dataFormat = 0;
		if(m_Channels == 4) { internalFormat = GL_RGBA8; dataFormat = GL_RGBA; }
		else if(m_Channels == 3) { internalFormat = GL_RGB8; dataFormat = GL_RGB; }
		else if(m_Channels == 2) { internalFormat = GL_RG8; dataFormat = GL_RG; }
		else if(m_Channels == 1) { internalFormat = GL_R8; dataFormat = GL_RED; }

		glTextureSubImage2D(m_RenderId.value(), 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, m_Image.data());
	}
}

bool Image::HasOpenGLTexture() const {
	return m_RenderId.has_value();
}

std::optional<uint32_t> Image::GetRenderId() const {
	return m_RenderId;
}
