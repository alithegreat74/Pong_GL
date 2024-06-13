#include "UserInterface.h"
#include "ImGUI/imgui.h"

float UI::backgroundColor[4]= { 0.0f, 0.0f, 0.0f,1.0f };
float UI::racketBPos[2] = { 1.0f,1.0f};
float UI::racketAPos[2] = { 1.0f,1.0f};

void UI::RenderUI() {
    ImGui::Begin("Debugger", nullptr);
    ImGui::DragFloat4("Color Clear", backgroundColor, 0.05f, 0.0f, 1.0);
    ImGui::DragFloat2("Racket A Position", racketAPos, 0.005);
    ImGui::DragFloat2("Racket B Position", racketBPos, 0.005);
    ImGui::End();
}