#include "aspch.h"
#include "Application.h"

int main()
{
	auto* app = new Aspen::Application("App");
	app->Run();

	delete app;
}