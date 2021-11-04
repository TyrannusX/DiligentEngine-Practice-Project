#ifndef DESTROYER_H
#define DESTROYER_H

#include <GLFW/glfw3.h>

struct GlfwWindowDestroyer
{
	void operator()(GLFWwindow* ptr)
	{
		glfwDestroyWindow(ptr);
	}
};
#endif