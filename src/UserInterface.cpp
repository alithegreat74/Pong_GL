#include "UserInterface.h"
#include "ImGUI/imgui.h"

float UI::backgroundColor[4]= { 0.0f, 0.0f, 0.0f,1.0f };
float UI::racketSpeed = 10;

void UI::RenderUI() {
    ImGui::Begin("Debugger", nullptr);
    ImGui::DragFloat4("Color Clear", backgroundColor, 0.05f, 0.0f, 1.0);
    ImGui::InputFloat("Racket Speed", &racketSpeed);
    ImGui::End();
}