#include "InputManager.h"
#include <iostream>

void InputManager::KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
	std::cout << "Key pressed!!" << std::endl;
}

InputManager::InputManager(std::unique_ptr<Window>& window)
{
	std::unique_ptr<GLFWwindow, GlfwWindowDestroyer>& underlyingWindow = window->GetUnderlyingWindow();
	glfwSetKeyCallback(underlyingWindow.get(), KeyCallback);
}