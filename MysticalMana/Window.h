#pragma once
#include <GLFW\glfw3.h>
#include <memory>
#include <string>
#include <vector>
#include "UserInputEvents.h"
#include "GlfwWindowDestroyer.h"

class Window
{
	public:
		Window(int width_in, int height_in, std::string title_in);
		~Window();
		bool Poll();
		GLFWwindow* GetUnderlyingWindow();
		std::vector<UserInputEvents> UserInputCheck();

	private:
		int width_;
		int height_;
		std::string title_;
		std::unique_ptr<GLFWwindow, GlfwWindowDestroyer> glfw_window_;
};
