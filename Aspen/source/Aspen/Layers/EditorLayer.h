#pragma once

#include "Aspen/Layers/GuiLayer.h"

#include "Aspen/Math/Vector2.h"
#include "Aspen/Math/Vector4.h"

namespace Aspen
{
	struct Brush
	{
		Brush() = default;

		Color4f brushColor = Color4f(0.5f, 0.0f, 1.0f, 1.0f);
		float minPressureThickness = 0.0f;
		float maxPressureThickness = 2.0f;
	};

	struct ColorEditorState
	{
		ColorEditorState() = default;

		enum ColorInput { RGB, HSV };

		bool windowOpen = true;
		bool windowUseAlphaBar = true;

		bool windowUseHueWheel = true;

		ColorInput windowClrInput = ColorInput::RGB;
	};

	struct BrushEditorState
	{
		BrushEditorState() = default;

		bool windowOpen = true;
	};

	class EditorLayer : public GuiLayer
	{
	public:
		virtual void OnRender();

		void RenderColorEditor();
		void RenderBrushEditor();

		static inline ColorEditorState& GetColorEditorState() { return s_ClrEditorState; }
		static inline BrushEditorState& GetBrushEditorState() { return s_BrshEditorState; }

	private:
		static Brush s_Brush;
		static ColorEditorState s_ClrEditorState;
		static BrushEditorState s_BrshEditorState;
	};
}