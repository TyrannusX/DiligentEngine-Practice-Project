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

	//Define entity vertex data
	Vertex vertex = {};
	vertex.position = Diligent::float3(-1, -1, -1);
	vertex.color = Diligent::float4(1, 0, 0, 1);
	static_entity.vertices.push_back(vertex);

	vertex = {};
	vertex.position = Diligent::float3(-1, +1, -1);
	vertex.color = Diligent::float4(0, 1, 0, 1);
	static_entity.vertices.push_back(vertex);

	vertex = {};
	vertex.position = Diligent::float3(+1, +1, -1);
	vertex.color = Diligent::float4(0, 0, 1, 1);
	static_entity.vertices.push_back(vertex);

	vertex = {};
	vertex.position = Diligent::float3(+1, -1, -1);
	vertex.color = Diligent::float4(1, 1, 1, 1);
	static_entity.vertices.push_back(vertex);

	vertex = {};
	vertex.position = Diligent::float3(-1, -1, +1);
	vertex.color = Diligent::float4(1, 1, 0, 1);
	static_entity.vertices.push_back(vertex);

	vertex = {};
	vertex.position = Diligent::float3(-1, +1, +1);
	vertex.color = Diligent::float4(0, 1, 1, 1);
	static_entity.vertices.push_back(vertex);

	vertex = {};
	vertex.position = Diligent::float3(+1, +1, +1);
	vertex.color = Diligent::float4(1, 0, 1, 1);
	static_entity.vertices.push_back(vertex);

	vertex = {};
	vertex.position = Diligent::float3(+1, -1, +1);
	vertex.color = Diligent::float4(0.2f, 0.2f, 0.2f, 1);
	static_entity.vertices.push_back(vertex);

	//Define entity vertex indices for drawing
	static_entity.indices = {
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
	Diligent::Vector3<float> cameraVector(0.0f, 0.0f, 5.0f);

	do
	{
		app_is_running = !window_->Poll();
		std::vector<UserInputEvents> events = window_->UserInputCheck();

		if (std::find(events.begin(), events.end(), UserInputEvents::kLeft) != events.end())
		{
			cameraVector.x += 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kRight) != events.end())
		{
			cameraVector.x -= 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kUp) != events.end())
		{
			cameraVector.z -= 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kDown) != events.end())
		{
			cameraVector.z += 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kS) != events.end())
		{
			cameraVector.y += 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kW) != events.end())
		{
			cameraVector.y -= 1;
		}

		audio_manager_->PlayAudio(audio_entity);
		renderer_manager_->UpdateWorld(cameraVector);
		renderer_manager_->PaintNextFrame(static_entity);
	} 
	while (app_is_running);
}