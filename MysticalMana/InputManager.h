#pragma once
#include <memory>
#include <GLFW\glfw3.h>
#include "Window.h"

class InputManager
{
	public:
		InputManager(std::unique_ptr<Window>& window);
		static void KeyCallback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
};

