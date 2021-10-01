#pragma once
#include "BaseEntity.h"
#include <FMOD/fmod.hpp>

struct AudioEntity : BaseEntity
{
	std::string file_name;
	FMOD::Sound* fmound_sound_handle;
	bool is_audio_playing = false;
};

