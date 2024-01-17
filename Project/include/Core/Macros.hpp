//
// Created by Sayama on 17/01/2024.
//

#pragma once


#include <csignal>

#ifndef IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 1
#endif

#define PC_CONCAT(x, y) x ## y
#define PC_COMBINE(x, y) PC_CONCAT(x, y)

// Defining the "_USE_MATH_DEFINES" for visual studio in the main hpp
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#ifndef __FUNCSIG__
#ifdef __PRETTY_FUNCTION__
		#define __FUNCSIG__ __PRETTY_FUNCTION__
	#else
		#define __FUNCSIG__ __FUNCTION__
	#endif
#endif

#ifdef PC_USE_SIMPLE_FUNCTION
#define PC_FUNC __FUNCTION__
#else
#define PC_FUNC __FUNCSIG__
#endif

#define PC_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
//deprecated. Use PC_BIND_EVENT_FN
#define BIND_EVENT_FN(fn) PC_BIND_EVENT_FN(fn)
//#define BIND_EVENT_FN(func) [this](auto && PH1) { func(std::forward<decltype(PH1)>(PH1)); }
//#define BIND_EVENT_FN(func, ...)	std::bind(&func, this, __VA_ARGS__)
//#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#ifdef PC_DEBUG
#ifndef PC_USE_ASSERT
        #define PC_USE_ASSERT 1
    #endif

    #ifndef PC_PROFILING
        #define PC_PROFILING 1
    #endif
#endif

#ifndef PC_DONT_PROFILE
#ifndef PC_PROFILING
#define PC_PROFILING 1
#endif
#endif

#if PC_USE_ASSERT
#if (_MSC_VER && !__INTEL_COMPILER) || (__MINGW32__ || __MINGW64__)
        #define PC_CORE_ASSERT(condition, ...) if(!(condition)) { PC_CORE_ERROR(__VA_ARGS__); __debugbreak(); }
        #define PC_ASSERT(condition, ...) if(!(condition)) { PC_ERROR(__VA_ARGS__); __debugbreak(); }
    #elif _POSIX
        #define PC_CORE_ASSERT(condition, ...) if(!(condition)) { PC_CORE_ERROR(__VA_ARGS__); std::raise(SIGTRAP) }
        #define PC_ASSERT(condition, ...) if(!(condition)) { PC_ERROR(__VA_ARGS__); std::raise(SIGTRAP) }
    #else
        #define PC_CORE_ASSERT(condition, ...) if(!(condition)) { PC_ERROR(__VA_ARGS__); }
        #define PC_ASSERT(condition, ...) if(!(condition)) { PC_ERROR(__VA_ARGS__); }
    #endif
#else
#define PC_CORE_ASSERT(condition, ...)
#define PC_ASSERT(condition, ...)
#endif

#ifndef BIT
#define BIT(X) (1 << X)
#endif

