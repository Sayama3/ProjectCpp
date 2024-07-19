//
// Created by ianpo on 19/07/2024.
//

#include "Scripting/GeometricCommands.hpp"
#include <string>
#include <format>

using namespace GeometricTransformation;

namespace Pic {
	// ==================== FlipHorizontalCommand ==================== //
	FlipHorizontalCommand::FlipHorizontalCommand(std::string varSource, std::string varTarget) : variableSource(std::move(varSource)), variableTarget(std::move(varTarget)) {}
	Image FlipHorizontalCommand::Execute(Image img) {
		img = std::move(FlipHorizontal(img));
		return std::move(img);
	}
	std::regex FlipHorizontalCommand::GetComparer() {
		return std::regex(R"(\s*(?:(?:flip\s+horizontal)|(?:fliph))\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}
	bool FlipHorizontalCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}
	Command *FlipHorizontalCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		return new FlipHorizontalCommand(smatch[1], smatch[2]);
	}
	std::string FlipHorizontalCommand::Save(const Command* command) {
		const auto* c = dynamic_cast<const FlipHorizontalCommand*>(command);
		if(!c) return "";
		return std::format("flip horizontal {} in {}", c->variableSource, c->variableTarget);
	}

	// ==================== FlipVerticalCommand ==================== //
	FlipVerticalCommand::FlipVerticalCommand(std::string varSource, std::string varTarget) : variableSource(std::move(varSource)), variableTarget(std::move(varTarget)) {}
	Image FlipVerticalCommand::Execute(Image img) {
		img = std::move(FlipVertical(img));
		return std::move(img);
	}
	std::regex FlipVerticalCommand::GetComparer() {
		return std::regex(R"(\s*(?:(?:flip\s+vertical)|(?:flipv))\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}
	bool FlipVerticalCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}
	Command *FlipVerticalCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		return new FlipVerticalCommand(smatch[1], smatch[2]);
	}
	std::string FlipVerticalCommand::Save(const Command* command) {
		const auto* c = dynamic_cast<const FlipVerticalCommand*>(command);
		if(!c) return "";
		return std::format("flip vertical {} in {}", c->variableSource, c->variableTarget);
	}

	// ==================== Rotate90Command ==================== //
	Rotate90Command::Rotate90Command(std::string varSource, std::string varTarget) : variableSource(std::move(varSource)), variableTarget(std::move(varTarget)) {}
	Image Rotate90Command::Execute(Image img) {
		img = std::move(Rotate90(img));
		return std::move(img);
	}
	std::regex Rotate90Command::GetComparer() {
		return std::regex(R"(\s*rotate90\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}
	bool Rotate90Command::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}
	Command *Rotate90Command::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		return new Rotate90Command(smatch[1], smatch[2]);
	}
	std::string Rotate90Command::Save(const Command* command) {
		const auto* c = dynamic_cast<const Rotate90Command*>(command);
		if(!c) return "";
		return std::format("rotate90 {} in {}", c->variableSource, c->variableTarget);
	}

	// ==================== CropCommand ==================== //
	CropCommand::CropCommand(std::string variableSrc, std::string variableTrg, uint32_t top, uint32_t left, uint32_t bottom, uint32_t right) : variableSource(std::move(variableSrc)), variableTarget(std::move(variableTrg)), top(top), left(left), bottom(bottom), right(right) {}
	Image CropCommand::Execute(Image img) {
		img = std::move(Crop(img, top, left, bottom, right));
		return std::move(img);
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
	Image TranslateCommand::Execute(Image img) {
		img = std::move(Translate(img, decalX, decalY));
		return std::move(img);
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
	Image ResizeCommand::Execute(Image img) {
		img = std::move(Resize(img, newWidth, newHeight));
		return std::move(img);
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
	Image ShearCommand::Execute(Image img) {
		img = std::move(Shear(img, decalX, decalY));
		return std::move(img);
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
	Image RotateCommand::Execute(Image img) {
		img = std::move(Rotate(img, angleDegree, centerX, centerY));
		return std::move(img);
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
	Image RemapCommand::Execute(Image img) {
		img = std::move(Remap(img, remap));
		return std::move(img);
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

	// ==================== ZoomCommand ==================== //
	ZoomCommand::ZoomCommand(std::string variableSrc, std::string variableTrg, float factor) : variableSource(std::move(variableSrc)), variableTarget(std::move(variableTrg)), newWidth(newWidth), newHeight(newHeight) {}
	Image ZoomCommand::Execute(Image img) {
		img = std::move(Zoom(img, factor));
		return std::move(img);
	}
	std::regex ZoomCommand::GetComparer() {
		return std::regex(R"(\s*zoom\s+([+-]?(?:(?:\.\d+)|(?:\d+(?:\.\d*)?)))\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}
	bool ZoomCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}
	Command* ZoomCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		return new ZoomCommand(smatch[2], smatch[3], std::stof(smatch[1]));
	}
	std::string ZoomCommand::Save(const Command* command) {
		const auto* c = dynamic_cast<const ZoomCommand*>(command);
		if(!c) return "";
		return std::format("zoom {} {} in {}", c->factor, c->variableSource, c->variableTarget);
	}
}// namespace Pic