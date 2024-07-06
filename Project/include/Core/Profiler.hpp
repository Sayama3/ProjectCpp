//
// Created by ianpo on 06/07/2024.
//

#pragma once

#define TracyFunction PC_FUNC

#include <tracy/Tracy.hpp>

#if PC_PROFILING

#define PC_PROFILE_BEGIN_SESSION(name, filepath)
#define PC_PROFILE_END_SESSION()
#define PC_FRAME_START() FrameMark//FrameMarkStart(s_MainFrame)
#define PC_FRAME_END() //FrameMarkEnd(s_MainFrame)
#define PC_PROFILE_SCOPE(name) ZoneScopedN(name)
#define PC_PROFILE_FUNCTION() ZoneScoped

#else

#define PC_PROFILE_BEGIN_SESSION(name, filepath)
#define PC_PROFILE_END_SESSION()
#define PC_FRAME_START()
#define PC_FRAME_END()
#define PC_PROFILE_SCOPE(name)
#define PC_PROFILE_FUNCTION()

#endif