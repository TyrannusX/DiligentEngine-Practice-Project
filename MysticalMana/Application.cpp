#include "Application.h"
#include "AudioEntity.h"
#include "StaticEntity.h"
#include <iostream>
#include <algorithm>
#include <fstream>

Application::Application()
{
	m_window_ = std::unique_ptr<MysticalMana::Window>(new MysticalMana::Window(800, 600, "Mystical Mana"));
	m_input_manager_ = std::unique_ptr<InputManager>(new InputManager(m_window_.get()));
	m_renderer_manager_ = std::unique_ptr<RendererManager>(new RendererManager(m_window_.get()));
	m_audio_manager_ = std::unique_ptr<AudioManager>(new AudioManager());
	m_asset_manager_ = std::unique_ptr<AssetManager>(new AssetManager());
}

void Application::Run()
{
	//HARD CODED ENTITIES
	//Audio
	AudioEntity audio_entity;
	audio_entity.m_id = "BACKGROUND_MUSIC";
	audio_entity.m_file_name = "/media/rr-linux/Blade 15 SSD/GameAssets/deus-ex-ambient.wav";
	audio_entity.background_music = m_audio_manager_->LoadMusic(audio_entity.m_file_name);

	//Graphics
	StaticEntity static_entity;
	static_entity.m_id = "MY_OBJECT";
	static_entity.mesh_file_name = "/media/rr-linux/Blade 15 SSD/GameAssets/viking_room.obj";

	//Define entity vertex data
	static_entity.m_vertices = m_asset_manager_->GetMeshVertices(static_entity.mesh_file_name);

	//Set buffers on entity
	static_entity.m_vertex_buffer = m_renderer_manager_->CreateVertexBuffer(static_entity);

	//Set texture on entity
	static_entity.m_texture = m_renderer_manager_->CreateTextureFromFile("/media/rr-linux/Blade 15 SSD/GameAssets/viking_room.png");

	bool app_is_running = true;
	Diligent::Vector3<float> camera_vector(0.0f, 0.0f, 2.0f);
	Diligent::Vector3<float> camera_rotation_vector(-1.6f, -6.3f, 1.5f);

	//Configure FPS
	const double frame_limit = 1.0 / 60.0;
	double last_update_time = 0;
	double last_frame_time = 0;

	do
	{
		double now = m_window_->GetCurrentTime();
		double delta_time = now - last_update_time;

		app_is_running = !m_window_->Poll();

		if ((now - last_frame_time) >= frame_limit)
		{
			std::unordered_map<UserInputEvents, bool> events = m_window_->UserInputCheck();

			if (events[UserInputEvents::kLeft])
			{
				camera_vector.x += 0.1;
			}
			if (events[UserInputEvents::kRight])
			{
				camera_vector.x -= 0.1;
			}
			if (events[UserInputEvents::kUp])
			{
				camera_vector.z -= 0.1;
			}
			if (events[UserInputEvents::kDown])
			{
				camera_vector.z += 0.1;
			}
			if (events[UserInputEvents::kS])
			{
				camera_vector.y += 0.1;
			}
			if (events[UserInputEvents::kW])
			{
				camera_vector.y -= 0.1;
			}
			if (events[UserInputEvents::kQ])
			{
				camera_rotation_vector.y += 0.01;
			}
			if (events[UserInputEvents::kE])
			{
				camera_rotation_vector.y -= 0.01;
			}
			if (events[UserInputEvents::kA])
			{
				camera_rotation_vector.x += 0.01;
			}
			if (events[UserInputEvents::kD])
			{
				camera_rotation_vector.x -= 0.01;
			}
			if (events[UserInputEvents::kZ])
			{
				camera_rotation_vector.z += 0.01;
			}
			if (events[UserInputEvents::kC])
			{
				camera_rotation_vector.z -= 0.01;
			}

			m_audio_manager_->PlayAudio(audio_entity);
			m_renderer_manager_->UpdateWorld(camera_vector, camera_rotation_vector);
			m_renderer_manager_->PaintNextFrame(static_entity);
			last_frame_time = now;
		}

		last_update_time = now;
	} while (app_is_running);
}
