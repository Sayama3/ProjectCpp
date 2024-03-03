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
#include <functional>

Image::Image() : m_Width(0), m_Height(0), m_Channels(0), m_ImageType(ModelType::None), m_Image(0)
{
}

Image::Image(const std::filesystem::path &path) : m_Width(0), m_Height(0), m_Channels(0), m_ImageType(ModelType::None), m_Image(0)
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

	if(channels == 3)
	{
		m_ImageType = ModelType::RGB;
	}
	else if(channels == 4)
	{
		m_ImageType = ModelType::RGBA;
	}
	else if(channels == 1)
	{
		m_ImageType = ModelType::Gray;
	}
	else
	{
		m_ImageType = ModelType::None;
	}

	m_Image.insert(m_Image.end(), data, data + (width * height * channels));
	stbi_image_free(data);
}

Image::Image(uint32_t width, uint32_t height, uint32_t channels, ModelType imageType, uint8_t value) : m_Width(width), m_Height(height), m_Channels(channels), m_ImageType(imageType), m_Image(width * height * channels)
{
	for (unsigned char & channel : m_Image) {
		channel = value;
	}
}

Image::Image(uint32_t width, uint32_t height, uint32_t channels, ModelType imageType, const std::vector<uint8_t>& image) : m_Width(width), m_Height(height), m_Channels(channels), m_ImageType(imageType), m_Image(image)
{
	assert(image.size() == width * height * channels);
	CreateOpenGLTexture();
}

Image::Image(uint32_t width, uint32_t height, uint32_t channels, ModelType imageType, const uint8_t *imageBuffer, uint64_t imageSize) : m_Width(width), m_Height(height), m_Channels(channels), m_ImageType(imageType), m_Image(imageBuffer, imageBuffer + imageSize)
{
	assert(imageSize == width * height * channels);
	CreateOpenGLTexture();
}

Image::Image(const Image & o) : m_Width(o.m_Width), m_Height(o.m_Height), m_Channels(o.m_Channels), m_ImageType(o.m_ImageType), m_Image(o.m_Image)
{
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
	std::vector<uint8_t> newImage(width * m_Height * m_Channels, 0);

	for (int64_t x = 0; x < std::min(width, m_Width); ++x) {
		for (int64_t y = 0; y < m_Height; ++y) {
			for (int64_t c = 0; c < m_Channels; ++c) {
				int64_t indexNewImg = y * width * m_Channels + x * m_Channels + c;
				int64_t indexImg = y * m_Width * m_Channels + x * m_Channels + c;
				newImage[indexNewImg] = m_Image[indexImg];
			}
		}
	}
	m_Image = newImage;
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
	std::vector<uint8_t> newImage(m_Width * height * m_Channels, 0);

	for (int64_t x = 0; x < m_Width; ++x) {
		for (int64_t y = 0; y < std::min(height, m_Height); ++y) {
			for (int64_t c = 0; c < m_Channels; ++c) {
				int64_t indexNewImg = y * m_Width * m_Channels + x * m_Channels + c;
				int64_t indexImg = y * m_Width * m_Channels + x * m_Channels + c;
				newImage[indexNewImg] = m_Image[indexImg];
			}
		}
	}
	m_Image = newImage;
	m_Height = height;
	UpdateImage();
}

uint32_t Image::GetChannels() const
{
	return m_Channels;
}

void Image::SetChannels(uint32_t channels)
{
	std::vector<uint8_t> newImage(m_Width * m_Height * channels, 0);

	for (int64_t x = 0; x < m_Width; ++x) {
		for (int64_t y = 0; y < m_Height; ++y) {
			for (int64_t c = 0; c < std::min(m_Channels, channels); ++c) {
				int64_t indexNewImg = y * m_Width * channels + x * channels + c;
				int64_t indexImg = y * m_Width * m_Channels + x * m_Channels + c;
				newImage[indexNewImg] = m_Image[indexImg];
			}
		}
	}
	m_Image = newImage;
	m_Channels = channels;
	UpdateImage();
}
void Image::Resize(uint32_t width, uint32_t height, uint32_t channels)
{
	std::vector<uint8_t> newImage(width * height * channels, 0);

	for (int64_t x = 0; x < std::min(width, m_Width); ++x) {
		for (int64_t y = 0; y < std::min(height, m_Height); ++y) {
			for (int64_t c = 0; c < std::min(channels, m_Channels); ++c) {
				int64_t indexNewImg = y * width * channels + x * channels + c;
				int64_t indexImg = y * m_Width * m_Channels + x * m_Channels + c;
				newImage[indexNewImg] = m_Image[indexImg];
			}
		}
	}
	m_Image = newImage;

	m_Width = width;
	m_Height = height;
	m_Channels = channels;

	UpdateImage();
}

