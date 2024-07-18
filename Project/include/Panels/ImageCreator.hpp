//
// Created by ianpo on 18/07/2024.
//

#pragma once

#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <unordered_map>

#include "Image.hpp"
#include "Core/Macro.hpp"
#include "Core/Logger.hpp"
#include "Core/Profiler.hpp"
#include "Core/Application.hpp"
#include "OpenGL/Texture.hpp"

namespace PC {

	struct ImageValueData
	{
		uint32_t x = 0;
		uint32_t y = 0;
		uint32_t channel = 0;
		ModelType target = ModelType::None;
		float sizeMultiplier = 1.0f;
		uint8_t* value = nullptr;
	};

	class ImageCreator {
	public:
		ImageCreator();
		~ImageCreator();
	public:
		void Update();
		void PostUpdate();
	public:
		std::string path = R"(D:\Data\Projects\Unity\ProjectCpp\Project\Data\seminaire.png)";
	private:
		const uint32_t uMin = 0;
		const uint32_t uMax = UINT32_MAX;
		const uint32_t maxChannel = 4;

		std::vector<std::string> imageTypeNames = ImageHelper::GetImageTypeNames();
		std::unordered_map<uint64_t, ImageValueData> imagesValues;
		std::unordered_map<uint64_t, Texture> imagesTexture;
		std::vector<Image*> images;
	};

}// namespace PC
