#include <iostream>
#include "GameObject.h"
#include "UserInterface.h"
#include "Input.h"

//Configuring the Game object
static GameObject ball;
static Racket racketA;
static Racket racketB;



int main() {
    //Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW";
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Create a window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "PONG", NULL, NULL);

    if (!window) {
        std::cout << "Failed to create a window";
        return -1;
    }
    //Set the window as the current context
    glfwMakeContextCurrent(window);


    //Initialize GLAD
    if (!gladLoadGL()) {
        std::cout << "Failed to load glad";
        return -1;
    }

    //Set the viewport and the background color
    glViewport(0, 0, 1280, 720);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    //Callback Function Set Start
    glfwSetKeyCallback(window, InputManager::Get().KeyboardCallback);
    //Callback Function Set Stop

    //Configuring the shader files and shader program
    Shader vertexShader("src/Shaders/VertexShader.glsl",GL_VERTEX_SHADER);
    Shader fragmentShader("src/Shaders/FragmentShader.glsl",GL_FRAGMENT_SHADER);
    ShaderProgram program(vertexShader, fragmentShader);


    //Configuring the Textures
    TextureLoader loader;
    Texture2D defaultTexture(loader.LoadImage("src/Textures/DefaultTexture.png"));
    Texture2D defaultCircleTexture(loader.LoadImage("src/Textures/DefaultTextureCircle.png"));


    // Initialize ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Initialize ImGui for GLFW and OpenGL
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Setup ImGui style
    ImGui::StyleColorsDark();
    
    //Setting the positions

    //Running the start funcitons
    ball.Start(glm::vec4(1.0), glm::vec3(0.0), glm::vec3(0.08, 0.145, 1.0));
    racketA.Start(glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec3(-32.0, 0, 0), glm::vec3(0.03, 0.3, 1.0));
    racketB.Start(glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec3(32.0, 0, 0), glm::vec3(0.03, 0.3, 1.0));
    
    racketA.SetInputs(GLFW_KEY_W, GLFW_KEY_S);
    racketB.SetInputs(GLFW_KEY_UP, GLFW_KEY_DOWN);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(UI::backgroundColor[0], UI::backgroundColor[1], UI::backgroundColor[2], UI::backgroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);


        //Render Game Objects start

        ball.Render(defaultCircleTexture, program);
        racketA.Render(defaultTexture,program);
        racketB.Render(defaultTexture, program);

        //Render Game Objects End


        //User Interface Start
        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // Render UI
        UI::RenderUI();
        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //User Interface End

        
        //Swap the calculated color with the next color
        glfwSwapBuffers(window);
        //Check for events such as closing the window
        glfwPollEvents();

        Time::Get().CalculateTime();
    }

    // Cleanup ImGui
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    //Destroy GLFW
    glfwTerminate();
    return 0;
}
