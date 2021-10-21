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
	static_entity.vertices = new Vertex[8];

	//Define entity vertex data
	Vertex vertex = {};
	vertex.position = Diligent::float3(-1, -1, -1);
	vertex.color = Diligent::float4(1, 0, 0, 1);
	static_entity.vertices[0] = vertex;

	vertex = {};
	vertex.position = Diligent::float3(-1, +1, -1);
	vertex.color = Diligent::float4(0, 1, 0, 1);
	static_entity.vertices[1] = vertex;

	vertex = {};
	vertex.position = Diligent::float3(+1, +1, -1);
	vertex.color = Diligent::float4(0, 0, 1, 1);
	static_entity.vertices[2] = vertex;

	vertex = {};
	vertex.position = Diligent::float3(+1, -1, -1);
	vertex.color = Diligent::float4(1, 1, 1, 1);
	static_entity.vertices[3] = vertex;

	vertex = {};
	vertex.position = Diligent::float3(-1, -1, +1);
	vertex.color = Diligent::float4(1, 1, 0, 1);
	static_entity.vertices[4] = vertex;

	vertex = {};
	vertex.position = Diligent::float3(-1, +1, +1);
	vertex.color = Diligent::float4(0, 1, 1, 1);
	static_entity.vertices[5] = vertex;

	vertex = {};
	vertex.position = Diligent::float3(+1, +1, +1);
	vertex.color = Diligent::float4(1, 0, 1, 1);
	static_entity.vertices[6] = vertex;

	vertex = {};
	vertex.position = Diligent::float3(+1, -1, +1);
	vertex.color = Diligent::float4(0.2f, 0.2f, 0.2f, 1);
	static_entity.vertices[7] = vertex;

	//Define entity vertex indices for drawing
	static_entity.indices = new Diligent::Uint32[36]
	{
		2,0,1, 2,3,0,
		4,6,5, 4,7,6,
		0,7,4, 0,3,7,
		1,0,4, 1,4,5,
		1,5,2, 5,6,2,
		3,6,7, 3,2,6
	};

	//Set buffers on entity
	static_entity.vertex_buffer = renderer_manager_->CreateVertexBuffer(static_entity);
	static_entity.index_buffer = renderer_manager_->CreateIndexBuffer(static_entity);

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
		renderer_manager_->UpdateEntity();
		renderer_manager_->PaintNextFrame(static_entity, x, y);
	} 
	while (app_is_running);
}