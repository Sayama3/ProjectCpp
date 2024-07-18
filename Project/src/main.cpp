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
#include "Panels/PicPanel.hpp"
#include "test.hpp"


using namespace PC;

int main(int, char**)
{
	Log::Init();

    int res = test_All();
    if(res<0)
    {
        return res;
	}

	std::unique_ptr<Application> application = std::make_unique<Application>();

	{
		double lastTime{0};
		double deltaTime{1.0/60.0};
		ImageCreator imCreator;
		PicPanel picPanel;

		imCreator.Begin();
		picPanel.Begin();

		while (application->ShouldUpdate()) {

			{
				double time = glfwGetTime();
				deltaTime = time - lastTime;
				lastTime = time;
			}
			auto dt = (float)deltaTime;

			application->BeginUpdate();

			{
				imCreator.Update(dt);
				picPanel.Update(dt);
			}

			{
				imCreator.PostUpdate(dt);
				picPanel.PostUpdate(dt);
			}

			application->EndUpdate();
		}

		imCreator.End();
		picPanel.End();
	}

	return 0;
}