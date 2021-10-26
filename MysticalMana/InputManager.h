#pragma once
#include <memory>
#include <GLFW\glfw3.h>
#include <vector>
#include "UserInputEvents.h"
#include "Window.h"
#include "GlfwWindowDestroyer.h"

class InputManager
{
	public:
		InputManager(Window* window);
		std::vector<UserInputEvents> UserInputCheck();
	private:
		GLFWwindow* m_underlying_window_;
};

