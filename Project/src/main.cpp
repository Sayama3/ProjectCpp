//
// Created by ianpo on 17/01/2024.
//

#include <iostream>
#include <vector>
#include "Core/Application.hpp"

using namespace PC;

int main(int argc, char** argv)
{
	std::vector<std::string> arguments(argc);
	for (int i = 0; i < argc; ++i) {
		arguments[i] = argv[i];
	}

	ApplicationSpecification appSpec(argc, argv);

	Application* app = new Application(appSpec);

	app->Run();

	delete app;

	return 0;
}
