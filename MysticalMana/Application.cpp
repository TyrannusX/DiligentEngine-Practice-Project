#include "Application.h"
#include "AudioEntity.h"
#include "StaticEntity.h"
#include <iostream>
#include <algorithm>

Application::Application()
{
	window_ = std::unique_ptr<Window>(new Window(800, 600, "Mystical Mana"));
	input_manager_ = std::unique_ptr<InputManager>(new InputManager(window_.get()));
	renderer_manager_ = std::unique_ptr<RendererManager>(new RendererManager(window_.get()));
	audio_manager_ = std::unique_ptr<AudioManager>(new AudioManager());
}

void Application::Run()
{
	//HARD CODED ENTITIES

	//Audio
	AudioEntity audio_entity;
	audio_entity.id = "BACKGROUND_MUSIC";
	audio_entity.file_name = "C:\\GameAssets\\deus-ex-ambient.mp3";

	//Graphics
	StaticEntity static_entity;
	static_entity.id = "TRIANGLE";
	static_entity.vertices = new Vertex[3];

	Vertex vertex = {};
	vertex.position_x = 0.5f;
	vertex.position_y = 0.5f;
	vertex.position_z = 0.0f;
	vertex.abgr = 0xff0000ff;
	static_entity.vertices[0] = vertex;

	vertex = {};
	vertex.position_x = 0.5f;
	vertex.position_y = -0.5f;
	vertex.position_z = 0.0f;
	vertex.abgr = 0xff00ff00;
	static_entity.vertices[1] = vertex;

	vertex = {};
	vertex.position_x = -0.5f;
	vertex.position_y = 0.5f;
	vertex.position_z = 0.0f;
	vertex.abgr = 0xff00ff00;
	static_entity.vertices[2] = vertex;

	static_entity.indices = new uint16_t[3];
	static_entity.indices[0] = 0;
	static_entity.indices[1] = 1;
	static_entity.indices[2] = 2;

	bool app_is_running = true;
	int x = 0;
	int y = 0;

	do
	{
		app_is_running = !window_->Poll();
		std::vector<UserInputEvents> events = window_->UserInputCheck();

		if (std::find(events.begin(), events.end(), UserInputEvents::kLeft) != events.end())
		{
			x -= 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kRight) != events.end())
		{
			x += 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kUp) != events.end())
		{
			y -= 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kDown) != events.end())
		{
			y += 1;
		}

		audio_manager_->PlayAudio(audio_entity);
		renderer_manager_->PaintNextFrame(static_entity, x, y);
	} 
	while (app_is_running);
}