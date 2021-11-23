#include "Application.h"
#include "AudioEntity.h"
#include "StaticEntity.h"
#include <iostream>
#include <algorithm>

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
	static_entity.mesh_file_name = "/media/rr-linux/Blade 15 SSD/GameAssets/Mandalorian.obj";

	//Define entity vertex data
	static_entity.m_vertices = m_asset_manager_->GetMeshVertices(static_entity.mesh_file_name);

	//Set buffers on entity
	static_entity.m_vertex_buffer = m_renderer_manager_->CreateVertexBuffer(static_entity);
	/*static_entity.m_index_buffer = m_renderer_manager_->CreateIndexBuffer(static_entity);*/
	std::cout << "END OF VERTEX BUFFER" << std::endl;
	//Set texture on entity
	/*static_entity.m_texture_file_path = "C:\\GameAssets\\MandalorianTextures\\dirt 2.png";*/
	static_entity.m_texture = m_renderer_manager_->CreateTextureFromFile("/media/rr-linux/Blade 15 SSD/GameAssets/MandalorianTextures/dirt 2.png");
	std::cout << "END OF TEXTURE" << std::endl;

	bool app_is_running = true;
	Diligent::Vector3<float> camera_vector(0.0f, 0.0f, 5.0f);
	Diligent::Vector3<float> camera_rotation_vector(0.0f, 0.0f, 0.0f);

	do
	{
		app_is_running = !m_window_->Poll();
		std::unordered_map<UserInputEvents, bool> events = m_window_->UserInputCheck();

		if (events[UserInputEvents::kLeft])
		{
			camera_vector.x += 1;
		}
		if (events[UserInputEvents::kRight])
		{
			camera_vector.x -= 1;
		}
		if (events[UserInputEvents::kUp])
		{
			camera_vector.z -= 1;
		}
		if (events[UserInputEvents::kDown])
		{
			camera_vector.z += 1;
		}
		if (events[UserInputEvents::kS])
		{
			camera_vector.y += 1;
		}
		if (events[UserInputEvents::kW])
		{
			camera_vector.y -= 1;
		}
		if (events[UserInputEvents::kQ])
		{
			camera_rotation_vector.y += 0.01;
		}
		if (events[UserInputEvents::kE])
		{
			camera_rotation_vector.y -= 0.01;
		}
		
		std::cout << "Playing music" << std::endl;
		m_audio_manager_->PlayAudio(audio_entity);
		std::cout << "Done Playing music" << std::endl;
		m_renderer_manager_->UpdateWorld(camera_vector, camera_rotation_vector);
		m_renderer_manager_->PaintNextFrame(static_entity);
	} 
	while (app_is_running);
}
