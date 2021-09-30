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
		int width;
		int height;
		std::string title;
		std::unique_ptr<GLFWwindow, GlfwWindowDestroyer> glfwWindow;
};
