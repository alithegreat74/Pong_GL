#include "UserInterface.h"

float UI::backgroundColor[4]= { 0.0f, 0.0f, 0.0f,1.0f };
float UI::racketSpeed = 10;
void UI::RenderUI() {

    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    DebugWindow();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::Init(GLFWwindow*window)
{
    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Initialize ImGui for GLFW and OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    // Setup ImGui style
    ImGui::StyleColorsDark();
}

void UI::DebugWindow()
{
    ImGui::Begin("Debugger", nullptr);
    ImGui::DragFloat4("Color Clear", backgroundColor, 0.05f, 0.0f, 1.0);
    ImGui::InputFloat("Racket Speed", &racketSpeed);
    ImGui::End();
}

void UI::CleanUp()
{
    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
