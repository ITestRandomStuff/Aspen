#include "aspch.h"
#include "EditorLayer.h"

#include <imgui_internal.h>

#define ASP_CENTER_ALIGN() ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x)
#define ASP_END_CENTER_ALIGN() ImGui::PopItemWidth()

namespace Aspen
{
	Brush EditorLayer::s_Brush;
	ColorEditorState EditorLayer::s_ClrEditorState;
	BrushEditorState EditorLayer::s_BrshEditorState;

	// Unused.
	bool ColorPicker4U8(const char* label, Color4<uint8_t>& col, ImGuiColorEditFlags flags = 0, Color4<uint8_t>tint_clr = Color4<uint8_t>())
	{
		Color4f clr = ((Color4f)col) / 255.0f;
		Color4f tint = ((Color4f)tint_clr) / 255.0f;

		bool result = ImGui::ColorPicker4(label, (float*)&clr, flags, (float*)&tint);

		col = (Color4<uint8_t>)(clr * 255.0f);
		return result;
	}

	Vector4f ConvertRGBToHSV(const Vector4f& rgb)
	{
		Vector4f ret;
		ImGui::ColorConvertRGBtoHSV(rgb.r, rgb.g, rgb.b, ret.h, ret.s, ret.v);

		return ret;
	}

	Vector4f ConvertHSVToRGB(const Vector4f& hsv)
	{
		Vector4f ret;
		ImGui::ColorConvertHSVtoRGB(hsv.h, hsv.s, hsv.v, ret.r, ret.g, ret.b);

		return ret;
	}

	void EditorLayer::RenderColorEditor()
	{
		ImGuiWindowFlags colorEditorFlags = 0;
		colorEditorFlags |= ImGuiWindowFlags_NoScrollbar;

		if (!s_ClrEditorState.windowOpen) return;
		if (ImGui::Begin("Color Editor", &s_ClrEditorState.windowOpen, colorEditorFlags))
		{
			// Color edit flags.
			ImGuiColorEditFlags clrEditFlags = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview;
			if (s_ClrEditorState.windowUseHueWheel)							{ clrEditFlags |= ImGuiColorEditFlags_PickerHueWheel; }
			if (s_ClrEditorState.windowUseAlphaBar)							{ clrEditFlags |= ImGuiColorEditFlags_AlphaBar; }			

			ASP_CENTER_ALIGN();
			
			// Color Button
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3);
			ImVec2 regionAvail = ImGui::GetContentRegionAvail();

			ImGui::ColorButton(
				"Color",
				s_Brush.brushColor,
				ImGuiColorEditFlags_AlphaPreviewHalf,
				ImVec2(regionAvail.x, regionAvail.x * 0.1f)
			);

			ImGui::PopStyleVar(1);

			// Color Picker
			ImGui::ColorPicker4("", (float*)&s_Brush.brushColor, clrEditFlags);

			// Color Input
			const char* comboInputItems[] = { "RGB", "HSV" };
			if (ImGui::Combo("Color Input", (int*)&s_ClrEditorState.windowClrInput, comboInputItems, 2))
			{
			}

			// Drag Floats (Inputs)
			bool isColorInputHSV = s_ClrEditorState.windowClrInput == ColorEditorState::HSV;
			ImGuiSliderFlags sliderFlags = ImGuiSliderFlags_ClampOnInput;

			if (isColorInputHSV)
			{
				ImGui::ColorConvertRGBtoHSV(s_Brush.brushColor.r, s_Brush.brushColor.g, s_Brush.brushColor.b, s_Brush.brushColor.h, s_Brush.brushColor.s, s_Brush.brushColor.v);

				ImGui::DragFloat("##ColorDragFloat1##", (float*)&s_Brush.brushColor.h, 0.01f, 0.0f, 1.0f, "H: %.3f", sliderFlags);
				ImGui::DragFloat("##ColorDragFloat2##", (float*)&s_Brush.brushColor.s, 0.01f, 0.0f, 1.0f, "S: %.3f", sliderFlags);
				ImGui::DragFloat("##ColorDragFloat3##", (float*)&s_Brush.brushColor.v, 0.01f, 0.0f, 1.0f, "V: %.3f", sliderFlags);

				ImGui::ColorConvertHSVtoRGB(s_Brush.brushColor.h, s_Brush.brushColor.s, s_Brush.brushColor.v, s_Brush.brushColor.r, s_Brush.brushColor.g, s_Brush.brushColor.b);
			}
			else
			{
				ImGui::DragFloat("##ColorDragFloat1##", (float*)&s_Brush.brushColor.r, 0.01f, 0.0f, 1.0f, "R: %.3f", sliderFlags);
				ImGui::DragFloat("##ColorDragFloat2##", (float*)&s_Brush.brushColor.g, 0.01f, 0.0f, 1.0f, "G: %.3f", sliderFlags);
				ImGui::DragFloat("##ColorDragFloat3##", (float*)&s_Brush.brushColor.b, 0.01f, 0.0f, 1.0f, "B: %.3f", sliderFlags);
			}

			ASP_END_CENTER_ALIGN();
		}

