//
// Created by ianpo on 18/07/2024.
//

#pragma once

#include "Image.hpp"
#include "OpenGL/Texture.hpp"
#include "Commands.hpp"
#include <vector>
#include <filesystem>
#include <unordered_map>
#include <string>
#include <cstdint>
#include <memory>
#include <tuple>

namespace Pic {
	class Pic {
	public:
		struct State {
			std::string commandStr{};
			std::unique_ptr<Command> command{nullptr};
			Image result{};
			Texture resultTex{};

			void UpdateCommandFromString() {command.reset(CommandHelper::GetCommand(commandStr));}

			operator bool() {return command.operator bool();}
		};
	public:
		Pic() = default;
		~Pic() = default;
		Pic(const Pic&) = default;
		Pic& operator=(const Pic&) = default;
		Pic(Pic&& other) noexcept;
		Pic& operator=(Pic&& other) noexcept;

		Pic(const std::filesystem::path& path);
		Pic(const std::string& picFileContent);
	public:
		void AddCommand(std::string command);
		void AddCommand(std::unique_ptr<Command> command);
	public:
		void UpdateCommand(uint64_t index);
		void Execute(uint64_t offset = 0);
		/// Search for an image in the range [0, min(States.size, upperBound)[
		const Image* GetImage(const std::string& variable, uint64_t upperBound = UINT64_MAX);
	public:
		[[nodiscard]] std::string ToString() const;
	public:
		std::vector<State> States;
	};
}