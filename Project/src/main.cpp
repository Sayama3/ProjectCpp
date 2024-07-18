//
// Created by ianpo on 17/01/2024.
//

#define NOMINMAX

#include "glad/glad.h"

#define GLFW_INCLUDE_NONE 1
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM 1

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <GLFW/glfw3.h>

#include "Core/Logger.hpp"
#include "Core/Application.hpp"
#include "Panels/ImageCreator.hpp"


using namespace PC;

int main(int, char**)
{
	Log::Init();

	std::unique_ptr<Application> application = std::make_unique<Application>();

	{
		ImageCreator imCreator;
		while (application->ShouldUpdate()) {
			application->BeginUpdate();

			imCreator.Update();
			imCreator.PostUpdate();

			application->EndUpdate();
		}
	}

	return 0;
}