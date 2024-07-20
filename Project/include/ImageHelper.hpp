//
// Created by ianpo on 20/07/2024.
//

#pragma once

#include "Image.hpp"
#include "OpenGL/Texture.hpp"

class TextureHelper
{
public:
	static Texture ImageToTexture(const Image& image);
private:
	static Texture GetGreyTexture(const Image& image);
	static Texture GetUsualTexture(const Image& image);
};
