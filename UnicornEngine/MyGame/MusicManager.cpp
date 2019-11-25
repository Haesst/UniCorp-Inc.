#include "MusicManager.h"
#include <iostream>

MusicManager::MusicManager()
{ 
	//Initialize SDL_mixer
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}


MusicManager* MusicManager::Instance()
{
	static MusicManager* instance = new MusicManager();

	return instance;
}

MusicManager::~MusicManager()
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

void MusicManager::PlayMusic(const char* name)
{
	if (music.find(name) != music.end())
	{
		Mix_PlayMusic(music[name], -1);
	}
}

void MusicManager::AddMusic(const char* path, const char* name)
{
	Mix_Music* musicFile = Mix_LoadMUS(path);

	if (music.find(name) == music.end() && musicFile != nullptr)
	{
		music[name] = musicFile;
	}
}

void MusicManager::PlaySound(const char* name)
{
	if (soundEffects.find(name) != soundEffects.end())
	{
		Mix_PlayChannel(-1, soundEffects[name], 0);
	}
}

void MusicManager::AddSound(const char* path, const char* name)
{
	Mix_Chunk* soundFile = Mix_LoadWAV(path);

	if (soundEffects.find(name) == soundEffects.end() && soundFile != nullptr)
	{
		soundEffects[name] = soundFile;
	}
}
