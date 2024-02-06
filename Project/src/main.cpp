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
#include <cstdio>
#include "Image.hpp"
#include "portable-file-dialogs.h"

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

// Main code
int main(int, char**)
{
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// Decide GL+GLSL versions
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 460";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

	// Create window with graphics context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Project Cpp", nullptr, nullptr);
	if (window == nullptr)
		return 1;
	glfwMakeContextCurrent(window);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	printf("glad loading status: %d\n", status);

	printf("OpenGL Info:\n");
	printf("  Vendor: %s\n", (const char*)glGetString(GL_VENDOR));
	printf("  Renderer: %s\n", (const char*)glGetString(GL_RENDERER));
	printf("  Version: %s\n", (const char*)glGetString(GL_VERSION));
	glfwSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = true;
	//io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
	// - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
	//io.Fonts->AddFontDefault();
	//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != nullptr);

	// Our state
	bool show_demo_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	const uint32_t uMin = 0;
	const uint32_t uMax = UINT32_MAX;
	const uint32_t maxChannel = 4;

	std::vector<std::string> imageTypeNames = ImageHelper::GetImageTypeNames();
	std::vector<Image*> images;

	images.push_back(new Image(R"(C:\Users\ianpo\Pictures\Iannis_V1_Squared.jpg)"));

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		{
			ImGui::Begin("Image Creator");
			{

				if (ImGui::CollapsingHeader("Create Default Image")) {
					if (ImGui::Button("Create")) {
						images.push_back(new Image());
					}
				}

				if (ImGui::CollapsingHeader("Create Image with value"))
				{
					static uint32_t width = 255;
					static uint32_t height = 255;
					static uint32_t channels = 4;
					static int type = 4;
					static uint8_t value = 255;
					ImGui::DragScalar("Width", ImGuiDataType_U32, &width, 1, &uMin, &uMax, "%d");
					ImGui::DragScalar("Height", ImGuiDataType_U32, &height, 1, &uMin, &uMax, "%d");
					ImGui::DragScalar("Channel", ImGuiDataType_U32, &channels, 1, &uMin, &maxChannel,"%d");
					if (ImGui::BeginCombo("Image Type", imageTypeNames[type].c_str())) {
						for (int i = 0; i < imageTypeNames.size(); i++) {
							const bool is_selected = (type == i);
							if (ImGui::Selectable(imageTypeNames[i].c_str(), is_selected)) {
								type = i;
							}

							// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
							if (is_selected) ImGui::SetItemDefaultFocus();
						}
						ImGui::EndCombo();
					}
					ImGui::DragScalar("Value", ImGuiDataType_U8, &channels, 1, nullptr, nullptr, "%d");

					if(ImGui::Button("Create"))
					{
						images.push_back(new Image(width, height, channels, (ImageType)type, value));
					}
				}
				if (ImGui::CollapsingHeader("Create Image with path"))
				{
					if(ImGui::Button("Choose Image"))
					{
						auto result = pfd::open_file("Select a file", "", {"Image Files (*.pgn, *.jpg)", "*"}, pfd::opt::multiselect);
						auto results = result.result();
						if(!results.empty())
						{
							for(const auto& path : results)
							{
								images.push_back(new Image(path));
							}
						}
					}
				}

				if (ImGui::CollapsingHeader("Create Image from other image"))
				{
					ImGui::BeginDisabled(images.empty());
					{
						static uint64_t indexImage = 0;
						indexImage = std::min(indexImage, images.size() - 1);
						std::string currentImage = "Image " + std::to_string(indexImage);
						if (ImGui::BeginCombo("Image", currentImage.c_str())) {
							for (int i = 0; i < images.size(); i++) {
								const bool is_selected = (indexImage == i);
								std::string iImage = "Image " + std::to_string(i);
								if (ImGui::Selectable(iImage.c_str(), is_selected)) {
									indexImage = i;
								}

								// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
								if (is_selected) ImGui::SetItemDefaultFocus();
							}
							ImGui::EndCombo();
						}

						if(ImGui::Button("Duplicate"))
						{
							images.push_back(new Image(*images[indexImage]));
						}
						ImGui::EndDisabled();
					}
				}

				if (ImGui::CollapsingHeader("Assign Image to another one"))
				{
					ImGui::BeginDisabled(images.size() < 1);
					{
						static uint64_t sourceImage = 0;
						sourceImage = std::min(sourceImage, images.size() - 1);
						std::string currentSourceImage = "Image " + std::to_string(sourceImage);
						if (ImGui::BeginCombo("Source Image", currentSourceImage.c_str())) {
							for (int i = 0; i < images.size(); i++) {
								const bool is_selected = (sourceImage == i);
								std::string iImage = "Image " + std::to_string(i);
								if (ImGui::Selectable(iImage.c_str(), is_selected)) {
									sourceImage = i;
								}

								// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
								if (is_selected) ImGui::SetItemDefaultFocus();
							}
							ImGui::EndCombo();
						}

						static uint64_t targetImage = 0;
						targetImage = std::min(targetImage, images.size() - 1);
						std::string currentTargetImage = "Image " + std::to_string(targetImage);
						if (ImGui::BeginCombo("Target Image", currentTargetImage.c_str())) {
							for (int i = 0; i < images.size(); i++) {
								const bool is_selected = (targetImage == i);
								std::string iImage = "Image " + std::to_string(i);
								if (ImGui::Selectable(iImage.c_str(), is_selected)) {
									targetImage = i;
								}

								// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
								if (is_selected) ImGui::SetItemDefaultFocus();
							}
							ImGui::EndCombo();
						}

						ImGui::BeginDisabled(targetImage == sourceImage);
						if(ImGui::Button("Assign"))
						{
							images[targetImage] = images[sourceImage];
						}
						ImGui::EndDisabled();
						ImGui::EndDisabled();
					}
				}

				ImGui::End();
			}
		}

		for (int i = 0; i < images.size(); ++i)
		{
			Image* imagePtr = images[i];
			if(imagePtr == nullptr) continue;
			Image& img = *imagePtr;

			std::string imageName = std::string("Image ").append(std::to_string(i));
			bool open = true;
			ImGui::Begin(imageName.c_str(), &open);
			{
				const uint32_t uMin = 0;
				const uint32_t uMax = UINT32_MAX;
				const uint32_t maxChannel = 4;

				uint32_t width = img.GetWidth();
				uint32_t height = img.GetHeight();
				uint32_t channels = img.GetChannels();
				int type = (int) img.GetImageType();

				if (ImGui::DragScalar("Width", ImGuiDataType_U32, &width, 1, &uMin, &uMax, "%d")) {
					img.SetWidth(width);
				}
				if (ImGui::DragScalar("Height", ImGuiDataType_U32, &height, 1, &uMin, &uMax, "%d")) {
					img.SetHeight(height);
				}
				if (ImGui::DragScalar("Channel", ImGuiDataType_U32, &channels, 1, &uMin, &maxChannel, "%d")) {
					img.SetChannels(channels);
				}

				if (ImGui::BeginCombo("Image Type", imageTypeNames[type].c_str())) {
					for (int i = 0; i < imageTypeNames.size(); i++) {
						const bool is_selected = (type == i);
						if (ImGui::Selectable(imageTypeNames[i].c_str(), is_selected)) {
							type = i;
							img.SetImageType((ImageType) type);
						}

						// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
						if (is_selected) ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}



				if (ImGui::Button("Duplicate"))
				{
					images.push_back(new Image(img));
				}

				if (img.HasOpenGLTexture()) {

					auto size = ImGui::GetContentRegionMax();
					size.y = size.x / img.GetRatio();
					ImGui::Image((void *) (intptr_t) img.GetRenderId().value(), size);
					if (ImGui::Button("Delete Texture")) {
						img.DeleteOpenGLTexture();
					}
				} else {
					if (ImGui::Button("Create Texture")) {
						img.CreateOpenGLTexture();
					}
				}
				ImGui::End();
			}

			if(!open)
			{
				delete imagePtr;
				images[i] = nullptr;
			}
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}

	// Delete all the image to avoid memory leaks
	for (auto& image : images) {
		delete image;
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}