#include "Window.h"
#include <exception>
#include <iostream>

namespace MysticalMana
{
	Window::Window(int width_in, int height_in, std::string title_in)
	{
		m_width_ = width_in;
		m_height_ = height_in;
		m_title_ = title_in;

		if (!glfwInit())
		{
			throw std::exception();
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
			throw std::exception();
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

	GLFWwindow *Window::GetUnderlyingWindow()
	{
		return m_glfw_window_.get();
	}

	std::unordered_map<UserInputEvents, bool> Window::UserInputCheck()
	{
		std::unordered_map<UserInputEvents, bool> events;

		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			events[UserInputEvents::kLeft] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			events[UserInputEvents::kRight] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_UP) == GLFW_PRESS)
		{
			events[UserInputEvents::kUp] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			events[UserInputEvents::kDown] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_W) == GLFW_PRESS)
		{
			events[UserInputEvents::kW] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_S) == GLFW_PRESS)
		{
			events[UserInputEvents::kS] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_Q) == GLFW_PRESS)
		{
			events[UserInputEvents::kQ] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_E) == GLFW_PRESS)
		{
			events[UserInputEvents::kE] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_A) == GLFW_PRESS)
		{
			events[UserInputEvents::kA] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_D) == GLFW_PRESS)
		{
			events[UserInputEvents::kD] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_Z) == GLFW_PRESS)
		{
			events[UserInputEvents::kZ] = true;
		}
		if (glfwGetKey(m_glfw_window_.get(), GLFW_KEY_C) == GLFW_PRESS)
		{
			events[UserInputEvents::kC] = true;
		}

		return events;
	}

	double Window::GetCurrentTime()
	{
		return glfwGetTime();
	}
}