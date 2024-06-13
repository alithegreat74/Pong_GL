#pragma once
#include "ImGUI/imgui.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"

namespace UI {
	extern float backgroundColor[4];
	extern float racketSpeed;
	void RenderUI();
}