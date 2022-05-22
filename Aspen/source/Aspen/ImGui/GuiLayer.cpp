#include "aspch.h"
#include "GuiLayer.h"

#include "Aspen/Core/Application.h"

#include "Aspen/Debug/Log.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_glfw.cpp"		// Including this because the compiler can't find them

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_opengl3.cpp"	// Including this because the compiler can't find them

namespace Aspen
{
	GuiLayer::GuiLayer()
		:Layer()
	{
		ASP_LOG("GuiLayer instanced!");
	}
	
	GuiLayer::~GuiLayer()
	{
		ASP_LOG("GuiLayer destroyed!");
	}

	void GuiLayer::OnAttach()
	{
		ASP_LOG("GuiLayer attached!");
	}

	void GuiLayer::OnDetach()
	{
		ASP_LOG("GuiLayer detached!");
		/*ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		ImGui::DestroyContext();*/
	}

	void GuiLayer::OnEvent(Event& e)
	{
		
	}

	void GuiLayer::OnUpdate(float ts)
	{
		// https://www.unknowncheats.me/forum/counterstrike-global-offensive/410311-imgui.html
		// The almighty ImGui gods have destroyed the context
		// Regenerate it!

		// I tried creating the context on attach, but ImGui destroyed the context
		// So i had no option.
		if (!ImGui::GetCurrentContext())
		{
			std::cout << "Created context!\n";

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

			ImGui::StyleColorsDark();

			Application& app = Application::GetApplication();
			GLFWwindow* window = app.GetWindow().GetNativeWindow();

			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 410");
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		bool showDemoWindow = true;
		ImGui::ShowDemoWindow(&showDemoWindow);

		Application& app = Application::GetApplication();
		GLFWwindow* window = app.GetWindow().GetNativeWindow();

		ImGui::Render();
		int displayWidth, displayHeight;
		glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
		glViewport(0, 0, displayWidth, displayHeight);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backUpContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backUpContext);
		}
	}
}