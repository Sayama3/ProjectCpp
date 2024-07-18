//
// Created by ianpo on 18/07/2024.
//

#include "Panels/PicPanel.hpp"
#include "Core/FileSystem.hpp"
#include <string>
#include <format>
#include <imgui.h>
#include "ImGui/imgui_stdlib.h"

namespace PC {
	void PicPanel::Begin()
	{

	}

	void PicPanel::Update(float dt)
	{
		UpdateMainMenu();
	}

	void PicPanel::PostUpdate(float dt)
	{
		UpdateStates();
	}

	void PicPanel::End()
	{
	}

	void PicPanel::UpdateStates()
	{
		for (auto& [id, state] : m_States) {
			UpdateState(id, state);
		}
	}

	void PicPanel::UpdateMainMenu()
	{
		ImGui::Begin("Pic Panel");
		{
			if(ImGui::Button("Load Pic File")) {
//				std::filesystem::path p;
				//TODO: Search for a file a load if found.
				std::string str;
//				FS::ReadTextInFile(p,str);
				::Pic::Pic sc(str);
				AddState(std::move(sc));
			}

			if(ImGui::Button("New Pic")) {
				AddState({});
			}
		}
		ImGui::End();
	}

	void PicPanel::UpdateState(uint64_t id, ::Pic::Pic &state)
	{
		std::string stateName = std::format("Pic {}", id);
		ImGui::Begin(stateName.c_str());
		{

			uint64_t index = -1;
			for (int i = 0; i < state.States.size(); ++i) {
				ImGui::PushID(i);
				bool textChanged = ImGui::InputText("##State", &state.States[i].commandStr);

				if(state.States[i].resultTex.GetRenderID()) {
					ImGui::Image(reinterpret_cast<ImTextureID>(state.States[i].resultTex.GetRenderID()), ImVec2(state.States[i].result.GetWidth(), state.States[i].result.GetHeight()));
				}

				ImGui::PopID();

				if(!textChanged) continue;
				auto* command = Pic::CommandHelper::GetCommand(state.States[i].commandStr);
				if(command) {
					state.States[i].command.reset(command);
				}
				if(index == -1) index = i;
			}

			{
				ImGui::Separator();
				static std::string commandStr;
				ImGui::InputText("##NewState", &commandStr);
				if(ImGui::Button("Add New Line")) {
					auto* command = Pic::CommandHelper::GetCommand(commandStr);
					if(command) {
						if(index == -1) index = state.States.size();
						state.AddCommand(std::unique_ptr<Pic::Command>(command));
					} else {
						PC_WARN("The command '{}' is not valid.", commandStr);
					}
				}
			}

			if(index != -1) {
				state.Execute(index);
			}

			if(ImGui::Button("Re-run")) {
				state.Execute();
			}

			if(ImGui::Button("Save")) {
				std::filesystem::path p;
				// TODO: Fetch path
				SaveState(state, p);
			}
		}
		ImGui::End();
	}
	void PicPanel::SaveState(::Pic::Pic& state, const std::filesystem::path& path)
	{
		FS::WriteTextInFile(path, state.ToString());
	}

	uint64_t PicPanel::AddState(::Pic::Pic state) {
		auto id = s_Count++;
		m_States.insert({id, std::move(state)});
		return id;
	}

	bool PicPanel::RemoveState(uint64_t id)
	{
		auto it = m_States.find(id);
		if(it != m_States.end()) {
			m_States.erase(it);
			return true;
		}
		return false;
	}
}// namespace PC