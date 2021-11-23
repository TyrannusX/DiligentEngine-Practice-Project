#include "AudioManager.h"
#include <exception>
#include <iostream>

AudioManager::AudioManager()
{
	frequency_ = 44100;
	number_of_hardware_channels_ = 2;
	sample_size_ = 2048;

	if(SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		throw std::exception();
	}

	if(Mix_OpenAudio(frequency_, MIX_DEFAULT_FORMAT, number_of_hardware_channels_, sample_size_) < 0)
	{
		printf("SDL Mixer could not initialize! SDL Mixer Error: %s\n", Mix_GetError());
		throw std::exception();
	}
}

Mix_Music* AudioManager::LoadMusic(std::string music_file_path)
{
	std::cout << "Loading music" << std::endl;
	Mix_Music* music = Mix_LoadMUS(music_file_path.c_str());
	if(music == NULL)
	{
		printf( "Failed to load music file! SDL_mixer Error: %s\n", Mix_GetError() );
		throw std::exception();
	}
	return music;
}

Mix_Chunk* AudioManager::LoadSoundEffect(std::string effect_file_path)
{
	Mix_Chunk* chunk = Mix_LoadWAV(effect_file_path.c_str());
	if(chunk == NULL)
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        throw std::exception();
	}
	return chunk;
}

void AudioManager::PlayAudio(AudioEntity& audio_entity)
{
	//Play the music forever
	if(!audio_entity.m_is_audio_playing)
	{
		std::cout << audio_entity.background_music << std::endl;
		Mix_PlayMusic(audio_entity.background_music, 1);
		audio_entity.m_is_audio_playing = true;
	}
}