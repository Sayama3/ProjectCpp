//
// Created by Sayama on 17/01/2024.
//

#include "Core/Logger.hpp"

namespace PC
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// Setting Pattern
		spdlog::set_pattern("%^[%T] [%l] %n (%s:%#->%!): %v%$");

		// Creating core logger
		s_CoreLogger = spdlog::stdout_color_mt("PC");
		s_CoreLogger->set_level(spdlog::level::trace);
		// Creating Client logger
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}