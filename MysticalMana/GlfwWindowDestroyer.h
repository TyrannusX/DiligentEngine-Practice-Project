#pragma once
#include <GLFW\glfw3.h>

struct GlfwWindowDestroyer
{
	void operator()(GLFWwindow* ptr)
	{
		glfwDestroyWindow(ptr);
	}
};