ModelType Image::GetImageType() const
{
	return m_ImageType;
}
void Image::ConvertImageToModelType(ModelType imageType){
	std::function<std::vector<uint8_t>(std::vector<uint8_t>)> conv=[&](std::vector<uint8_t> in ) {
		if(imageType!=m_ImageType)
			std::cerr<<"Conversion from "<< (int)m_ImageType << " to " <<(int)imageType<<std::endl;
		return in;
	};
	switch(m_ImageType){
		case ModelType::Gray:
			switch(imageType){
				case ModelType::RGB:
					conv = [](std::vector<uint8_t> in) {
						uint8_t s = 0;
						for(uint8_t i : in)s+=i;
						in.clear();
						in.push_back(s);
						in.push_back(s);
						in.push_back(s);
						return in;
					};
					break;
				case ModelType::RGBA:
					conv = [](std::vector<uint8_t> in) {
						uint8_t s = 0;
						for(uint8_t i : in)s+=i;
						in.clear();
						in.push_back(s);
						in.push_back(s);
						in.push_back(s);
						in.push_back(255);
						return in;
					};
					break;
			}
			break;
		case ModelType::RGB:
			if(imageType==ModelType::Gray){
				conv = [](std::vector<uint8_t> in) {
					uint8_t s=0;
					for (auto v : in) {
						s+=v;
					}
					in.clear();
					in.push_back(s);
					return in;
				};
			};
			break;
		case ModelType::RGBA:
			if(imageType==ModelType::ARGB) {
				conv = [](std::vector<uint8_t> in) {
					auto a = in[3];
					in[3]=in[2];
					in[2]=in[1];
					in[1]=in[0];
					in[0]=a;
					return in;
				};
			}
			if(imageType==ModelType::Gray){
				conv = [](std::vector<uint8_t> in) {
					uint8_t s=0;
					for (auto v : in) {
						s+=v;
					}
					in.clear();
					in.push_back(s);
					return in;
				};
			}
			break;
		case ModelType::ARGB:
			if(imageType==ModelType::RGBA){
				conv = [](std::vector<uint8_t> in) {
					auto b = in[3];
					in[3]=in[0];
					in[0]=in[1];
					in[1]=in[2];
					in[2]=b;
					return in;
				};
			}
			break;
	}
	const auto targetChannelCount=ImageHelper::GetModelTypeChannelCount(imageType);
	std::vector<uint8_t> newPixels(m_Width*m_Height*targetChannelCount);
	for (int y = 0; y < m_Height; ++y) {
		for (int x = 0; x < m_Width; ++x) {
			auto begin=m_Image.begin()+(y * m_Width * m_Channels + x * m_Channels);
			std::vector<uint8_t> pix(begin,begin+m_Channels);
			assert(pix.size()==m_Channels);
			pix=conv(pix);
			uint8_t* ptrTrg = &newPixels[(y * m_Width * targetChannelCount + x * targetChannelCount)];
			std::memcpy(ptrTrg, pix.data(), pix.size() * sizeof(pix[0]));
		}
	}
	m_ImageType=imageType;
	m_Channels=targetChannelCount;
	m_Image=newPixels;

	if(m_RenderId)
	{
		RecreateOpenGLTexture();
	}
}

void Image::SetImageType(ModelType imageType)
{
	m_ImageType = imageType;
}

void Image::UpdateImage()
{
	m_Image.resize(m_Width * m_Height * m_Channels);
	if(HasOpenGLTexture()) RecreateOpenGLTexture();
}

Vec2UI Image::GetPosition(uint32_t index) const {
	uint32_t y = index / (m_Width * m_Channels);
	uint32_t x = (index / m_Channels) % m_Width;
	return {x, y};
}

uint32_t Image::GetIndex(Vec2UI pos) const {return GetIndex(pos.x, pos.y);}

uint32_t Image::GetIndex(uint32_t x, uint32_t y) const {return y * m_Width * m_Channels + x * m_Channels;};

bool Image::IsInside(uint32_t x, uint32_t y) const
{
	return x < m_Width && y < m_Height;
}

bool Image::IsInside(uint32_t x, uint32_t y, uint32_t channel) const
{
	return x < m_Width && y < m_Height && channel < m_Channels;
}

uint8_t &Image::at(uint32_t x, uint32_t y, uint32_t channel) {
	if(x >= m_Width) {throw std::out_of_range(std::format("the value x({0}) is outside the limits [0, {1}[", x, m_Width));}
	if(y >= m_Height) {throw std::out_of_range(std::format("the value y({0}) is outside the limits [0, {1}[", y, m_Height));}
	if(channel >= m_Channels) {throw std::out_of_range(std::format("the value channel({0}) is outside the limits [0, {1}[", channel, m_Channels));}
	return m_Image[GetIndex(x,y) + channel];
}

