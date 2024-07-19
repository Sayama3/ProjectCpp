//
// Created by ianpo on 06/07/2024.
//

#pragma once

#include <string>
#include <variant>
#include <vector>
#include <optional>
#include <memory>
#include <map>
#include <set>
#include <regex>
#include <utility>
#include <unordered_map>
#include <functional>
#include "OpenGL/Texture.hpp"
#include "Image.hpp"

//TODO: Implement a Command Pattern to describe and represent the change of the Image as we interact with it.

namespace Pic {
	class Command {
	public:
		virtual ~Command() = default;
		virtual bool HasSource() const {return true;}
		virtual std::string GetSource() const {return {};};

		virtual bool HasTarget() const {return true;}
		virtual std::string GetTarget() const {return {};};

		virtual Image Execute(Image sc) = 0;

//		/// Execute the undo command and/or return the name of the previous state
//		virtual std::string Undo(StateContainer& sc) = 0;

		virtual std::string ToString() const = 0;

		friend bool operator==(const Command& lft, const Command& rht) {return lft.ToString() == rht.ToString();}
		friend bool operator!=(const Command& lft, const Command& rht) {return !(lft == rht);}
	};

	struct CommandCreator {
		bool(*Comparer)(const std::string&) = nullptr;
		Command*(*Loader)(const std::string&) = nullptr;
		std::string(*Saver)(const Command*) = nullptr;

		friend bool operator==(const CommandCreator& lft, const CommandCreator& rht) {return lft.Comparer == rht.Comparer &&  lft.Loader == rht.Loader && lft.Saver == rht.Saver;}
		friend bool operator!=(const CommandCreator& lft, const CommandCreator& rht) {return !(lft == rht);}
	};

	class LoadCommand : public Command
	{
	public:
		LoadCommand(std::filesystem::path path, std::string variable);
	public:
		virtual bool HasSource() const override {return false;}
		virtual std::string GetTarget() const override {return variableStore;}

		virtual Image Execute(Image img) override;
	public:
		static std::regex GetComparer();
		static bool Compare(const std::string& content);
		static Command* Create(const std::string& content);
		static std::string Save(const Command* command);
		virtual std::string ToString() const override {return Save(this);}

	private:
		std::filesystem::path source;
		std::string variableStore;
	};

	class SaveCommand : public Command
	{
	public:
		SaveCommand(std::string variable, std::filesystem::path path);
	public:
		virtual bool HasTarget() const override {return false;}
		virtual std::string GetSource() const override {return variableSource;}
		virtual Image Execute(Image img) override;
	public:
		static std::regex GetComparer();
		static bool Compare(const std::string& content);
		static Command* Create(const std::string& content);
		static std::string Save(const Command* command);
		virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource;
		std::filesystem::path pathTarget;
	};

	class ConvertCommand : public Command
	{
	public:
		ConvertCommand(std::string variableSource, std::string variableTarget, ModelType conversionModel);
	public:
		virtual std::string GetSource() const override {return variableSource;}
		virtual std::string GetTarget() const override {return variableTarget;}
		virtual Image Execute(Image img) override;
	public:
		static std::regex GetComparer();
		static bool Compare(const std::string& content);
		static Command* Create(const std::string& content);
		static std::string Save(const Command* command);
		virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource;
		std::string variableTarget;
		ModelType conversionModel;
	};

	class ThresholdCommand : public Command
	{
	public:
		ThresholdCommand(std::string variableSource, std::string variableTarget, int64_t threshold);
	public:
		virtual std::string GetSource() const override {return variableSource;}
		virtual std::string GetTarget() const override {return variableTarget;}
		virtual Image Execute(Image img) override;
	public:
		static std::regex GetComparer();
		static bool Compare(const std::string& content);
		static Command* Create(const std::string& content);
		static std::string Save(const Command* command);
		virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource;
		std::string variableTarget;
		int64_t threshold;
	};

	static inline std::vector<CommandCreator> s_Command {
			{LoadCommand::Compare, LoadCommand::Create, LoadCommand::Save},
			{SaveCommand::Compare, SaveCommand::Create, SaveCommand::Save},
			{ConvertCommand::Compare, ConvertCommand::Create, ConvertCommand::Save},
			{ThresholdCommand::Compare, ThresholdCommand::Create, ThresholdCommand::Save},
	};

	namespace CommandHelper {
		Command* GetCommand(const std::string& str);
	}

}