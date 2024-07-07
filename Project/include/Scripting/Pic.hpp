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
#include <unordered_map>
#include <utility>
#include <unordered_map>
#include "OpenGL/Texture.hpp"
#include "Image.hpp"

//TODO: Implement a Command Pattern to describe and represent the change of the Image as we interact with it.

struct State {
	State() = default;

	State(const State&);
	State& operator=(const State&);

	State(State&&) noexcept;
	State& operator=(State&&) noexcept;

	State(const Image& image);
	State(Image&& image);

	~State() = default;

	void CreateTextureFromImage();

	Image image{};
	Texture texture{};
	std::string NextState{};
	std::string PreviousState{};
};

class StateContainer {
public:
	StateContainer() = default;
	StateContainer(const StateContainer&) = default;
	StateContainer& operator=(const StateContainer&) = default;
	StateContainer(StateContainer&&) noexcept;
	StateContainer& operator=(StateContainer&&) noexcept;
	StateContainer(const std::string& name, const State& state);
	StateContainer(const std::string& name, State&& state);
	~StateContainer() = default;
public:
	void AddState(const std::string& stateName, const State& state, const std::string& previousState = {});
	void AddState(const std::string& stateName, State&& state, const std::string& previousState = {});

	bool HasState(const std::string& name) const;
	State* TryGetState(const std::string& name);
	State* TryGetState(uint64_t index);
	const std::string& GetStateName(uint64_t index) const;
	uint64_t GetStateCount() const;
private:
	std::vector<std::string> m_StateOrder;
	std::map<std::string, State> m_States;
};

class Command {
public:
	~Command() = default;
	/// Execute the command and return the name of the new state
	virtual std::string Execute(StateContainer& sc) = 0;

	/// Execute the undo command and/or return the name of the previous state
	virtual std::string Undo(StateContainer& sc) = 0;
};

class LoadCommand : public Command
{
public:
	LoadCommand(std::filesystem::path path, std::string variable);
public:
	virtual std::string Execute(StateContainer& sc) override;
	virtual std::string Undo(StateContainer& sc) override;

private:
	std::filesystem::path source;
	std::string variableStore;
};

class SaveCommand : public Command
{
public:
	SaveCommand(std::string variable, std::filesystem::path path);
	virtual std::string Execute(StateContainer& sc) override;
	virtual std::string Undo(StateContainer& sc) override;
private:
	std::string variableSource;
	std::filesystem::path pathTarget;
};

class ConvertCommand : public Command
{
public:
	ConvertCommand(std::string variableSource, std::string variableTarget, ModelType conversionModel);
public:
	virtual std::string Execute(StateContainer& sc) override;
	virtual std::string Undo(StateContainer& sc) override;
private:
	std::string variableSource;
	std::string variableTarget;
	ModelType conversionModel;
};

class ThresholdCommand : public Command
{
public:
	ThresholdCommand(std::string variableSource, std::string variableTarget, uint32_t threshold);
public:
	virtual std::string Execute(StateContainer& sc) override;
	virtual std::string Undo(StateContainer& sc) override;
private:
	std::string variableSource;
	std::string variableTarget;
	uint32_t threshold;
};