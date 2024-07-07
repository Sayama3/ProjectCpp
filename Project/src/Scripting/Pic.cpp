//
// Created by ianpo on 06/07/2024.
//

#include "Scripting/Pic.hpp"
#include "stb_image_write.h"
State::State(const Image &img) : image(img)
{
	CreateTextureFromImage();
}

State::State(Image &&img) : image(std::move(img))
{
	CreateTextureFromImage();
}

void State::CreateTextureFromImage()
{
	texture = {image.GetTextureSpec(), image.GetImageBuffer()};
}
State::State(const State& o) : image(o.image), NextState(o.NextState), PreviousState(o.PreviousState) {
	CreateTextureFromImage();
}
State &State::operator=(const State& o){
	image = o.image;
	NextState = o.NextState;
	PreviousState = o.PreviousState;
	CreateTextureFromImage();
	return *this;
}

State::State(State&& o) noexcept : image(std::move(o.image)), texture(std::move(o.texture)), NextState(std::move(o.NextState)), PreviousState(std::move(o.PreviousState))
{
}

State &State::operator=(State&& o) noexcept {
	std::swap(image, o.image);
	std::swap(texture, o.texture);
	std::swap(NextState, o.NextState);
	std::swap(PreviousState, o.PreviousState);
	return *this;
}

StateContainer::StateContainer(const std::string& name, const State &state)
{
	m_StateOrder.push_back(name);
	m_States[name] = state;
}

StateContainer::StateContainer(const std::string& name, State&& state)
{
	m_StateOrder.push_back(name);
	m_States[name] = std::move(state);
}

StateContainer::StateContainer(StateContainer&& o) noexcept : m_States(o.m_States), m_StateOrder(o.m_StateOrder)
{
}

StateContainer &StateContainer::operator=(StateContainer&& o) noexcept {
	std::swap(m_States, o.m_States);
	std::swap(m_StateOrder, o.m_StateOrder);
	return *this;
}


void StateContainer::AddState(const std::string &stateName, const State &state, const std::string &previousState)
{
	m_StateOrder.push_back(stateName);
	m_States[stateName] = state;
	if(!previousState.empty()) {
		auto it = m_States.find(previousState);
		if(it != m_States.end()) {
			m_States[stateName].PreviousState = previousState;
			it->second.NextState = stateName;
		}
	}
}

void StateContainer::AddState(const std::string &stateName, State &&state, const std::string &previousState)
{
	m_StateOrder.push_back(stateName);
	m_States[stateName] = std::move(state);
	if(!previousState.empty()) {
		auto it = m_States.find(previousState);
		if(it != m_States.end()) {
			m_States[stateName].PreviousState = previousState;
			it->second.NextState = stateName;
		}
	}
}

State* StateContainer::TryGetState(const std::string &name) {
	auto it = m_States.find(name);
	if(it != m_States.end()) {
		return &(it->second);
	} else {
		return nullptr;
	}
}
State *StateContainer::TryGetState(uint64_t index) {
	if(index >= m_StateOrder.size()) return nullptr;
	return TryGetState(m_StateOrder[index]);
}

const std::string& StateContainer::GetStateName(uint64_t index) const {
	return m_StateOrder[index];
}

uint64_t StateContainer::GetStateCount() const {
	return m_StateOrder.size();
}
bool StateContainer::HasState(const std::string &name) const {
	return m_States.contains(name);
}

LoadCommand::LoadCommand(std::filesystem::path path, std::string variable) : source(std::move(path)), variableStore(std::move(variable))
{
}

std::string LoadCommand::Execute(StateContainer &sc) {
	sc.AddState(variableStore, Image(source));
	return variableStore;
}

std::string LoadCommand::Undo(StateContainer &sc) {
	return {};
}

SaveCommand::SaveCommand(std::string variable, std::filesystem::path path) : variableSource(std::move(variable)), pathTarget(std::move(path))
{
}

std::string SaveCommand::Execute(StateContainer &sc) {
	auto* state = sc.TryGetState(variableSource);
	if(!state) return {};

	std::string strPath = pathTarget.string();
	auto& img = state->image;

	stbi_write_png(strPath.c_str(), img.GetWidth(), img.GetHeight(), img.GetChannels(), &img(0,0,0), img.GetWidth() * img.GetChannels());
	return std::move(strPath);
}

std::string SaveCommand::Undo(StateContainer &sc) {
	return sc.HasState(variableSource) ? variableSource : std::string{};
}


ConvertCommand::ConvertCommand(std::string variableSource, std::string variableTarget, ModelType conversionModel) : variableSource(std::move(variableSource)), variableTarget(std::move(variableTarget)), conversionModel(conversionModel)
{

}

std::string ConvertCommand::Execute(StateContainer &sc) {
	auto* previous = sc.TryGetState(variableSource);
	if(!previous) return {};

	previous->NextState = variableSource;
	State newState(*previous);
	newState.PreviousState = variableSource;

	newState.image.ConvertImageToModelType(conversionModel);\
	newState.CreateTextureFromImage();

	sc.AddState(variableTarget, std::move(newState), variableSource);
	return variableTarget;
}

std::string ConvertCommand::Undo(StateContainer &sc)
{
	return sc.HasState(variableSource) ? variableSource : std::string{};
}

ThresholdCommand::ThresholdCommand(std::string variableSource, std::string variableTarget, uint32_t threshold) : variableSource(std::move(variableSource)),variableTarget(std::move(variableTarget)), threshold(threshold)
{
}

std::string ThresholdCommand::Execute(StateContainer &sc) {
	auto* previous = sc.TryGetState(variableSource);
	if(!previous) return {};

	previous->NextState = variableSource;
	State newState(*previous);
	newState.PreviousState = variableSource;

	//TODO: Do the threshold.
//	newState.image.Threshold(threshold);
//	newState.CreateTextureFromImage();

	sc.AddState(variableTarget, std::move(newState), variableSource);
	return variableTarget;
}

std::string ThresholdCommand::Undo(StateContainer &sc) {
	return sc.HasState(variableSource) ? variableSource : std::string{};
}
