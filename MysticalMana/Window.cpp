#include "Window.h"
#include <exception>

Window::Window(int width_in, int height_in, std::string title_in)
{
	width = width_in;
	height = height_in;
	title = title_in;

	if (!glfwInit())
	{
		throw std::exception("Failed to initialize GLFW");
	}

	glfwWindow = std::unique_ptr<GLFWwindow, GlfwWindowDestroyer>(glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr));
	if (!glfwWindow)
	{
		glfwTerminate();
		throw std::exception("Failed to create GLFW window");
	}

	glfwMakeContextCurrent(glfwWindow.get());
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::Poll()
{
	bool shouldCloseWindow = glfwWindowShouldClose(glfwWindow.get());
	glfwPollEvents();
	return shouldCloseWindow;
}

std::unique_ptr<GLFWwindow, GlfwWindowDestroyer>& Window::GetUnderlyingWindow()
{
	return glfwWindow;
}