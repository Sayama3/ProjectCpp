//
// Created by Sayama on 05/02/2024.
//

#pragma once

#include <cmath>
#include <cstdint>
#include <vector>
#include <ostream>
#include <optional>
#include <filesystem>

struct Vec2UI
{
	uint32_t x;
	uint32_t y;
};

enum class ModelType
{
	None = 0,
	Gray,
	RGB,
	RGBA,
	ARGB,
	CMJN,
	HSL,
	HSLA,
};



namespace ImageHelper
{
	inline std::vector<std::string> GetImageTypeNames()
	{
		return {
			"None",
			"Gray",
			"RGB",
			"RGBA",
			"ARGB",
			"CMJN",
			"HSL",
			"HSLA",
		};
	}

	inline std::string GetImageTypeName(ModelType mt)
	{
		switch(mt)
		{

			case ModelType::None: return "None";
			case ModelType::Gray: return "Gray";
			case ModelType::RGB: return "RGB";
			case ModelType::RGBA: return "RGBA";
			case ModelType::ARGB: return "ARGB";
			case ModelType::CMJN: return "CMJN";
			case ModelType::HSL: return "HSL";
			case ModelType::HSLA: return "HSLA";
			default: return "Unknown";
		}
	}

	inline uint32_t GetModelTypeChannelCount(ModelType mt)
	{
		switch (mt) {
			case ModelType::None:
				return 0;
				break;
			case ModelType::Gray:
				return 1;
				break;
			case ModelType::RGB:
				return 3;
				break;
			case ModelType::RGBA:
				return 4;
				break;
			case ModelType::ARGB:
				return 4;
				break;
			case ModelType::CMJN:
				return 3;
				break;
			case ModelType::HSL:
				return 3;
				break;
			case ModelType::HSLA:
				return 4;
				break;
		}
		return 0;
	}
}

class Image {
public:
	// Constructors
	Image();
	Image(uint32_t width, uint32_t height, uint32_t channels, ModelType imageType, uint8_t value);
	Image(const std::filesystem::path& path);
	Image(uint32_t width, uint32_t height, uint32_t channels, ModelType imageType, const std::vector<uint8_t>& image);
	Image(uint32_t width, uint32_t height, uint32_t channels, ModelType imageType, const uint8_t* imageBuffer, uint64_t imageSize);
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
	[[nodiscard]] ModelType GetImageType() const;
	void SetImageType(ModelType imageType);
	[[nodiscard]] inline float GetRatio() const {return (float)m_Width / (float)m_Height;}

	uint8_t& at(uint32_t x, uint32_t y, uint32_t channel);
	[[nodiscard]] const uint8_t& at(uint32_t x, uint32_t y, uint32_t channel) const;

	uint8_t& operator() (uint32_t x, uint32_t y, uint32_t channel);
	const uint8_t& operator() (uint32_t x, uint32_t y, uint32_t channel) const;

	void CreateOpenGLTexture();
	void DeleteOpenGLTexture();
	void UpdateOpenGLTexture();
	bool HasOpenGLTexture() const;
	std::optional<uint32_t> GetRenderId() const;
public:
	/*
	- l’addition avec une autre image (via + et +=) : on additionne les valeurs des pixels correspondants
	- l’addition avec une valeur (via + et +=): on additionne la valeur à chaque canal de chaque pixel
	- l’addition avec un pixel (tableau de valeurs) (via + et +=) : on additionne les valeurs du pixel a chaque pixel
	- la soustraction avec une autre image (via - et -=)
	- la soustraction avec une valeur(via - et -=)
	- la soustraction avec un pixel (via - et -=)
	- la différence avec une autre image (via ^ et ^=)
	- la différence avec une valeur (via ^ et ^=)
	- la différence avec un pixel (via ^ et ^=)
	- la multiplication par une valeur réelle (via * et *=)
	- la division par une valeur réelle (via / et /=)
	- le seuillage par une valeur (via <, <=, >, >=, ==, !=) : le résultat sera une image de même taille, avec un
			seul canal en mode “GRAY”, avec les valeurs 0 ou 255
	- l’inversement des valeurs (via l’opération unaire ~), le résultat est une image de même taille, ou toutes les
	valeurs sont (255-valeur d’origine)
	 */
	Image& operator+=(const Image& rht);
	friend Image operator+(Image lft, const Image& rht) {lft += rht; return lft;}

	Image& operator+=(const uint8_t rht);
	friend Image operator+(Image lft, const uint8_t rht) {lft += rht; return lft;}

	Image& operator+=(const std::vector<uint8_t>& rht);
	friend Image operator+(Image lft, const std::vector<uint8_t>& rht) {lft += rht; return lft;}

	Image& operator-=(const Image& rht);
	friend Image operator-(Image lft, const Image& rht) {lft -= rht; return lft;}

	Image& operator-=(const uint8_t rht);
	friend Image operator-(Image lft, const uint8_t rht) {lft -= rht; return lft;}

	Image& operator-=(const std::vector<uint8_t>& rht);
	friend Image operator-(Image lft, const std::vector<uint8_t>& rht) {lft -= rht; return lft;}

	Image& operator^=(const Image& rht);
	friend Image operator^(Image lft, const Image& rht) {lft ^= rht; return lft;}

	Image& operator^=(const uint8_t rht);
	friend Image operator^(Image lft, const uint8_t rht) {lft ^= rht; return lft;}

	Image& operator^=(const std::vector<uint8_t>& rht);
	friend Image operator^(Image lft, const std::vector<uint8_t>& rht) {lft ^= rht; return lft;}

	Image& operator*=(float rht);
	friend Image operator*(Image lft, float rht) {lft *= rht; return lft;}

	Image& operator/=(float rht);
	friend Image operator/(Image lft, float rht) {lft /= rht; return lft;}

	friend Image operator< (Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator<=(Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator> (Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator>=(Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator==(Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator!=(Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator~ (Image lft) {
		for (uint8_t & i : lft.m_Image) {
			i = 255 - i;
		}
		return lft;
	}

private:
	void UpdateImage();
	void RecreateOpenGLTexture();

	[[nodiscard]] uint32_t GetIndex(uint32_t x, uint32_t y) const;
	[[nodiscard]] uint32_t GetIndex(Vec2UI pos) const;
	[[nodiscard]] Vec2UI GetPosition(uint32_t index) const;

	uint32_t m_Width;
	uint32_t m_Height;
	uint32_t m_Channels;
	ModelType m_ImageType;
	std::vector<uint8_t> m_Image;
	std::optional<uint32_t> m_RenderId;
};

inline std::ostream& operator<<(std::ostream& os, const Image& img)
{
	os << img.GetWidth() << "x" << img.GetHeight() << "x" << img.GetChannels() << "(" << (uint32_t)img.GetImageType() << ")";
	return os;
}