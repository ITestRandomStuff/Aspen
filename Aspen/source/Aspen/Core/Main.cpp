#include "aspch.h"
#include "Application.h"

int main()
{
	auto* app = new Aspen::Application();
	app->Run();

	delete app;
}