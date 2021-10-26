#pragma once
#include "AudioEntity.h"
#include <memory>
#include <FMOD\fmod.hpp>
#undef main

class AudioManager
{
	public:
		AudioManager();
		void PlayAudio(AudioEntity& audio_entity);
	private:
		FMOD::System* m_fmod_system_;
};

