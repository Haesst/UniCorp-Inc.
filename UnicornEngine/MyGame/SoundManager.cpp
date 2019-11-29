#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{ 
	//Initialize SDL_mixer
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}


SoundManager* SoundManager::Instance()
{
	static SoundManager* instance = new SoundManager();

	return instance;
}

SoundManager::~SoundManager()
{
	for (auto song : music)
	{
		Mix_FreeMusic(song.second);
	}

	for (auto soundEffect : soundEffects)
	{
		Mix_FreeChunk(soundEffect.second);
	}

	Mix_CloseAudio();
}

void SoundManager::PlayMusic(const char* name)
{
	if (music.find(name) != music.end())
	{
		Mix_PlayMusic(music[name], -1);
	}
}

void SoundManager::AddMusic(const char* path, const char* name)
{
	Mix_Music* musicFile = Mix_LoadMUS(path);

	if (music.find(name) == music.end() && musicFile != nullptr)
	{
		music[name] = musicFile;
	}
}

void SoundManager::PlaySound(const char* name)
{
	if (soundEffects.find(name) != soundEffects.end())
	{
		Mix_PlayChannel(-1, soundEffects[name], 0);
	}
}

void SoundManager::AddSound(const char* path, const char* name, float volumeModifier/* = 0.5 */)
{
	Mix_Chunk* soundFile = Mix_LoadWAV(path);

	if (soundEffects.find(name) == soundEffects.end() && soundFile != nullptr)
	{
		Mix_VolumeChunk(soundFile, MIX_MAX_VOLUME * volumeModifier);
		soundEffects[name] = soundFile;
	}
}
