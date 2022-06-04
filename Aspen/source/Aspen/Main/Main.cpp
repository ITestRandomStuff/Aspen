#include <aspch.h>
#include <crtdbg.h>

#include "Aspen/Core/Application.h"

// Basically just The Cherno's code lol

int main(int argc, char** argv)
{
	auto* app = Aspen::CreateApplication(1080, 720, "App");
	app->Run();

	delete app;
}