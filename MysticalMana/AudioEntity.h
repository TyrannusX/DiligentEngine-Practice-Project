#ifndef AUDIOENTITY_H
#define AUDIOENTITY_H

#include "BaseEntity.h"
#include "../External/Include/FMOD/fmod.hpp"

struct AudioEntity : BaseEntity
{
	std::string m_file_name;
	FMOD::Sound* m_fmound_sound_handle;
	bool m_is_audio_playing = false;
};
#endif