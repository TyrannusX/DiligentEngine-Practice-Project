#include "Application.h"
#include <iostream>

Application::Application()
{
	window = std::unique_ptr<Window>(new Window(800, 600, "Mystical Mana"));
	inputManager = std::unique_ptr<InputManager>(new InputManager(window));
	rendererManager = std::unique_ptr<RendererManager>(new RendererManager(window));
}

void Application::Run()
{
	bool app_is_running = true;
	do
	{
		app_is_running = !window->Poll();
	} 
	while (app_is_running);
}