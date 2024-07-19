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

#define PC_COMMAND_CREATOR(CLASS) {CLASS::Compare, CLASS::Create, CLASS::Save}

namespace Pic {
	class Command {
	public:
		virtual ~Command() = default;
		[[nodiscard]] virtual bool HasSource() const {return true;}
		[[nodiscard]] virtual std::string GetSource() const {return {};};

		[[nodiscard]] virtual bool HasTarget() const {return true;}
		[[nodiscard]] virtual std::string GetTarget() const {return {};};

		[[nodiscard]] virtual Image Execute(const Image& sc) = 0;

//		/// Execute the undo command and/or return the name of the previous state
//		virtual std::string Undo(StateContainer& sc) = 0;

		[[nodiscard]] virtual std::string ToString() const = 0;

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
		[[nodiscard]] virtual bool HasSource() const override {return false;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableStore;}

		[[nodiscard]] virtual Image Execute(const Image& img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}

	private:
		std::filesystem::path source;
		std::string variableStore;
	};

	class SaveCommand : public Command
	{
	public:
		SaveCommand(std::string variable, std::filesystem::path path);
	public:
		[[nodiscard]] virtual bool HasTarget() const override {return false;}
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual Image Execute(const Image& img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource;
		std::filesystem::path pathTarget;
	};

	class ConvertCommand : public Command
	{
	public:
		ConvertCommand(std::string variableSource, std::string variableTarget, ModelType conversionModel);
	public:
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(const Image& img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
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
		[[nodiscard]] virtual std::string GetSource() const override {return variableSource;}
		[[nodiscard]] virtual std::string GetTarget() const override {return variableTarget;}
		[[nodiscard]] virtual Image Execute(const Image& img) override;
	public:
		[[nodiscard]] static std::regex GetComparer();
		[[nodiscard]] static bool Compare(const std::string& content);
		[[nodiscard]] static Command* Create(const std::string& content);
		[[nodiscard]] static std::string Save(const Command* command);
		[[nodiscard]] virtual std::string ToString() const override {return Save(this);}
	private:
		std::string variableSource;
		std::string variableTarget;
		int64_t threshold;
	};

	/// Function to add all the geometrics Commands to the list of command
	static inline void AddBaseCommands(std::vector<CommandCreator>& commands) {
		commands.insert(commands.end(), {
				PC_COMMAND_CREATOR(LoadCommand),
				PC_COMMAND_CREATOR(SaveCommand),
				PC_COMMAND_CREATOR(ConvertCommand),
				PC_COMMAND_CREATOR(ThresholdCommand),
		});
	}

	namespace CommandHelper {
		Command* GetCommand(const std::vector<CommandCreator>& commands, const std::string& str);
	}

}