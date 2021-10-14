#include "InputManager.h"
#include <iostream>

InputManager::InputManager(Window* window)
{
	underlyind_window_ = window->GetUnderlyingWindow();
}

std::vector<UserInputEvents> InputManager::UserInputCheck()
{
	std::vector<UserInputEvents> events;

	if (glfwGetKey(underlyind_window_, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kLeft);
	}
	if (glfwGetKey(underlyind_window_, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kRight);
	}
	if (glfwGetKey(underlyind_window_, GLFW_KEY_UP) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kUp);
	}
	if (glfwGetKey(underlyind_window_, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		events.push_back(UserInputEvents::kLeft);
	}

	return events;
}