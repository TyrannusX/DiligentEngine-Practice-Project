#include "InputManager.h"
#include <iostream>

InputManager::InputManager(Window* window)
{
	m_underlying_window_ = window->GetUnderlyingWindow();
}

std::vector<UserInputEvents> InputManager::UserInputCheck()
{
	std::vector<UserInputEvents> events;

	if (glfwGetKey(m_underlying_window_, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kLeft);
	}
	if (glfwGetKey(m_underlying_window_, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kRight);
	}
	if (glfwGetKey(m_underlying_window_, GLFW_KEY_UP) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kUp);
	}
	if (glfwGetKey(m_underlying_window_, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kLeft);
	}

	return events;
}