		ImGui::End();
	}

	void EditorLayer::RenderBrushEditor()
	{
		ImGuiWindowFlags brushEditorFlags = 0;

		if (!s_BrshEditorState.windowOpen) return;
		if (ImGui::Begin("Brush Editor", &s_BrshEditorState.windowOpen, brushEditorFlags))
		{
			ImGuiWindow* window = ImGui::GetCurrentWindow();
			ImDrawList* drawList = ImGui::GetWindowDrawList();
			ImVec2 pos = window->DC.CursorPos;

			ImVec2 size = ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().x * 0.5f);

			float border = 10.0f;
			
			drawList->AddRectFilled(
				pos,
				Vector2f(pos) + size,
				ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, 1.0f)),
				0.5f
			);

			float halfThickness = s_Brush.maxPressureThickness * 0.5f;
			/*drawList->AddBezierCurve(
				Vector2f(border		    ,		   size.y * 0.5f) + pos,
				Vector2f(size.x * 0.25f ,		   halfThickness) + pos,
				Vector2f(size.x * 0.5f  , size.y + halfThickness) + pos,
				Vector2f(size.x - border,		   size.y * 0.5f) + pos,
				ImGui::ColorConvertFloat4ToU32(s_Brush.brushColor),
				1.0f
			);
			
			drawList->AddBezierCurve(
				Vector2f(border		    ,		   size.y * 0.5f) + pos,
				Vector2f(size.x * 0.25f ,   0.0f - halfThickness) + pos,
				Vector2f(size.x * 0.5f  , size.y - halfThickness) + pos,
				Vector2f(size.x - border,		   size.y * 0.5f) + pos,
				ImGui::ColorConvertFloat4ToU32(s_Brush.brushColor),
				1.0f
			);*/

			// Temporary.
			// Fill the thing
			for (size_t i = 0; i < s_Brush.maxPressureThickness; ++i)
			{
				drawList->AddBezierCurve(
					Vector2f(border, size.y * 0.5f) + pos,
					Vector2f(size.x * 0.25f, halfThickness - i) + pos,
					Vector2f(size.x * 0.5f, size.y + halfThickness - i) + pos,
					Vector2f(size.x - border, size.y * 0.5f) + pos,
					ImGui::ColorConvertFloat4ToU32(s_Brush.brushColor),
					1.0f
				);
			}

			ASP_CENTER_ALIGN();

			ImRect bb = ImRect(pos, Vector2f(pos) + size);
			ImGui::ItemSize(size, 0);
			ImGui::ItemAdd(bb, 0);

			ImGuiSliderFlags sliderFlags = ImGuiSliderFlags_ClampOnInput;

			ImGui::DragFloat("##ThicknessDragFloat##", (float*)&s_Brush.maxPressureThickness, 0.05f, 0.0f, 20.0f, "Thickness: %.3f", sliderFlags);

			ASP_END_CENTER_ALIGN();
		}

		ImGui::End();
	}

	void EditorLayer::OnRender()
	{
		RenderColorEditor();
		RenderBrushEditor();
	}
}