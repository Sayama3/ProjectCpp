//
// Created by Sayama on 05/02/2024.
//

#pragma once

#include <algorithm>
#include <vector>
#include <ostream>
#include <optional>
#include <filesystem>
#include <cmath>
#include <cstring>
#include <cstdint>

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
    void ConvertImageToModelType(ModelType imageType);
    [[nodiscard]] inline float GetRatio() const {return (float)m_Width / (float)m_Height;}
	void Resize(uint32_t width, uint32_t height, uint32_t channels);


	uint8_t& at(uint32_t x, uint32_t y, uint32_t channel);
	[[nodiscard]] const uint8_t& at(uint32_t x, uint32_t y, uint32_t channel) const;

	uint8_t& operator() (uint32_t x, uint32_t y, uint32_t channel);
	const uint8_t& operator() (uint32_t x, uint32_t y, uint32_t channel) const;

    //<

    [[nodiscard]] Image lt (uint8_t ceil) const;
    //>=
    [[nodiscard]] Image ge(uint8_t ceil) const{return ~(~this->lt(Invert(ceil)));}
    //<=
    [[nodiscard]] Image le(uint8_t ceil) const{
        //Ceiling an image with <= over < doesn't make a lot of sense we are not treating boolean values, it means that we also include i.e don't put equal to the ceil value that are already equal to the ceil
        //But in order to have operator with different behaviour we consider ceil+1 cause we dealing with int values
        return this->lt(ceil+1);
    }
    //>
    [[nodiscard]] Image gt (uint8_t ceil) const{
        //Same for > using >= which uses directly <
        return this->ge(ceil+1);
    }
    //==
    [[nodiscard]] Image eq(uint8_t ceil) const{return (this->ge(ceil)).le(ceil);}
    //!=
    [[nodiscard]] Image ne(uint8_t ceil) const{
        //With current logic of setting each value "outside" of the ceil to the ceil, != with a uint8 value returns same picture even if we'd compose it using other operators
        return *this;
    }

    Image& set(uint32_t x, uint32_t y, uint32_t channel,int32_t val);
    Image& add(uint32_t x, uint32_t y, uint32_t channel, int16_t val);


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
    //Ceil with another image, not mandatory
	friend Image operator< (Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator<=(Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator> (Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator>=(Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator==(Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
	friend Image operator!=(Image lft, const Image& rht) {/*TODO: ce qu'il faut faire*/; return lft;}
    static uint8_t Invert (uint8_t lft) {
        return 255-lft;
    }
    friend Image operator~ (Image lft) {
        for (uint8_t & i : lft.m_Image) {
            i = Invert(i);
        }
        return lft;
    }
    //Ceil with value
    friend Image operator< (Image im,uint8_t ceil);
    friend Image operator>=(Image lft, uint8_t ceil) {return ~(lft<ceil);}
    friend Image operator<=(Image lft, uint8_t ceil) {
        return lft<ceil+1;
    }
    friend Image operator> (Image lft, uint8_t ceil) {
        return ~(lft<=ceil);
    }
    //Will act as boolean || because we're deealing with "boolean" images
    friend Image operator!=(Image lft, uint8_t ceil) { return (lft<ceil)+(lft>ceil);}
    friend Image operator==(Image lft, uint8_t ceil) {return ~(lft!=ceil);}





private:
	void UpdateImage();
	void RecreateOpenGLTexture();

	[[nodiscard]] uint32_t GetIndex(uint32_t x, uint32_t y) const;
	[[nodiscard]] uint32_t GetIndex(Vec2UI pos) const;
	[[nodiscard]] Vec2UI GetPosition(uint32_t index) const;
	[[nodiscard]] bool IsInside(uint32_t x, uint32_t y) const;
	[[nodiscard]] bool IsInside(uint32_t x, uint32_t y, uint32_t channel) const;


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