//
// Created by Sayama on 17/01/2024.
//

#pragma once
#include <memory>
#include <filesystem>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace PC {

	class Log {
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}



#ifdef PC_DEBUG
//  spdlog::source_loc(__FILE__, __LINE__, __FUNCTION__ )
#define PC_CORE_TRACE(...)       ::PC::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::trace, __VA_ARGS__)
#define PC_CORE_INFO(...)        ::PC::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::info, __VA_ARGS__)
#define PC_CORE_WARNING(...)     ::PC::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::warn, __VA_ARGS__)
#define PC_CORE_ERROR(...)       ::PC::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::err, __VA_ARGS__)
#define PC_CORE_CRITICAL(...)    ::PC::Log::GetCoreLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::critical, __VA_ARGS__)


#define PC_TRACE(...)       ::PC::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::trace, __VA_ARGS__)
#define PC_INFO(...)        ::PC::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::info, __VA_ARGS__)
#define PC_WARNING(...)     ::PC::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::warn, __VA_ARGS__)
#define PC_ERROR(...)       ::PC::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::err, __VA_ARGS__)
#define PC_CRITICAL(...)    ::PC::Log::GetClientLogger()->log(spdlog::source_loc{__FILE__, __LINE__, PC_FUNC}, spdlog::level::critical, __VA_ARGS__)

//#define PC_CORE_TRACE(...)       ::PC::Log::GetCoreLogger()->trace(__VA_ARGS__)
//#define PC_CORE_INFO(...)        ::PC::Log::GetCoreLogger()->info(__VA_ARGS__)
//#define PC_CORE_WARNING(...)     ::PC::Log::GetCoreLogger()->warn(__VA_ARGS__)
//#define PC_CORE_ERROR(...)       ::PC::Log::GetCoreLogger()->error(__VA_ARGS__)
//#define PC_CORE_CRITICAL(...)    ::PC::Log::GetCoreLogger()->critical(__VA_ARGS__)
//
//
//#define PC_TRACE(...)       ::PC::Log::GetClientLogger()->trace(__VA_ARGS__)
//#define PC_INFO(...)        ::PC::Log::GetClientLogger()->info(__VA_ARGS__)
//#define PC_WARNING(...)     ::PC::Log::GetClientLogger()->warn(__VA_ARGS__)
//#define PC_ERROR(...)       ::PC::Log::GetClientLogger()->error(__VA_ARGS__)
//#define PC_CRITICAL(...)    ::PC::Log::GetClientLogger()->critical(__VA_ARGS__)

#else

#define PC_CORE_TRACE(...)
#define PC_CORE_INFO(...)
#define PC_CORE_WARNING(...)
#define PC_CORE_ERROR(...)
#define PC_CORE_CRITICAL(...)


#define PC_TRACE(...)
#define PC_INFO(...)
#define PC_WARNING(...)
#define PC_ERROR(...)
#define PC_CRITICAL(...)

#endif