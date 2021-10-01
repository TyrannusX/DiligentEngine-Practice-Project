#pragma once
#include <GLFW\glfw3.h>
#include <memory>
#include <string>
#include "GlfwWindowDestroyer.h"

class Window
{
	public:
		Window(int width_in, int height_in, std::string title_in);
		~Window();
		bool Poll();
		std::unique_ptr<GLFWwindow, GlfwWindowDestroyer>& GetUnderlyingWindow();
	private:
		int width_;
		int height_;
		std::string title_;
		std::unique_ptr<GLFWwindow, GlfwWindowDestroyer> glfw_window_;
};
