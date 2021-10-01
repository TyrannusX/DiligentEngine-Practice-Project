#include "Application.h"
#include "AudioEntity.h"
#include <iostream>

Application::Application()
{
	window_ = std::unique_ptr<Window>(new Window(800, 600, "Mystical Mana"));
	input_manager_ = std::unique_ptr<InputManager>(new InputManager(window_));
	renderer_manager_ = std::unique_ptr<RendererManager>(new RendererManager(window_));
	audio_manager_ = std::unique_ptr<AudioManager>(new AudioManager());
}

void Application::Run()
{
	//DEBUG CODE. HARD CODING ENTITY DATA FOR NOW
	AudioEntity audio_entity;
	audio_entity.file_name = "C:\\GameAssets\\deus-ex-ambient.mp3";

	bool app_is_running = true;
	do
	{
		app_is_running = !window_->Poll();
		audio_manager_->PlayAudio(audio_entity);
	} 
	while (app_is_running);
}