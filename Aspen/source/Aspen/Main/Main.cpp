#include <aspch.h>

#include <stdlib.h>
#include <crtdbg.h>

#include "Aspen/Core/Application.h"
#include "Aspen/Debug/Log.h"

int main(int argc, char** argv)
{
	auto* app = Aspen::CreateApplication("App");
	app->Run();

	delete app;

	_CrtDumpMemoryLeaks();
}