#include "UserInterface.h"

float UI::backgroundColor[4]= { 0.0f, 0.0f, 0.0f,1.0f };
float UI::racketSpeed = 5;
float UI::ballSpeed = 5;

unsigned int UI::scoreA=0, UI::scoreB=0;

ImFont* UI::scoreFont;
ImFont* UI::menuFont;


void UI::RenderUI(GLFWwindow* window) {

    // Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    //Show Score
    ScoreWindow();
    
    //Show debug window
    DebugWindow();


    // Render ImGui
    ImGui::Render();

    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
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

    scoreFont = io.Fonts->AddFontFromFileTTF("src/fonts/arial.ttf", 82.0f);
    menuFont = io.Fonts->AddFontFromFileTTF("src/fonts/arial.ttf", 24.0);


    // Setup ImGui style
    ImGui::StyleColorsDark();
}

void UI::DebugWindow()
{
    ImGui::PushFont(menuFont);
    ImGui::Begin("Debugger", nullptr);
    ImGui::DragFloat4("Color Clear", backgroundColor, 0.05f, 0.0f, 1.0);
    ImGui::DragFloat("Racket Speed", &racketSpeed,0.1f);
    ImGui::DragFloat("Ball Speed", &ballSpeed,0.1f);
    ImGui::PopFont();
    ImGui::End();
}

void UI::ScoreWindow()
{
    ImGui::Begin("##hidden", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground);
    ImGui::SetCursorPos(ImVec2(520, 0));
    ImGui::PushFont(scoreFont);

    std::string score = std::to_string(scoreA) + "\t" + std::to_string(scoreB);
    ImGui::Text(score.c_str());
    ImGui::PopFont();
    ImGui::End();
}

void UI::CleanUp()
{
    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
