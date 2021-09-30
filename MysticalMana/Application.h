#pragma once
#include <memory>
#include "Window.h"
#include "InputManager.h"
#include "RendererManager.h"

class Application
{
	public:
		Application();
		void Run();

	private:
		std::unique_ptr<Window> window;
		std::unique_ptr<InputManager> inputManager;
		std::unique_ptr<RendererManager> rendererManager;
};

