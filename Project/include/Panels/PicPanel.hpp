//
// Created by ianpo on 18/07/2024.
//

#pragma once

#include "Panel.hpp"
#include "Scripting/Pic.hpp"
#include <filesystem>

namespace PC {

	class PicPanel : public Panel
	{
	public:
		virtual void Begin() override;
		virtual void Update(float dt) override;
		virtual void PostUpdate(float dt) override;
		virtual void End() override;
	private:
		void UpdateMainMenu();
		void UpdateStates();
		void UpdateState(uint64_t id, Pic::Pic& state, bool& open);

		void SaveState(Pic::Pic& state, const std::filesystem::path& path);
	private:
		uint64_t AddState(Pic::Pic state);
		bool RemoveState(uint64_t id);
	private:
		static inline uint64_t s_Count{0};
		std::unordered_map<uint64_t, Pic::Pic> m_States;
	};

}// namespace PC
