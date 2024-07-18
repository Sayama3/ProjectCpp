//
// Created by ianpo on 06/07/2024.
//

#include "Core/Logger.hpp"
#include <spdlog/sinks/basic_file_sink.h>


std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Init()
{
   // Setting Pattern
   spdlog::set_pattern("%^[%T] [%l] %n (%s:%#->%!): %v%$");

   // Creating core logger
   std::array<spdlog::sink_ptr, 2> app_sinks;
   app_sinks[0] = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
   app_sinks[1] = std::make_shared<spdlog::sinks::basic_file_sink_mt>("ProjectCpp.log");

   s_Logger = std::make_shared<spdlog::logger>("App", app_sinks.begin(), app_sinks.end());
   s_Logger->set_level(spdlog::level::trace);


   //TODO: Add imgui sink logger.
}