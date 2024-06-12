#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW";
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(1280, 720, "PONG", NULL,NULL);

	if (!window) {
		std::cout << "Failed to create a window";
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) {
		std::cout << "Failed to load glad";
		return -1;
	}

	glViewport(0, 0, 1280, 720);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}