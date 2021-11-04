#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "AudioEntity.h"
#include <memory>
#include "../External/Include/FMOD/fmod.hpp"
#undef main

class AudioManager
{
	public:
		AudioManager();
		void PlayAudio(AudioEntity& audio_entity);
	private:
		FMOD::System* m_fmod_system_;
};
#endif