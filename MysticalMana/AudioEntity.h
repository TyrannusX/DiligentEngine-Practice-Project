#ifndef AUDIOENTITY_H
#define AUDIOENTITY_H

#include "BaseEntity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

struct AudioEntity : BaseEntity
{
	std::string m_file_name;
	Mix_Music* background_music;
	Mix_Chunk* sound_effect;
	bool m_is_audio_playing = false;
};
#endif