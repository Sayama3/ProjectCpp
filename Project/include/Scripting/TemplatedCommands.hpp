//
// Created by ianpo on 19/07/2024.
//

#pragma once

#include "Commands.hpp"

#define PC_FLOAT_REG R"(((?:(?:\.\d+)|(?:\d+(?:\.\d*)?))))"
#define PC_INT_REG R"(([-+]?\d+))"
#define PC_UINT_REG R"((\d+))"

namespace Pic {

	template<class Self, typename T>
	class TCommand : public Command {
	public:
		TCommand(std::string variableSrc, std::string variableTrg, T value) : variableSource(std::move(variableSrc)), variableTarget(std::move(variableTrg)), value(value) {}
		[[nodiscard]] virtual std::string GetSource() const override { return variableSource; }
		[[nodiscard]] virtual std::string GetTarget() const override { return variableTarget; }
	public:
		[[nodiscard]] static bool Compare(const std::string &content) { return std::regex_search(content, Self::GetComparer()); }
		[[nodiscard]] static Command* Create(const std::string &content) {
			std::smatch smatch;
			if (!std::regex_search(content, smatch, Self::GetComparer())) return nullptr;
			return new Self(smatch[2], smatch[3], Self::StringToValue(smatch[1]));
		}
		[[nodiscard]] static std::string Save(const Command *command) {
			const auto *c = dynamic_cast<const Self *>(command);
			if (!c) return "";
			return std::format("{} {} {} in {}", Self::GetCommandName(), c->value, c->variableSource, c->variableTarget);
		}
		[[nodiscard]] virtual std::string ToString() const override { return Save(this); }

	protected:
		std::string variableSource, variableTarget;
		T value;
	};

	template<class Self>
	class TCommandNoParam : public Command {
	public:
		TCommandNoParam(std::string variableSrc, std::string variableTrg) : variableSource(std::move(variableSrc)), variableTarget(std::move(variableTrg)) {}
		[[nodiscard]] virtual std::string GetSource() const override { return variableSource; }
		[[nodiscard]] virtual std::string GetTarget() const override { return variableTarget; }

	public:
		[[nodiscard]] static std::regex GetComparer() {
			static std::string regex = std::format(R"(\s*{}\s+(\w+)\s+in\s+(\w+)\s*)", Self::GetCommandName());
			static auto reg = std::regex(regex, std::regex_constants::icase);
			return reg;
		}
		[[nodiscard]] static bool Compare(const std::string &content) { return std::regex_search(content, Self::GetComparer()); }
		[[nodiscard]] static Command *Create(const std::string &content) {
			std::smatch smatch;
			if (!std::regex_search(content, smatch, GetComparer())) return nullptr;
			return new Self(smatch[1], smatch[2]);
		}
		[[nodiscard]] static std::string Save(const Command *command) {
			const auto *c = dynamic_cast<const Self *>(command);
			if (!c) return "";
			return std::format("{} {} in {}", Self::GetCommandName(), c->variableSource, c->variableTarget);
		}
		[[nodiscard]] virtual std::string ToString() const override { return Save(this); }

	protected:
		std::string variableSource, variableTarget;
	};

	template<class Self>
	class IntCommand : public TCommand<Self, int> {
	public:
		IntCommand(std::string variableSrc, std::string variableTrg, int value) : TCommand<Self, int>(variableSrc, variableTrg, value) {}
		[[nodiscard]] static std::regex GetComparer() {
			static std::string regex = std::format(R"(\s*{}\s+([-+]?\d+)\s+(\w+)\s+in\s+(\w+)\s*)", Self::GetCommandName());
			static auto reg = std::regex(regex, std::regex_constants::icase);
			return reg;
		}
		static int StringToValue(const std::string &value) { return std::stoi(value); }
	};

	template<class Self>
	class FloatCommand : public TCommand<Self, float> {
	public:
		FloatCommand(std::string variableSrc, std::string variableTrg, float value) : TCommand<Self, float>(variableSrc, variableTrg, value) {}
		[[nodiscard]] static std::regex GetComparer() {
			static std::string regex = std::format(R"(\s*{}\s+((?:(?:\.\d+)|(?:\d+(?:\.\d*)?)))\s+(\w+)\s+in\s+(\w+)\s*)", Self::GetCommandName());
			static auto reg = std::regex(regex, std::regex_constants::icase);
			return reg;
		}
		static float StringToValue(const std::string &value) { return std::stof(value); }
	};
}

#define PC_IMPL_FLT_COMMAND(ClassName, Func, commandName) public:\
	ClassName(std::string variableSrc, std::string variableTrg, float value) : FloatCommand<ClassName>(variableSrc, variableTrg, value) {} \
[[nodiscard]] virtual Image Execute(const Image& sc) override {return Func(sc, value);} \
[[nodiscard]] static std::string GetCommandName() {return commandName;} \
[[nodiscard]] std::string GetName() {return GetCommandName();}

#define PC_IMPL_INT_COMMAND(ClassName, Func, commandName) public:\
	ClassName(std::string variableSrc, std::string variableTrg, int value) : IntCommand<ClassName>(variableSrc, variableTrg, value) {} \
	[[nodiscard]] virtual Image Execute(const Image& sc) override {return Func(sc, value);} \
	[[nodiscard]] static std::string GetCommandName() {return commandName;} \
	[[nodiscard]] std::string GetName() {return GetCommandName();}

#define PC_IMPL_NO_PARAM_COMMAND(ClassName, Func, commandName) public:\
	ClassName(std::string variableSrc, std::string variableTrg) : TCommandNoParam<ClassName>(variableSrc, variableTrg) {} \
	[[nodiscard]] virtual Image Execute(const Image& sc) override {return Func(sc);} \
	[[nodiscard]] static std::string GetCommandName() {return commandName;} \
	[[nodiscard]] std::string GetName() {return GetCommandName();}