const uint8_t &Image::at(uint32_t x, uint32_t y, uint32_t channel) const {
	if(x >= m_Width) {throw std::out_of_range(std::format("the value x({0}) is outside the limits [0, {1}[", x, m_Width));}
	if(y >= m_Height) {throw std::out_of_range(std::format("the value y({0}) is outside the limits [0, {1}[", y, m_Height));}
	if(channel >= m_Channels) {throw std::out_of_range(std::format("the value channel({0}) is outside the limits [0, {1}[", channel, m_Channels));}
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
//    auto ch = std::max(ImageHelper::GetModelTypeChannelCount(m_ImageType), (uint32_t)3);
	auto ch = m_Channels;
	if(ch == 4) { internalFormat = GL_RGBA8; dataFormat = GL_RGBA; }
	else if(ch == 3) { internalFormat = GL_RGB8; dataFormat = GL_RGB; }
	else if(ch == 2) { internalFormat = GL_RG8; dataFormat = GL_RG; }
	else if(ch == 1) { internalFormat = GL_R8; dataFormat = GL_RED; }

	glCreateTextures(GL_TEXTURE_2D, 1, &rendererID);
	glTextureStorage2D(rendererID, 1, internalFormat, static_cast<GLsizei>(m_Width), static_cast<GLsizei>(m_Height));

	//TODO: Add parameter on the Texture API to be able to change this type of parameters.
	glTextureParameteri(rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(rendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	m_RenderId = rendererID;
	UpdateOpenGLTexture();
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
		//TODO: recreate the image following the display mode.
		GLenum dataFormat = 0;
		if(m_Channels == 4) { dataFormat = GL_RGBA; }
		else if(m_Channels == 3) { dataFormat = GL_RGB; }
		else if(m_Channels == 2) { dataFormat = GL_RG; }
		else if(m_Channels == 1) { dataFormat = GL_RED; }
		//glTextureSubImage2D(m_RenderId.value(), 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE,m_Image.data());
		//return;
		/*
        if(m_ImageType!=ModelType::RGB && m_ImageType!=ModelType::RGBA) {
            Image newImg(*this);
            switch (m_ImageType) {

                case ModelType::Gray:
                case ModelType::HSL :
                    newImg.ConvertImageToModelType(ModelType::RGB);
                case ModelType::RGB:
                    dataFormat = GL_RGB;
                    break;
                case ModelType::HSLA:
                case ModelType::ARGB:
                    newImg.ConvertImageToModelType(ModelType::RGBA);
                case ModelType::RGBA:
                    dataFormat = GL_RGBA;
                    break;
            }
            glTextureSubImage2D(m_RenderId.value(), 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE,newImg.m_Image.data());
        }
        else
        */

		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTextureSubImage2D(m_RenderId.value(), 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, m_Image.data());
		}
	}
}

bool Image::HasOpenGLTexture() const {
	return m_RenderId.has_value();
}

std::optional<uint32_t> Image::GetRenderId() const {
	return m_RenderId;
}


Image &Image::operator+=(const Image &rht) {
	if(m_Channels != rht.m_Channels)
	{
		throw std::out_of_range("The two images don't have the same numbers of channels");
	}
	auto width = std::max(m_Width, rht.m_Width);
	auto height = std::max(m_Height, rht.m_Height);
	auto channels = m_Channels;
	std::vector<uint8_t> newImage(width * height * channels);

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			for (int c = 0; c < channels; ++c) {
				int16_t p1 = this->IsInside(x,y,c) ? this->at(x,y,c) : 0;
				int16_t p2 = rht.IsInside(x,y,c) ? rht.at(x,y,c) : 0;
				newImage[(y * width * channels) + x * channels + c] = std::clamp(p1 + p2, 0, 255);
			}
		}
	}
	m_Width = width;
	m_Height = height;
	m_Channels = channels;
	m_Image = newImage;
	UpdateOpenGLTexture();
	return *this;
}

Image &Image::operator+=(const uint8_t rht) {
	for (int x = 0; x < m_Width; ++x) {
		for (int y = 0; y < m_Height; ++y) {
			for (int c = 0; c < m_Channels; ++c) {
				this->add(x,y,c,rht);
			}
		}
	}
	return *this;
}

Image &Image::operator+=(const std::vector<uint8_t> &rht) {
	for (int x = 0; x < m_Width; ++x) {
		for (int y = 0; y < m_Height; ++y) {
			for (int c = 0; c < m_Channels; ++c) {
				int16_t val = rht.size() < c+1 ? 0 : rht[c];
				this->add(x,y,c,val);
			}
		}
	}
	return *this;
}

