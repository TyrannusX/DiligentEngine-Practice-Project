#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "AudioEntity.h"
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#undef main

class AudioManager
{
	public:
		AudioManager();
		void PlayAudio(AudioEntity& audio_entity);
		Mix_Music* LoadMusic(std::string music_file_path);
		Mix_Chunk* LoadSoundEffect(std::string effect_file_path);
	private:
		int frequency_;
		int number_of_hardware_channels_;
		int sample_size_;
};
#endif