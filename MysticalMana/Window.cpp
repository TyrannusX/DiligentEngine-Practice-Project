#include "Window.h"
#include <exception>

Window::Window(int width_in, int height_in, std::string title_in)
{
	m_width_ = width_in;
	m_height_ = height_in;
	m_title_ = title_in;

	if (!glfwInit())
	{
		throw std::exception("Failed to initialize GLFW");
	}

	/*
	* IMPORTANT
	* Explicitly tell GLFW to not create an OpenGL/Vulkan context itself.
	* This breaks Diligent's contexts
	*/
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	m_glfw_window_ = std::unique_ptr<GLFWwindow, GlfwWindowDestroyer>(glfwCreateWindow(m_width_, m_height_, m_title_.c_str(), nullptr, nullptr));
	if (!m_glfw_window_)
	{
		glfwTerminate();
		throw std::exception("Failed to create GLFW window");
	}
}

Window::~Window()
{
	glfwTerminate();
}

bool Window::Poll()
{
	bool should_close_window = glfwWindowShouldClose(m_glfw_window_.get());
	glfwPollEvents();
	return should_close_window;
}

GLFWwindow* Window::GetUnderlyingWindow()
{
	return m_glfw_window_.get();
}

std::vector<UserInputEvents> Window::UserInputCheck()
{
	std::vector<UserInputEvents> events;

	if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kLeft);
	}
	if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kRight);
	}
	if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_UP) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kUp);
	}
	if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kDown);
	}
	if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_W) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kW);
	}
	if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_S) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kS);
	}

	return events;
}