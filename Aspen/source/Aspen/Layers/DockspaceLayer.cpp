#include "aspch.h"
#include "DockspaceLayer.h"

#include "Aspen/Core/Texture.h"

#include <imgui.h>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Aspen/Layers/EditorLayer.h"

bool showImGuiDemoWindow = true;

namespace Aspen
{
    void DockspaceLayer::RenderMenuBar()
    {
        if (ImGui::BeginMainMenuBar())
        {
            RenderFileMenuItem();
            RenderViewMenuItem();
            RenderSettingsMenuItem();

            ImGui::EndMainMenuBar();
        }
    }

    void DockspaceLayer::RenderFileMenuItem()
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::EndMenu();
        }
    }

    void DockspaceLayer::RenderViewMenuItem()
    {
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::BeginMenu("Windows"))
            {
                if (ImGui::MenuItem("Color Editor"))
                {
                    ColorEditorState& state = EditorLayer::GetColorEditorState();
                    state.windowOpen = !state.windowOpen;
                }

                if (ImGui::MenuItem("Brush Editor"))
                {
                    BrushEditorState& state = EditorLayer::GetBrushEditorState();
                    state.windowOpen = !state.windowOpen;
                }

                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
    }

    void DockspaceLayer::RenderSettingsMenuItem()
    {
        if (ImGui::BeginMenu("Settings"))
        {
            ColorEditorState& state = EditorLayer::GetColorEditorState();
            
            if (ImGui::MenuItem("Use Alpha Bar", nullptr, &state.windowUseAlphaBar))
            {
            }

            if (ImGui::MenuItem("Use Hue Wheel", nullptr, &state.windowUseHueWheel))
            {
            }

            ImGui::EndMenu();
        }
    }

	void DockspaceLayer::OnRender()
	{
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags hostWindowFlags = 0;
        hostWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
        hostWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        hostWindowFlags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;

        ImGuiDockNodeFlags dockspaceFlags = 0;
        dockspaceFlags |= ImGuiDockNodeFlags_PassthruCentralNode;

        ImGuiWindowClass windowClass;

        if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
            hostWindowFlags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("Dockspace", nullptr, hostWindowFlags);
        ImGui::PopStyleVar(3);
        
        RenderMenuBar();

        ImGui::DockSpace(ImGui::GetID("Dockspace"), ImVec2(0.0f, 0.0f), dockspaceFlags, &windowClass);

        ImGui::End();

        if (showImGuiDemoWindow)
            ImGui::ShowDemoWindow(&showImGuiDemoWindow);
	}
}