//
// Created by ianpo on 06/07/2024.
//

#include "Scripting/Commands.hpp"
#include <stb_image_write.h>

namespace Pic {
	LoadCommand::LoadCommand(std::filesystem::path path, std::string variable) : source(std::move(path)), variableStore(std::move(variable)) {
	}

	Image LoadCommand::Execute(const Image& img) {
		return Image(source);
	}

	std::regex LoadCommand::GetComparer() {
		return std::regex(R"(\s*load\s+([\w\.\\\/\:]+)\s+([\w]+)\s*)", std::regex_constants::icase);
	}

	bool LoadCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}

	Command *LoadCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		std::string path = smatch[1];
		std::string variable = smatch[2];
		return new LoadCommand(path, variable);
	}

	std::string LoadCommand::Save(const Command *command) {
		const LoadCommand* load = dynamic_cast<const LoadCommand*>(command);
		if(!load) return "";
		return std::format("load {} {}", load->source.string(), load->variableStore);
	}

	SaveCommand::SaveCommand(std::string variable, std::filesystem::path path) : variableSource(std::move(variable)), pathTarget(std::move(path)) {
	}

	Image SaveCommand::Execute(const Image& img) {
		auto path = this->pathTarget.string();
		stbi_write_png(path.c_str(), img.GetWidth(), img.GetHeight(), img.GetChannels(), &img(0,0,0), img.GetWidth() * img.GetChannels());
		return std::move(img);
	}

	std::regex SaveCommand::GetComparer() {
		return std::regex(R"(\s*save\s+([\w]+)\s+([\w\.\\\/\:]+)\s*)", std::regex_constants::icase);
	}

	bool SaveCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}

	Command *SaveCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		std::string variable = smatch[1];
		std::string path = smatch[2];
		return new SaveCommand(path, variable);
	}

	std::string SaveCommand::Save(const Command *command) {
		const SaveCommand* save = dynamic_cast<const SaveCommand*>(command);
		if(!save) return "";
		return std::format("save {} {}", save->variableSource, save->pathTarget.string());
	}


	ConvertCommand::ConvertCommand(std::string variableSource, std::string variableTarget, ModelType conversionModel) : variableSource(std::move(variableSource)), variableTarget(std::move(variableTarget)), conversionModel(conversionModel) {
	}

	Image ConvertCommand::Execute(const Image& img) {
		Image result(img);
		result.ConvertImageToModelType(conversionModel);
		return std::move(result);
	}

	std::regex ConvertCommand::GetComparer() {
		return std::regex(R"(\s*convert\s+in\s+(Gray|Grey|RGB|RGBA|ARGB|CMJN|HSL|HSLA)\s+(\w+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}

	bool ConvertCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}

	Command *ConvertCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		ModelType target = ImageHelper::GetImageTypeFromName(smatch[1]);
		std::string variableSrc = smatch[2];
		std::string variableTrg = smatch[3];
		return new ConvertCommand(variableSrc, variableTrg, target);
	}

	std::string ConvertCommand::Save(const Command *command) {
		const ConvertCommand* convert = dynamic_cast<const ConvertCommand*>(command);
		if(!convert) return "";
		return std::format("convert in {} {} in {}", ImageHelper::GetImageTypeName(convert->conversionModel), convert->variableSource, convert->variableTarget);
	}

	ThresholdCommand::ThresholdCommand(std::string variableSource, std::string variableTarget, int64_t threshold) : variableSource(std::move(variableSource)), variableTarget(std::move(variableTarget)), threshold(threshold) {
	}

	Image ThresholdCommand::Execute(const Image& image) {
		Image img(image);
		img.SetWidth(img.GetWidth() + threshold);
		img.SetHeight(img.GetHeight() + threshold);
		return std::move(img);
	}

	std::regex ThresholdCommand::GetComparer() {
		return std::regex(R"(\s*threshold\s+(\w+)\s+to\s+([+-]?\d+)\s+in\s+(\w+)\s*)", std::regex_constants::icase);
	}

	bool ThresholdCommand::Compare(const std::string &content) {
		return std::regex_search(content, GetComparer());
	}

	Command *ThresholdCommand::Create(const std::string &content) {
		std::smatch smatch;
		if(!std::regex_search(content, smatch, GetComparer())) return nullptr;
		std::string variableSrc = smatch[1];
		int64_t threshold = std::stoll(smatch[2]);
		std::string variableTrg = smatch[3];
		return new ThresholdCommand(variableSrc, variableTrg, threshold);
	}

	std::string ThresholdCommand::Save(const Command *command) {
		const ThresholdCommand* threshold = dynamic_cast<const ThresholdCommand*>(command);
		if(!threshold) return "";
		return std::format("threshold {} to {} in {}", threshold->variableSource, threshold->threshold, threshold->variableTarget);
	}

	Command *CommandHelper::GetCommand(const std::vector<CommandCreator>& commands, const std::string &str) {
		for(auto& [checker, loader, saver] : commands)
		{
			if(!loader) continue;
			auto* command = loader(str);
			if(command) return command;
		}
		return nullptr;
	}
}
