#include <iostream>
#include "GameObject.h"
#include "UserInterface.h"
#include "Input.h"
#include "AudioManager.h"



/// <summary>
/// So this is a game of pong
/// in this game we made three 2d game object which have a color and a texture 
/// basically this is a sprite from normal game engines
/// btw I had to make the window unresizable because it would have messed the scale of our game objects and UI
/// I'm using ImGUI library for my UI
/// </summary>



//Configuring the Game object
static Ball ball;
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

    //Configuring the shader files and shader programs
    Shader vertexShader("src/Shaders/VertexShader.glsl",GL_VERTEX_SHADER);
    Shader fragmentShader("src/Shaders/FragmentShader.glsl",GL_FRAGMENT_SHADER);
    Shader particleVertexShader("src/Shaders/ParticleVertexShader.glsl", GL_VERTEX_SHADER);
    Shader particleFragmentShader("src/Shaders/ParticleFragmentShader.glsl", GL_FRAGMENT_SHADER);
    ShaderProgram program(vertexShader, fragmentShader);
    ShaderProgram particleProgram(particleVertexShader, particleFragmentShader);


    //Configuring the Textures
    TextureLoader loader;
    Texture2D defaultTexture(loader.LoadImage("src/Textures/DefaultTexture.png"));
    Texture2D defaultCircleTexture(loader.LoadImage("src/Textures/DefaultTextureCircle.png"));
    Texture2D particleTexture(loader.LoadImage("src/Textures/particle.png"));

    
    //Initialzie Free Type End
    UI::Init(window);

    //Initialize the particle emitter
    Effects::ParticleEmitter emitter;

    //Running the start funcitons
    ball.Start(glm::vec4(1.0), glm::vec3(0.0), glm::vec3(0.04, 0.075, 1.0));
    racketA.Start(glm::vec4(0.0, 1.0, 0.0, 1.0), glm::vec3(-32.0, 0, 0), glm::vec3(0.03, 0.3, 1.0));
    racketB.Start(glm::vec4(0.0, 0.0, 1.0, 1.0), glm::vec3(32.0, 0, 0), glm::vec3(0.03, 0.3, 1.0));

    //Input configuration
    racketA.SetInputs(GLFW_KEY_W, GLFW_KEY_S);
    racketB.SetInputs(GLFW_KEY_UP, GLFW_KEY_DOWN);
    InputManager::Get().AddListerners(GLFW_KEY_ESCAPE, GameManager::OnPause);   //To pause or unpause the game whenever the escape key is pressed

    //Add the collidable objects to the collision detector
    Collision::objects.push_back(&racketA);
    Collision::objects.push_back(&racketB);

    //Setting the ball's initial speed
    Time::Get().CalculateTime();
    ball.direction = glm::vec3(1, -1, 0);

    //Play the game music on a loop
    Audio::PlayAudio("src/Audio/breakout.mp3",true);


    //Make the window resizable
    glfwSetWindowAttrib(window, GLFW_RESIZABLE, false);
    while (!glfwWindowShouldClose(window)) {
        glClearColor(UI::backgroundColor[0], UI::backgroundColor[1], UI::backgroundColor[2], UI::backgroundColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);


        //User Interface Start
        UI::RenderUI(window);
        
        //User Interface End

        //Render The game Effects start
        Effects::RenderEffects();
        if(UI::ballTrail && !GameManager::pause)
            emitter.RenderParticles(particleProgram, ball, defaultCircleTexture);
        //Render the game effects end
        
        //Render Game Objects start

        //Render the ball based on it's chosen shape
        switch (UI::ballShape)
        {
        case 0:
            ball.Render(defaultCircleTexture, program);
            break;
        case 1:
            ball.Render(defaultTexture, program);
            break;
        default:
            ball.Render(defaultCircleTexture, program);
            break;
        }
        ball.Render(defaultCircleTexture, program);
        racketA.Render(defaultTexture,program);
        racketB.Render(defaultTexture, program);
        //Render Game Objects End


        //Swap the calculated color with the next color
        glfwSwapBuffers(window);
        //Check for events such as closing the window
        glfwPollEvents();

        //Calculate delta time
        Time::Get().CalculateTime();
    }

    Audio::Cleanup();
    UI::CleanUp();
    //Destroy GLFW
    glfwTerminate();
    return 0;
}
