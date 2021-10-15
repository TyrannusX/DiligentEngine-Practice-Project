#include "Window.h"
#include <exception>

Window::Window(int width_in, int height_in, std::string title_in)
{
	width_ = width_in;
	height_ = height_in;
	title_ = title_in;

	if (!glfwInit())
	{
		throw std::exception("Failed to initialize GLFW");
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	glfw_window_ = std::unique_ptr<GLFWwindow, GlfwWindowDestroyer>(glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr));
	if (!glfw_window_)
	{
		glfwTerminate();
		throw std::exception("Failed to create GLFW window");
	}
}

Window::~Window()
{
	glfwDestroyWindow(glfw_window_.get());
	glfwTerminate();
}

bool Window::Poll()
{
	bool shouldCloseWindow = glfwWindowShouldClose(glfw_window_.get());
	glfwPollEvents();
	return shouldCloseWindow;
}

GLFWwindow* Window::GetUnderlyingWindow()
{
	return glfw_window_.get();
}

std::vector<UserInputEvents> Window::UserInputCheck()
{
	std::vector<UserInputEvents> events;

	if (glfwGetKey(glfw_window_.get(), GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kLeft);
	}
	if (glfwGetKey(glfw_window_.get(), GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kRight);
	}
	if (glfwGetKey(glfw_window_.get(), GLFW_KEY_UP) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kUp);
	}
	if (glfwGetKey(glfw_window_.get(), GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kDown);
	}

	return events;
}