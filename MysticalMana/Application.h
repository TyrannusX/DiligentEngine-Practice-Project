#pragma once
#include <memory>
#include "Window.h"
#include "InputManager.h"
#include "RendererManager.h"
#include "AudioManager.h"
#include "AssetManager.h"

class Application
{
	public:
		Application();
		void Run();

	private:
		std::unique_ptr<Window> m_window_;
		std::unique_ptr<InputManager> m_input_manager_;
		std::unique_ptr<RendererManager> m_renderer_manager_;
		std::unique_ptr<AudioManager> m_audio_manager_;
		std::unique_ptr<AssetManager> m_asset_manager_;
};