Image &Image::operator-=(const Image &rht) {
	if(m_Channels != rht.m_Channels)
	{
		throw std::out_of_range("The two images don't have the same numbers of channels");
	}
	auto width = std::max(m_Width, rht.m_Width);
	auto height = std::max(m_Height, rht.m_Height);
	auto channels = m_Channels;
	std::vector<uint8_t> newImage(width * height * channels);

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			for (int c = 0; c < channels; ++c) {
				int16_t p1 = this->IsInside(x,y,c) ? this->at(x,y,c) : 0;
				int16_t p2 = rht.IsInside(x,y,c) ? rht.at(x,y,c) : 0;
				newImage[(y * width * channels) + x * channels + c] = std::clamp(p1 - p2, 0, 255);
			}
		}
	}
	m_Width = width;
	m_Height = height;
	m_Channels = channels;
	m_Image = newImage;
	UpdateOpenGLTexture();
	return *this;
}

Image &Image::operator-=(const uint8_t rht) {
	return *this+=-rht;
}

Image &Image::operator-=(const std::vector<uint8_t> &rht) {
	for (int x = 0; x < m_Width; ++x) {
		for (int y = 0; y < m_Height; ++y) {
			for (int c = 0; c < m_Channels; ++c) {
				int16_t val = rht.size() < c+1 ? 0 : rht[c];
				this->add(x,y,c,-1*val);
			}
		}
	}
	return *this;
}

Image &Image::operator^=(const Image &rht) {
	if(m_Channels != rht.m_Channels)
	{
		throw std::out_of_range("The two images don't have the same numbers of channels");
	}
	auto width = std::max(m_Width, rht.m_Width);
	auto height = std::max(m_Height, rht.m_Height);
	auto channels = m_Channels;
	std::vector<uint8_t> newImage(width * height * channels);

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			for (int c = 0; c < channels; ++c) {
				int16_t p1 = this->IsInside(x,y) ? this->at(x,y,c) : 0;
				int16_t p2 = rht.IsInside(x,y) ? rht.at(x,y,c) : 0;
				newImage[(y * width * channels) + x * channels + c] = std::abs(p1 - p2);
			}
		}
	}
	m_Width = width;
	m_Height = height;
	m_Channels = channels;
	m_Image = newImage;
	UpdateOpenGLTexture();
	return *this;
}

Image &Image::operator^=(const uint8_t rht) {
	for (int x = 0; x < m_Width; ++x) {
		for (int y = 0; y < m_Height; ++y) {
			for (int c = 0; c < m_Channels; ++c) {
				this->at(x,y,c)=std::abs(this->at(x,y,c)-rht);
			}
		}
	}
	return *this;
}

Image &Image::operator^=(const std::vector<uint8_t> &rht) {
	for (int x = 0; x < m_Width; ++x) {
		for (int y = 0; y < m_Height; ++y) {
			for (int c = 0; c < m_Channels; ++c) {
				int16_t val = rht.size() < c+1 ? 0 : rht[c];
				this->at(x,y,c)=std::abs(this->at(x,y,c)-val);
			}
		}
	}
	return *this;
}

Image &Image::operator*=(float rht) {
	for (int x = 0; x < m_Width; ++x) {
		for (int y = 0; y < m_Height; ++y) {
			for (int c = 0; c < m_Channels; ++c) {
				this->set(x,y,c,this->at(x,y,c)*rht);
			}
		}
	}
	return *this;
}

Image &Image::operator/=(float rht) {
	return *this*=(1/rht);
}
Image operator<(Image im, uint8_t ceil) {
	auto cha=im.m_Channels;
	Image image(im.m_Width,im.m_Height,1,ModelType::Gray,255);
	for (int x = 0; x < im.m_Width; ++x) {
		for (int y = 0; y < im.m_Height; ++y) {
			bool pass=true;
			int av=0;
			for (int c = 0; c < cha; ++c) {
				uint8_t val=im(x,y,c);
				if(val>ceil){
					pass=false;
					break;
				}else
					av+=val;
			}
			image(x,y,0)=pass ? (uint8_t)(av/cha) : ceil;
		}
	}
	//image.CreateOpenGLTexture();
	return image;
}

Image &Image::set(uint32_t x, uint32_t y, uint32_t channel, int32_t val) {
	this->at(x, y, channel)=val < 0 ? 0 : (val > 255 ? 255 : val);
	return *this;
}
Image &Image::add(uint32_t x, uint32_t y, uint32_t channel, int16_t val) {
	this->set(x, y, channel,this->at(x,y,channel)+val);
	return *this;
}


