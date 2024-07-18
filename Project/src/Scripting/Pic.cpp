//
// Created by ianpo on 18/07/2024.
//

#include "Scripting/Pic.hpp"
#include "Core/FileSystem.hpp"
#include <string>
#include <sstream>


using namespace PC;

namespace Pic {
	void Pic::AddCommand(std::string command)
	{
		State state;
		state.commandStr = std::move(command);
		state.command.reset(CommandHelper::GetCommand(state.commandStr));
		if(state) {
			States.push_back(std::move(state));
		} else {
			PC_WARNING("The command '{}' is not valid.", state.commandStr);
		}
	}

	void Pic::AddCommand(std::unique_ptr<Command> command) {
		State state;
		state.command = std::move(command);
		state.commandStr = state.command ? state.command->ToString() : std::string{};
		if(state) {
			States.push_back(std::move(state));
		} else {
			PC_WARNING("No command has been given.");
		}
	}

	Pic::Pic(const std::filesystem::path &path) : Pic(FS::ReadTextInFile(path))
	{
	}

	Pic::Pic(const std::string& input)
	{
		std::string result;
		std::istringstream iss(input);

		for (std::string line; std::getline(iss, line); )
		{
			AddCommand(line);
		}
	}

	std::string Pic::ToString() const {
		std::string str;
		for(const auto& state : States) {
			str += state.commandStr;
			str += '\n';
		}
		return std::move(str);
	}
	void Pic::UpdateCommand(uint64_t index){States[index].UpdateCommandFromString();}

	void Pic::Execute(uint64_t offset) {
		for (int i = offset; i < States.size(); ++i) {
			auto& state = States[i];
			if(!state.command) state.UpdateCommandFromString();
			if(!state.command) continue;

			const Image* imgPtr = state.command->HasSource() ? GetImage(state.command->GetTarget(), i) : nullptr;
			state.result = std::move(state.command->Execute(imgPtr ? *imgPtr : Image{}));
			if(state.command->HasTarget()) {
				state.resultTex = {state.result.GetTextureSpec(), state.result.GetImageBuffer()};
			}
		}
	}

	const Image *Pic::GetImage(const std::string &variable, uint64_t upperBound) {
		const Image* img = nullptr;
		for (int64_t i = std::min(upperBound, States.size()) - 1; i >= 0; --i)
		{
			auto& state = States[i];
			if(!state.command) continue;

			if(state.command->HasTarget() && state.command->GetTarget() == variable) {
				return &state.result;
			}
		}
		return nullptr;
	}

	Pic::Pic(Pic && other) noexcept : States(std::move(other.States))
	{
	}

	Pic &Pic::operator=(Pic &&other) noexcept {
		std::swap(States, other.States);
		return *this;
	}
}
