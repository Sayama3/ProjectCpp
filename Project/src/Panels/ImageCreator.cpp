//
// Created by ianpo on 18/07/2024.
//

#include "Panels/ImageCreator.hpp"
#include "Panels/ImageCreator.hpp"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <portable-file-dialogs.h>
#include <stb_image_write.h>

namespace PC {
	void ImageCreator::Update()
	{
		ImGui::Begin("Image Creator");
		{

			if (ImGui::CollapsingHeader("Create Default Image")) {
				if (ImGui::Button("Create")) {
					Image* im=new Image(path);
					images.push_back(im);
					imagesTexture[images.size()-1] = {im->GetTextureSpec(), im->GetImageBuffer()};
				}
			}

			if (ImGui::CollapsingHeader("Create Image with value"))
			{
				static uint32_t width = 255;
				static uint32_t height = 255;
				static uint32_t channels = 4;
				static int type = 4;
				static uint8_t value = 255;
				ImGui::DragScalar("Width", ImGuiDataType_U32, &width, 1, &uMin, &uMax, "%d");
				ImGui::DragScalar("Height", ImGuiDataType_U32, &height, 1, &uMin, &uMax, "%d");
				ImGui::DragScalar("Channels", ImGuiDataType_U32, &channels, 1, &uMin, &maxChannel,"%d");
				if (ImGui::BeginCombo("Image Type", imageTypeNames[type].c_str())) {
					for (int i = 0; i < imageTypeNames.size(); i++) {
						const bool is_selected = (type == i);
						if (ImGui::Selectable(imageTypeNames[i].c_str(), is_selected)) {
							type = i;
						}

						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (is_selected) ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
				ImGui::DragScalar("Value", ImGuiDataType_U8, &value, 1, nullptr, nullptr, "%d");

				if(ImGui::Button("Create"))
				{
					images.push_back(new Image(width, height, channels, (ModelType)type, value));
				}
			}

			if (ImGui::CollapsingHeader("Create Image with path"))
			{
				if(ImGui::Button("Choose Image"))
				{
					auto result = pfd::open_file("Select a file", "", {"Image Files (*.pgn, *.jpg)", "*"}, pfd::opt::multiselect);
					auto results = result.result();
					if(!results.empty())
					{
						for(const auto& path : results)
						{
							images.push_back(new Image(path));
						}
					}
				}
			}

			if (ImGui::CollapsingHeader("Create Image from other image"))
			{
				ImGui::BeginDisabled(images.empty());
				{
					static uint64_t indexImage = 0;
					indexImage = std::min(indexImage, (uint64_t)images.size() - 1);
					std::string currentImage = "Image " + std::to_string(indexImage);
					if (ImGui::BeginCombo("Image", currentImage.c_str())) {
						for (int i = 0; i < images.size(); i++) {
							if(images[i] == nullptr) continue;
							const bool is_selected = (indexImage == i);
							std::string iImage = "Image " + std::to_string(i);
							if (ImGui::Selectable(iImage.c_str(), is_selected)) {
								indexImage = i;
							}

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected) ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					ImGui::BeginDisabled(images[indexImage] == nullptr);
					if(ImGui::Button("Duplicate"))
					{
						images.push_back(new Image(*images[indexImage]));
					}
					ImGui::EndDisabled();
				}
				ImGui::EndDisabled();
			}

			if (ImGui::CollapsingHeader("Assign Image to another one"))
			{
				ImGui::BeginDisabled(images.size() < 1);
				{
					static uint64_t sourceImage = 0;
					sourceImage = std::min(sourceImage, (uint64_t)images.size() - 1);
					sourceImage = std::min(sourceImage, (uint64_t)images.size() - 1);
					std::string currentSourceImage = "Image " + std::to_string(sourceImage);
					if (ImGui::BeginCombo("Source Image", currentSourceImage.c_str())) {
						for (int i = 0; i < images.size(); i++) {
							if(images[i] == nullptr) continue;
							const bool is_selected = (sourceImage == i);
							std::string iImage = "Image " + std::to_string(i);
							if (ImGui::Selectable(iImage.c_str(), is_selected)) {
								sourceImage = i;
							}

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected) ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					static uint64_t targetImage = 0;
					targetImage = std::min(targetImage, (uint64_t)images.size() - 1);
					std::string currentTargetImage = "Image " + std::to_string(targetImage);
					if (ImGui::BeginCombo("Target Image", currentTargetImage.c_str())) {
						for (int i = 0; i < images.size(); i++) {
							if(images[i] == nullptr) continue;
							const bool is_selected = (targetImage == i);
							std::string iImage = "Image " + std::to_string(i);
							if (ImGui::Selectable(iImage.c_str(), is_selected)) {
								targetImage = i;
							}

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected) ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					ImGui::BeginDisabled(images[targetImage] == nullptr || images[sourceImage] == nullptr || targetImage == sourceImage);
					if(ImGui::Button("Assign"))
					{
						images[targetImage] = images[sourceImage];
					}
					ImGui::EndDisabled();
				}
				ImGui::EndDisabled();
			}

			if(ImGui::CollapsingHeader("Operators"))
			{
				ImGui::BeginDisabled(images.empty());
				{
					static uint64_t leftImage = 0;
					leftImage = std::min(leftImage, (uint64_t)images.size() - 1);
					std::string currentSourceImage = "Image " + std::to_string(leftImage);
					if (ImGui::BeginCombo("Left Image", currentSourceImage.c_str())) {
						for (int i = 0; i < images.size(); i++) {
							if(images[i] == nullptr) continue;
							const bool is_selected = (leftImage == i);
							std::string iImage = "Image " + std::to_string(i);
							if (ImGui::Selectable(iImage.c_str(), is_selected)) {
								leftImage = i;
							}

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected) ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					static uint64_t rightImage = 0;
					rightImage = std::min(rightImage, (uint64_t)images.size() - 1);
					std::string currentTargetImage = "Image " + std::to_string(rightImage);
					if (ImGui::BeginCombo("Right Image", currentTargetImage.c_str())) {
						for (int i = 0; i < images.size(); i++) {
							if(images[i] == nullptr) continue;
							const bool is_selected = (rightImage == i);
							std::string iImage = "Image " + std::to_string(i);
							if (ImGui::Selectable(iImage.c_str(), is_selected)) {
								rightImage = i;
							}

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected) ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					static uint8_t operatorChannel = 0;
					ImGui::DragScalar("u8 Value", ImGuiDataType_U8, &operatorChannel, 1, nullptr, nullptr, "%d");

					static float operatorReal = 0;
					ImGui::DragFloat("Real Value", &operatorReal, 0.005);

					static std::vector<uint8_t> operatorPixels = {};
					if(ImGui::CollapsingHeader("pixels"))
					{
						static uint8_t value = 128;
						if(ImGui::Button("+"))
						{
							operatorPixels.push_back(value);
						}
						ImGui::SameLine();
						ImGui::DragScalar("##ValueForVectorOperator", ImGuiDataType_U8, &value, 1, nullptr, nullptr, "%d");
						ImGui::Separator();
						int index = 0;
						for (auto it = operatorPixels.begin(); it != operatorPixels.end();)
						{
							ImGui::PushID(&*it);
							std::string label = std::to_string(index);
							ImGui::Text("%s :", label.c_str());
							ImGui::SameLine();
							ImGui::DragScalar("", ImGuiDataType_U8, &*it, 1, nullptr, nullptr, "%d");
							ImGui::SameLine();

							if(ImGui::Button("-"))
							{
								it = operatorPixels.erase(it);
							}
							else
							{
								++it;
								++index;
							}
							ImGui::PopID();
						}
					}

					ImGui::Separator();

					ImGui::BeginDisabled(images[leftImage] == nullptr);
					{
						ImGui::BeginDisabled(images[rightImage] == nullptr);
						if (ImGui::Button("operator+ (Image lft, const Image& rht)")) {
							Image img = *images[leftImage] + *images[rightImage];
							images.push_back(new Image(img));
						}
						ImGui::EndDisabled();//images[rightImage] == nullptr
						if (ImGui::Button("operator+ (Image lft, const uint8_t rht);")) {
							Image img = *images[leftImage] + operatorChannel;
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator+ (Image lft, const std::vector<uint8_t>& rht);")) {
							Image img = *images[leftImage] + operatorPixels;
							images.push_back(new Image(img));
						}
						ImGui::BeginDisabled(images[rightImage] == nullptr);
						if (ImGui::Button("operator- (Image lft, const Image& rht);")) {
							Image img = *images[leftImage] - *images[rightImage];
							images.push_back(new Image(img));
						}
						ImGui::EndDisabled();//images[rightImage] == nullptr
						if (ImGui::Button("operator- (Image lft, const uint8_t rht);")) {
							Image img = *images[leftImage] - operatorChannel;
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator- (Image lft, const std::vector<uint8_t>& rht);")) {
							Image img = *images[leftImage] - operatorPixels;
							images.push_back(new Image(img));
						}
						ImGui::BeginDisabled(images[rightImage] == nullptr);
						if (ImGui::Button("operator^ (Image lft, const Image& rht);")) {
							Image img = *images[leftImage] ^ *images[rightImage];
							images.push_back(new Image(img));
						}
						ImGui::EndDisabled();//images[rightImage] == nullptr
						if (ImGui::Button("operator^ (Image lft, const uint8_t rht);")) {
							Image img = *images[leftImage] ^ operatorChannel;
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator^ (Image lft, const std::vector<uint8_t>& rht);")) {
							Image img = *images[leftImage] ^ operatorPixels;
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator* (Image lft, float rht);")) {
							Image img = *images[leftImage] * operatorReal;
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator/ (Image lft, float rht);")) {
							Image img = *images[leftImage] / operatorReal;
							images.push_back(new Image(img));
						}

						ImGui::Separator();
						ImGui::PushID("BooleanOperator");
						ImGui::Text("Boolean ceil as requested");
						if (ImGui::Button("operator< ")) {
							Image img = *images[leftImage] < operatorChannel;
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator<=")) {
							Image img = *images[leftImage] <= operatorChannel;
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator> ")) {
							Image img = *images[leftImage] > operatorChannel;
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator>=")) {
							Image img = *images[leftImage] >= operatorChannel;
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator==")) {
							Image img = *images[leftImage] == operatorChannel;
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator!=")) {
							Image img = *images[leftImage] != operatorChannel;
							images.push_back(new Image(img));
						}
						ImGui::PopID();

						ImGui::Separator();
						ImGui::PushID("PixelOperator");
						ImGui::Text("Pixel value ceil, bonus");
						if (ImGui::Button("operator< ")) {
							Image img = images[leftImage]->lt(operatorChannel);
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator<=")) {
							Image img = images[leftImage]->le(operatorChannel);
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator> ")) {
							Image img = images[leftImage]->gt(operatorChannel);
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator>=")) {
							Image img = images[leftImage]->ge(operatorChannel);
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator==")) {
							Image img = images[leftImage]->eq(operatorChannel);
							images.push_back(new Image(img));
						}
						if (ImGui::Button("operator!=")) {
							Image img = images[leftImage]->ne(operatorChannel);
							images.push_back(new Image(img));
						}
						ImGui::PopID();
						/*ImGui::Text("With images, experimental");
							ImGui::BeginDisabled(images[rightImage] == nullptr);
							if (ImGui::Button("operator < IMG ")) {
								Image img = *images[leftImage] < *images[rightImage];
								images.push_back(new Image(img));
							}
							if (ImGui::Button("operator <= IMG ")) {
								Image img = *images[leftImage] <= *images[rightImage];
								images.push_back(new Image(img));
							}
							if (ImGui::Button("operator > IMG  ")) {
								Image img = *images[leftImage] > *images[rightImage];
								images.push_back(new Image(img));
							}
							if (ImGui::Button("operator >= IMG ")) {
								Image img = *images[leftImage] >= *images[rightImage];
								images.push_back(new Image(img));
							}
							if (ImGui::Button("operator == IMG ")) {
								Image img = *images[leftImage] == *images[rightImage];
								images.push_back(new Image(img));
							}
							if (ImGui::Button("operator != IMG ")) {
								Image img = *images[leftImage] != *images[rightImage];
								images.push_back(new Image(img));
							}
							ImGui::EndDisabled();
							 */
						if (ImGui::Button("operator~ ")) {
							Image img = ~*images[leftImage];
							images.push_back(new Image(img));
						}
						ImGui::EndDisabled();
					}
					ImGui::EndDisabled();
				}
			}

			ImGui::End();
		}
	}
	void ImageCreator::PostUpdate() {
		for (int index = 0; index < images.size(); ++index)
		{
			Image* imagePtr = images[index];
			if(imagePtr == nullptr) continue;
			Image& img = *imagePtr;

			std::string imageName = std::string("Image ").append(std::to_string(index));
			bool open = true;
			ImGuiWindowFlags_ flags = ImGuiWindowFlags_AlwaysVerticalScrollbar;
			ImGui::Begin(imageName.c_str(), &open, flags);
			{
				const uint32_t uMin = 0;
				const uint32_t uMax = UINT32_MAX;
				const uint32_t maxChannel = 4;

				if(ImGui::CollapsingHeader("Image Parameters")) {
					uint32_t width = img.GetWidth();
					uint32_t height = img.GetHeight();
					uint32_t channels = img.GetChannels();
					int type = (int) img.GetImageType();

					if (ImGui::DragScalar("Width", ImGuiDataType_U32, &width, 1, &uMin, &uMax, "%d")) {
						img.SetWidth(width);
					}
					if (ImGui::DragScalar("Height", ImGuiDataType_U32, &height, 1, &uMin, &uMax, "%d")) {
						img.SetHeight(height);
					}
					if (ImGui::DragScalar("Channels", ImGuiDataType_U32, &channels, 1, &uMin, &maxChannel, "%d")) {
						img.SetChannels(channels);
					}

					if (ImGui::BeginCombo("Image Type", imageTypeNames[type].c_str())) {
						for (int i = 0; i < imageTypeNames.size(); ++i) {
							const bool is_selected = (type == i);
							if (ImGui::Selectable(imageTypeNames[i].c_str(), is_selected)) {
								type = i;
								img.SetImageType((ModelType) type);
							}

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected) ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}
				}

				if(ImGui::CollapsingHeader("Converter"))
				{

					if (ImGui::BeginCombo("Conversion Type", imageTypeNames[(int)imagesValues[index].target].c_str())) {
						for (int i = 0; i < imageTypeNames.size(); ++i) {
							const bool is_selected = ((int)imagesValues[i].target == i);
							if (ImGui::Selectable(imageTypeNames[i].c_str(), is_selected)) {
								imagesValues[index].target = (ModelType)i;
							}

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected) ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}

					if(ImGui::Button("Convert Image"))
					{
						img.ConvertImageToModelType(imagesValues[index].target);
					}
				}

				if(ImGui::CollapsingHeader("Image Values")) {
					ImageValueData& imgValueData = imagesValues[index];
					ImGui::DragScalar("X", ImGuiDataType_U32, &imgValueData.x, 1, nullptr, nullptr, "%d");
					ImGui::DragScalar("Y", ImGuiDataType_U32, &imgValueData.y, 1, nullptr, nullptr, "%d");
					ImGui::DragScalar("Channel", ImGuiDataType_U32, &imgValueData.channel, 1, nullptr, nullptr, "%d");

					if (ImGui::Button("at(x,y,channel)")) {
						try {
							imagesValues[index].value = &img.at(imgValueData.x, imgValueData.y, imgValueData.channel);
						} catch (std::exception& e) {
							PC_CRITICAL("std::exception: {}", e.what());
						}
					}

					if (ImGui::Button("operator()(x,y,channel)")) {
						imagesValues[index].value = &img(imgValueData.x, imgValueData.y, imgValueData.channel);
					}

					if (ImGui::Button("Reset Value")) {
						imagesValues[index].value = nullptr;
					}

					if (imagesValues.contains(index) && imagesValues[index].value) {
						img.Dirty |= ImGui::DragScalar("Value", ImGuiDataType_U8, imagesValues[index].value, 1, nullptr, nullptr, "%d");
					}
				}

				if(ImGui::CollapsingHeader("Image")) {
					if(ImGui::Button("Update Image")) {
						imagesTexture[index] = {img.GetTextureSpec(), img.GetImageBuffer()};
					}
					if(img.Dirty) {
						imagesTexture[index] = {img.GetTextureSpec(), img.GetImageBuffer()};
						img.Dirty = false;
					}
					ImGui::SliderFloat("Image Size", &imagesValues[index].sizeMultiplier, 0.01f, 1.00f, "%.2f");
					auto size = ImGui::GetContentRegionAvail();
					size.x *= imagesValues[index].sizeMultiplier;
					size.y *= imagesValues[index].sizeMultiplier;

					size.y = size.x / img.GetRatio();
					ImGui::Image((void *) (intptr_t) imagesTexture[index].GetRenderID(), size);
				}

				if (ImGui::Button("Duplicate"))
				{
					images.push_back(new Image(img));
					imagesTexture[images.size() - 1] = {images.back()->GetTextureSpec(), images.back()->GetImageBuffer()};
				}

				if (ImGui::Button("Save"))
				{
					std::string saveName = "Save " + imageName;
					auto sf = pfd::save_file(saveName, "", {"Image (*.png)", "*.png"});
					std::string res = sf.result();
					if(!res.empty())
					{
						if(!res.ends_with(".png"))
						{
							res.append(".png");
						}
						stbi_write_png(res.c_str(), img.GetWidth(), img.GetHeight(), img.GetChannels(), &img(0,0,0), img.GetWidth() * img.GetChannels());
					}
				}
				ImGui::End();
			}

			if(!open)
			{
				delete imagePtr;
				images[index] = nullptr;
				imagesValues[index].value = nullptr;
				imagesTexture.erase(index);
			}
		}
	}
	ImageCreator::ImageCreator() {
		auto im = new Image(path);
		images.push_back(im);
		imagesTexture[images.size() - 1] = {im->GetTextureSpec(), im->GetImageBuffer()};
	}
	ImageCreator::~ImageCreator() {
		// Delete all the image to avoid memory leaks
		for (auto& image : images) {
			delete image;
		}
	}
}// namespace PC