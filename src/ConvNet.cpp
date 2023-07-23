#include <iostream>
#include <GLFW/glfw3.h>

int main()
{
	GLFWwindow* window;

	glfwInit();

	window = glfwCreateWindow(1080, 720, "Hello GLFW", NULL, NULL);

	glfwMakeContextCurrent(window);

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	std::cout << "Hello CMake. morbidly a beast" << std::endl;

	std::cin.get();

	return 0;
}
