#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

int main()
{
	if (!glfwInit()) {
		std::cout << "Failed to Initialize glfw\n";
		return -1;
	}


	return 0;
}
