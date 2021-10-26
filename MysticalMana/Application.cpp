#include "Application.h"
#include "AudioEntity.h"
#include "StaticEntity.h"
#include <iostream>
#include <algorithm>

Application::Application()
{
	m_window_ = std::unique_ptr<Window>(new Window(800, 600, "Mystical Mana"));
	m_input_manager_ = std::unique_ptr<InputManager>(new InputManager(m_window_.get()));
	m_renderer_manager_ = std::unique_ptr<RendererManager>(new RendererManager(m_window_.get()));
	m_audio_manager_ = std::unique_ptr<AudioManager>(new AudioManager());
}

void Application::Run()
{
	//HARD CODED ENTITIES

	//Audio
	AudioEntity audio_entity;
	audio_entity.m_id = "BACKGROUND_MUSIC";
	audio_entity.m_file_name = "C:\\GameAssets\\deus-ex-ambient.mp3";

	//Graphics
	StaticEntity static_entity;
	static_entity.m_id = "TRIANGLE";

	//Define entity vertex data
	Vertex vertex = {};
	vertex.m_position = Diligent::float3(-1, -1, -1);
	vertex.m_color = Diligent::float4(1, 0, 0, 1);
	static_entity.m_vertices.push_back(vertex);

	vertex = {};
	vertex.m_position = Diligent::float3(-1, +1, -1);
	vertex.m_color = Diligent::float4(0, 1, 0, 1);
	static_entity.m_vertices.push_back(vertex);

	vertex = {};
	vertex.m_position = Diligent::float3(+1, +1, -1);
	vertex.m_color = Diligent::float4(0, 0, 1, 1);
	static_entity.m_vertices.push_back(vertex);

	vertex = {};
	vertex.m_position = Diligent::float3(+1, -1, -1);
	vertex.m_color = Diligent::float4(1, 1, 1, 1);
	static_entity.m_vertices.push_back(vertex);

	vertex = {};
	vertex.m_position = Diligent::float3(-1, -1, +1);
	vertex.m_color = Diligent::float4(1, 1, 0, 1);
	static_entity.m_vertices.push_back(vertex);

	vertex = {};
	vertex.m_position = Diligent::float3(-1, +1, +1);
	vertex.m_color = Diligent::float4(0, 1, 1, 1);
	static_entity.m_vertices.push_back(vertex);

	vertex = {};
	vertex.m_position = Diligent::float3(+1, +1, +1);
	vertex.m_color = Diligent::float4(1, 0, 1, 1);
	static_entity.m_vertices.push_back(vertex);

	vertex = {};
	vertex.m_position = Diligent::float3(+1, -1, +1);
	vertex.m_color = Diligent::float4(0.2f, 0.2f, 0.2f, 1);
	static_entity.m_vertices.push_back(vertex);

	//Define entity vertex indices for drawing
	static_entity.m_indices = {
		2,0,1, 2,3,0,
		4,6,5, 4,7,6,
		0,7,4, 0,3,7,
		1,0,4, 1,4,5,
		1,5,2, 5,6,2,
		3,6,7, 3,2,6
	};
	

	//Set buffers on entity
	static_entity.m_vertex_buffer = m_renderer_manager_->CreateVertexBuffer(static_entity);
	static_entity.m_index_buffer = m_renderer_manager_->CreateIndexBuffer(static_entity);

	bool app_is_running = true;
	Diligent::Vector3<float> camera_vector(0.0f, 0.0f, 5.0f);

	do
	{
		app_is_running = !m_window_->Poll();
		std::vector<UserInputEvents> events = m_window_->UserInputCheck();

		if (std::find(events.begin(), events.end(), UserInputEvents::kLeft) != events.end())
		{
			camera_vector.x += 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kRight) != events.end())
		{
			camera_vector.x -= 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kUp) != events.end())
		{
			camera_vector.z -= 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kDown) != events.end())
		{
			camera_vector.z += 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kS) != events.end())
		{
			camera_vector.y += 1;
		}
		if (std::find(events.begin(), events.end(), UserInputEvents::kW) != events.end())
		{
			camera_vector.y -= 1;
		}

		m_audio_manager_->PlayAudio(audio_entity);
		m_renderer_manager_->UpdateWorld(camera_vector);
		m_renderer_manager_->PaintNextFrame(static_entity);
	} 
	while (app_is_running);
}