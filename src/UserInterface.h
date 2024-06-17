#pragma once
#include "ImGUI/imgui.h"
#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw.h"
#include "ImGUI/imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>

namespace UI {
	extern float backgroundColor[4];
	extern float racketSpeed;
	extern float ballSpeed;
	extern unsigned int scoreA, scoreB;
	extern ImFont* scoreFont;
	extern ImFont* menuFont;
	void RenderUI(GLFWwindow*window);
	void Init(GLFWwindow* window);

	void DebugWindow();
	void ScoreWindow();
	void CleanUp();
}