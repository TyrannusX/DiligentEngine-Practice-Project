#include "InputManager.h"
#include <iostream>

InputManager::InputManager(MysticalMana::Window* window)
{
	m_underlying_window_ = window->GetUnderlyingWindow();
}

std::set<UserInputEvents> InputManager::UserInputCheck()
{
	std::set<UserInputEvents> events;

	if (glfwGetKey(m_underlying_window_, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		events.insert(UserInputEvents::kLeft);
	}
	if (glfwGetKey(m_underlying_window_, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		events.insert(UserInputEvents::kRight);
	}
	if (glfwGetKey(m_underlying_window_, GLFW_KEY_UP) == GLFW_PRESS)
	{
		events.insert(UserInputEvents::kUp);
	}
	if (glfwGetKey(m_underlying_window_, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		events.insert(UserInputEvents::kLeft);
	}

	return events;
}