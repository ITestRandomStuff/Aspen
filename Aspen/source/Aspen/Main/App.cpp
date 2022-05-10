#include "aspch.h"
#include "Aspen/Core/Application.h"

namespace Aspen
{
	void Application::OnUpdate()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glVertex2f(-0.5f, -0.5f);
		glEnd();
	}
}