//
// Created by Sayama on 05/02/2024.
//

#include "Image.hpp"

#include <exception>
#include <stdexcept>
#include <string>
#include <format>
#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>
#include <functional>

#include "Core/Logger.hpp"

Image::Image() : m_Width(0), m_Height(0), m_Channels(0), m_ImageType(ModelType::None), m_Image(0), Dirty(false)
{
}

Image::Image(const std::filesystem::path &path) : m_Width(0), m_Height(0), m_Channels(0), m_ImageType(ModelType::None), m_Image(0)
{
	if(!std::filesystem::exists(path))
	{
		PC_WARN("The file '{}' doesn't exist.", path.string());
		return;
	}

	stbi_set_flip_vertically_on_load(false);
	std::string strPath = path.string();
	int width, height, channels;
	stbi_uc* data = stbi_load(strPath.c_str(), &width, &height, &channels, 0);

	if(data == nullptr)
	{
		PC_WARN("The file '{}' wasn't load correctly. '{}'", path.string(), stbi_failure_reason());
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
	PC_ASSERT(image.size() == width * height * channels, "image.size()({}) == width({}) * height({}) * channels({}) (={})",image.size(),width,height,channels, width*height*channels);
}

Image::Image(uint32_t width, uint32_t height, uint32_t channels, ModelType imageType, const uint8_t *imageBuffer, uint64_t imageSize) : m_Width(width), m_Height(height), m_Channels(channels), m_ImageType(imageType), m_Image(imageBuffer, imageBuffer + imageSize)
{
	PC_ASSERT(imageSize == width * height * channels, "imageSize({}) == width({}) * height({}) * channels({}) (={})",imageSize,width,height,channels, width*height*channels);
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
	Dirty = true;
	return *this;
}

Image::Image(Image && o) noexcept : m_Width(o.m_Width), m_Height(o.m_Height), m_Channels(o.m_Channels), m_ImageType(o.m_ImageType), m_Image(std::move(o.m_Image))
{
	o.m_Width = {};
	o.m_Height = {};
	o.m_Channels = {};
	o.m_ImageType = {};
	Dirty = true;
	o.Dirty = false;
}

Image &Image::operator=(Image&& o) noexcept {
	std::swap(m_Width, o.m_Width);
	std::swap(m_Height, o.m_Height);
	std::swap(m_Channels, o.m_Channels);
	std::swap(m_ImageType, o.m_ImageType);
	std::swap(m_Image, o.m_Image);
	Dirty = true;
	o.Dirty = true;
	return *this;
}

Image::~Image() = default;


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
	std::swap(m_Image, newImage);
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
	std::swap(m_Image, newImage);
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
		if(imageType!=m_ImageType) {
			PC_ERROR("Conversion from {} to {} not handled yet.", (int)m_ImageType, (int)imageType);
		}
		return in;
	};
	switch(m_ImageType){
		case ModelType::Gray:
			switch(imageType){
				case ModelType::RGB:
					conv = [](std::vector<uint8_t> in) {
						int32_t s = 0;
						for(uint8_t i : in)s+=i;
						s /= in.size();
						in.clear();
						in.push_back(std::clamp(s,0,255));
						in.push_back(std::clamp(s,0,255));
						in.push_back(std::clamp(s,0,255));
						return in;
					};
					break;
				case ModelType::RGBA:
					conv = [](std::vector<uint8_t> in) {
						int32_t s = 0;
						for(uint8_t i : in)s+=i;
						s /= in.size();
						in.clear();
						in.push_back(std::clamp(s,0,255));
						in.push_back(std::clamp(s,0,255));
						in.push_back(std::clamp(s,0,255));
						in.push_back(255);
						return in;
					};
					break;
			}
			break;
		case ModelType::RGB:
			if(imageType==ModelType::Gray){
				conv = [](std::vector<uint8_t> in) {
					int32_t s=0;
					for (auto v : in) {
						s+=v;
					}
					s/= in.size();
					in.clear();
					in.push_back(std::clamp(s,0,255));
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
					int32_t s=0;
					for (auto v : in) {
						s+=v;
					}
					s /= in.size();
					in.clear();
					in.push_back(std::clamp(s,0,255));
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
			PC_ASSERT(pix.size()==m_Channels, "pix.size()({})==m_Channels({})",pix.size(),m_Channels);
			pix=conv(pix);
			uint8_t* ptrTrg = &newPixels[(y * m_Width * targetChannelCount + x * targetChannelCount)];
			std::memcpy(ptrTrg, pix.data(), pix.size() * sizeof(pix[0]));
		}
	}
	m_ImageType=imageType;
	m_Channels=targetChannelCount;
	m_Image=newPixels;
	Dirty = true;
}

void Image::SetImageType(ModelType imageType)
{
	m_ImageType = imageType;
	UpdateImage();
}

void Image::UpdateImage()
{
	m_Image.resize(m_Width * m_Height * m_Channels);
	Dirty = true;
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
	Dirty = true;
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
	Dirty = true;
	return *this;
}

Image &Image::operator-=(const uint8_t rht) {
	for (int x = 0; x < m_Width; ++x) {
		for (int y = 0; y < m_Height; ++y) {
			for (int c = 0; c < m_Channels; ++c) {
				this->add(x,y,c,-(int16_t)rht);
			}
		}
	}
	return *this;
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
	Dirty = true;
	return *this;
}

Image &Image::operator^=(const uint8_t rht) {
	for (int x = 0; x < m_Width; ++x) {
		for (int y = 0; y < m_Height; ++y) {
			for (int c = 0; c < m_Channels; ++c) {
				this->at(x,y,c)=std::abs((int16_t)this->at(x,y,c)-(int16_t)rht);
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
Image Image::lt(uint8_t ceil) const {
    auto cha=m_Channels;
    Image image(m_Width,m_Height,1,ModelType::Gray,255);
    for (int x = 0; x < m_Width; ++x) {
        for (int y = 0; y < m_Height; ++y) {
            bool pass=true;
            int av=0;
            for (int c = 0; c < cha; ++c) {
                uint8_t val;
                val = this->operator()(x, y, c);
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
			image(x,y,0)=pass ? 255 : 0;
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

Buffer Image::GetImageBuffer() {
	return {m_Image.data(), m_Image.size()};
}

TextureSpecification Image::GetTextureSpec() const {
	TextureSpecification spec;
	spec.width = m_Width;
	spec.height = m_Height;
	spec.channels = m_Channels;

	spec.pixelFormat = (PixelFormat)m_Channels;
	spec.pixelType = PixelType::PX_8;

	spec.generateMipMaps = true;

	return spec;
}
