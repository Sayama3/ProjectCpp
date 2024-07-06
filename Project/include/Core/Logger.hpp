//
// Created by ianpo on 06/07/2024.
//

#pragma once


#ifndef SPDLOG_ACTIVE_LEVEL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#endif

#include <memory>
#include <exception>
#include <stdexcept>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "Core/Macro.hpp"


class Log {
public:
	static void Init();
	inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }

private:
	static std::shared_ptr<spdlog::logger> s_Logger;
};


#ifdef PC_LOG

#define PC_TRACE(...)       ::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::trace, __VA_ARGS__)
#define PC_INFO(...)        ::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::info, __VA_ARGS__)
#define PC_WARNING(...)     ::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::warn, __VA_ARGS__)
#define PC_WARN(...)     ::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::warn, __VA_ARGS__)
#define PC_ERROR(...)       ::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::err, __VA_ARGS__)
#define PC_CRITICAL(...)    ::Log::GetLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::critical, __VA_ARGS__)

#else

#define PC_TRACE(...)
#define PC_INFO(...)
#define PC_WARNING(...)
#define PC_WARN(...)
#define PC_ERROR(...)
#define PC_CRITICAL(...)

#endif

#if PC_USE_ASSERT
	#if (_MSC_VER && !__INTEL_COMPILER) || (__MINGW32__ || __MINGW64__)
		#define PC_ASSERT(condition, ...) if(!(condition)) { PC_ERROR(__VA_ARGS__); __debugbreak(); }
	#elif _POSIX
		#define PC_ASSERT(condition, ...) if(!(condition)) { PC_ERROR(__VA_ARGS__); std::raise(SIGTRAP) }
	#else
		#define PC_ASSERT(condition, ...) if(!(condition)) { PC_ERROR(__VA_ARGS__); throw std::runtime_error(fmt::format(__VA_ARGS__));  }
	#endif
#else
	#define PC_ASSERT(condition, ...)
#endif

#if PC_DEBUG
	#define PC_CHECK(condition, ...)  if(!(condition)) { PC_WARNING(__VA_ARGS__); }
#else
	#define PC_CHECK(condition, ...)
#endif