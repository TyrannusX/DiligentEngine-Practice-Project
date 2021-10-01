#pragma once
#include <memory>
#include "Window.h"
#include "InputManager.h"
#include "RendererManager.h"
#include "AudioManager.h"

class Application
{
	public:
		Application();
		void Run();

	private:
		std::unique_ptr<Window> window_;
		std::unique_ptr<InputManager> input_manager_;
		std::unique_ptr<RendererManager> renderer_manager_;
		std::unique_ptr<AudioManager> audio_manager_;

};

