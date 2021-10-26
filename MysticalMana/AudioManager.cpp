#include "AudioManager.h"
#include <exception>

AudioManager::AudioManager()
{
	FMOD_RESULT fmod_result = FMOD::System_Create(&m_fmod_system_);
	if (fmod_result != FMOD_OK)
	{
		throw std::exception("Failed to create FMOD system");
	}

	fmod_result = m_fmod_system_->init(512, FMOD_INIT_NORMAL, 0);
	if (fmod_result != FMOD_OK)
	{
		throw std::exception("Failed to initialize FMOD");
	}
}

void AudioManager::PlayAudio(AudioEntity& audio_entity)
{
	if (!audio_entity.m_is_audio_playing)
	{
		m_fmod_system_->createSound(audio_entity.m_file_name.c_str(), FMOD_DEFAULT, nullptr, &audio_entity.m_fmound_sound_handle);
		m_fmod_system_->playSound(audio_entity.m_fmound_sound_handle, nullptr, false, nullptr);
		audio_entity.m_is_audio_playing = true;
	}
}