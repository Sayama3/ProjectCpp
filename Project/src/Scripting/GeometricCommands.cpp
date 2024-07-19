//
// Created by ianpo on 19/07/2024.
//

#include "Scripting/GeometricCommands.hpp"
#include <string>
#include <format>

using namespace GeometricTransformation;

namespace Pic {
	// ==================== CropCommand ==================== //
	CropCommand::CropCommand(std::string variableSrc, std::string variableTrg, uint32_t top, uint32_t left, uint32_t bottom, uint32_t right) : variableSource(std::move(variableSrc)), variableTarget(std::move(variableTrg)), top(top), left(left), bottom(bottom), right(right) {}
	Image CropCommand::Execute(const Image& img) {
		return Crop(img, top, left, bottom, right);
	}
	std::regex CropCommand::GetComparer() {
		return std::regex(R"(\s*crop\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}
	bool CropCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}
	Command *CropCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		return new CropCommand(smatch[5], smatch[6], std::stoll(smatch[1]), std::stoll(smatch[2]), std::stoll(smatch[3]), std::stoll(smatch[4]));
	}
	std::string CropCommand::Save(const Command* command) {
		const auto* c = dynamic_cast<const CropCommand*>(command);
		if(!c) return "";
		return std::format("crop {} {} {} {} {} in {}", c->top, c->left, c->bottom, c->right, c->variableSource, c->variableTarget);
	}

	// ==================== TranslateCommand ==================== //
	TranslateCommand::TranslateCommand(std::string variableSrc, std::string variableTrg, uint32_t decalX, uint32_t decalY) : variableSource(std::move(variableSrc)), variableTarget(std::move(variableTrg)), decalX(decalX), decalY(decalY) {}
	Image TranslateCommand::Execute(const Image& img) {
		return Translate(img, decalX, decalY);
	}
	std::regex TranslateCommand::GetComparer() {
		return std::regex(R"(\s*translate\s+(\d+)\s+(\d+)\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}
	bool TranslateCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}
	Command *TranslateCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		return new TranslateCommand(smatch[3], smatch[4], std::stoll(smatch[1]), std::stoll(smatch[2]));
	}
	std::string TranslateCommand::Save(const Command* command) {
		const auto* c = dynamic_cast<const TranslateCommand*>(command);
		if(!c) return "";
		return std::format("translate {} {} {} in {}", c->decalX, c->decalY, c->variableSource, c->variableTarget);
	}

	// ==================== ResizeCommand ==================== //
	ResizeCommand::ResizeCommand(std::string variableSrc, std::string variableTrg, uint32_t newWidth, uint32_t newHeight) : variableSource(std::move(variableSrc)), variableTarget(std::move(variableTrg)), newWidth(newWidth), newHeight(newHeight) {}
	Image ResizeCommand::Execute(const Image& img) {
		return Resize(img, newWidth, newHeight);
	}
	std::regex ResizeCommand::GetComparer() {
		return std::regex(R"(\s*resize\s+(\d+)\s+(\d+)\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}
	bool ResizeCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}
	Command *ResizeCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		return new ResizeCommand(smatch[3], smatch[4], std::stoll(smatch[1]), std::stoll(smatch[2]));
	}
	std::string ResizeCommand::Save(const Command* command) {
		const auto* c = dynamic_cast<const ResizeCommand*>(command);
		if(!c) return "";
		return std::format("resize {} {} {} in {}", c->newWidth, c->newHeight, c->variableSource, c->variableTarget);
	}

	// ==================== ShearCommand ==================== //
	ShearCommand::ShearCommand(std::string variableSrc, std::string variableTrg, uint32_t decalX, uint32_t decalY) : variableSource(std::move(variableSrc)), variableTarget(std::move(variableTrg)), decalX(decalX), decalY(decalY) {}
	Image ShearCommand::Execute(const Image& img) {
		return Shear(img, decalX, decalY);
	}
	std::regex ShearCommand::GetComparer() {
		return std::regex(R"(\s*shear\s+(\d+)\s+(\d+)\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}
	bool ShearCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}
	Command *ShearCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		return new ShearCommand(smatch[3], smatch[4], std::stoll(smatch[1]), std::stoll(smatch[2]));
	}
	std::string ShearCommand::Save(const Command* command) {
		const auto* c = dynamic_cast<const ShearCommand*>(command);
		if(!c) return "";
		return std::format("shear {} {} {} in {}", c->decalX, c->decalY, c->variableSource, c->variableTarget);
	}

	// ==================== RotateCommand ==================== //
	RotateCommand::RotateCommand(std::string variableSrc, std::string variableTrg, float angleDegree, uint32_t centerX, uint32_t centerY) : variableSource(std::move(variableSrc)), variableTarget(std::move(variableTrg)), angleDegree(angleDegree), centerX(centerX), centerY(centerY) {}
	Image RotateCommand::Execute(const Image& img) {
		return Rotate(img, angleDegree, centerX, centerY);
	}
	std::regex RotateCommand::GetComparer() {
		return std::regex(R"(\s*rotate\s+([+-]?(?:(?:\.\d+)|(?:\d+(?:\.\d*)?)))\s+(\d+)\s+(\d+)\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}
	bool RotateCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}
	Command *RotateCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		return new RotateCommand(smatch[4], smatch[5], std::stof(smatch[1]), std::stoll(smatch[2]), std::stoll(smatch[3]));
	}
	std::string RotateCommand::Save(const Command* command) {
		const auto* c = dynamic_cast<const RotateCommand*>(command);
		if(!c) return "";
		return std::format("rotate {} {} {} {} in {}", c->angleDegree, c->centerX,  c->centerY, c->variableSource, c->variableTarget);
	}

	// ==================== RemapCommand ==================== //
	RemapCommand::RemapCommand(std::string variableSrc, std::string variableTrg, std::vector<Vec2UI> remap) : variableSource(std::move(variableSrc)), variableTarget(std::move(variableTrg)), remap(std::move(remap)) {}
	Image RemapCommand::Execute(const Image& img) {
		return Remap(img, remap);
	}
	std::regex RemapCommand::GetComparer() {
		return std::regex(R"(\s*remap\s+\[((?:\d+,\d+,?))+\]\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}
	bool RemapCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}
	Command *RemapCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		std::vector<Vec2UI> coords;
		{
			std::stringstream ss (smatch[1]);
			std::string item;
			Vec2UI coord;
			uint8_t a = 0;
			while (getline (ss, item, ',')) {
				coord[a++] = std::stoll(item);
				if(a > 1) {
					coords.push_back(coord);
					a = 0;
				}
			}
		}
		return new RemapCommand(smatch[2], smatch[3], coords);
	}
	std::string RemapCommand::Save(const Command* command) {
		const auto* c = dynamic_cast<const RemapCommand*>(command);
		if(!c) return "";
		return std::format("remap {} {} in {}", c->ArrayToString(), c->variableSource, c->variableTarget);
	}
	std::string RemapCommand::ArrayToString() const
	{
		std::string result = "[";
		for (auto pos : remap) {
			result += std::format("{},{},", pos.x, pos.y);
		}
		result.back() = ']';
		return std::move(result);
	}
}// namespace Pic