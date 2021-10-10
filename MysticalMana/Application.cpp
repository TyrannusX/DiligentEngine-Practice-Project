#include "Application.h"
#include "AudioEntity.h"
#include "StaticEntity.h"
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
	//HARD CODED ENTITIES

	//Audio
	AudioEntity audio_entity;
	audio_entity.id = "BACKGROUND_MUSIC";
	audio_entity.file_name = "C:\\GameAssets\\deus-ex-ambient.mp3";

	//Graphics
	StaticEntity static_entity;
	static_entity.id = "TRIANGLE";

	Vertex vertex;
	vertex.position = glm::vec3(1.0f, 1.0f, 0.0f);
	vertex.color = glm::vec3(1.0f, 0.0f, 0.0f);
	static_entity.vertices.push_back(vertex);

	vertex.position = glm::vec3(-1.0f, 1.0f, 0.0f);
	vertex.color = glm::vec3(0.0f, 1.0f, 0.0f);
	static_entity.vertices.push_back(vertex);

	vertex.position = glm::vec3(0.0f, -1.0f, 0.0f);
	vertex.color = glm::vec3(0.0f, 0.0f, 1.0f);
	static_entity.vertices.push_back(vertex);

	static_entity.vertex_buffer_handle = renderer_manager_->CreateVertexBuffer(static_entity.vertices);

	bool app_is_running = true;
	do
	{
		app_is_running = !window_->Poll();
		audio_manager_->PlayAudio(audio_entity);
		renderer_manager_->PaintNextFrame(static_entity);
	} 
	while (app_is_running);
}