#pragma once
#include <memory>
#include <GLFW\glfw3.h>
#include <set>
#include "UserInputEvents.h"
#include "Window.h"
#include "GlfwWindowDestroyer.h"

class InputManager
{
	public:
		InputManager(Window* window);
		std::set<UserInputEvents> UserInputCheck();
	private:
		GLFWwindow* m_underlying_window_;
};

