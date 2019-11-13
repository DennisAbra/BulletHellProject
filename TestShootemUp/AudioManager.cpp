#include "AudioManager.h"

AudioManager* AudioManager::instance = nullptr;

AudioManager* AudioManager::Instance()
{
	if (instance == nullptr)
	{
		instance = new AudioManager();
	}
	return instance;
}

void AudioManager::Release()
{
	delete instance;
	instance = nullptr;
}

AudioManager::AudioManager()
{
	if (Mix_Init(MIX_INIT_MP3) < 0)
	{
		printf("Mixer MP3 Init Error: %s\n", Mix_GetError());
	}
	assetManager = AssetManager::Instance();
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("Mixer Init Error: %s\n", Mix_GetError());
	}
}

AudioManager::~AudioManager()
{
	assetManager = nullptr;
	Mix_Quit();
}

void AudioManager::PlayMusic(std::string filename, int loops)
{
	Mix_PlayMusic(assetManager->GetMusic(filename), loops);
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
	}
}

void AudioManager::PlaySFX(std::string filename, int loops, int channel)
{
	Mix_PlayChannel(channel, assetManager->GetSFX(filename), loops);
}