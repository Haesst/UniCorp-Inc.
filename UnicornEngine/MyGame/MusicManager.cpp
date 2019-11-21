#include "MusicManager.h"
#include <iostream>

MusicManager::MusicManager()
{ 
	//Initialize SDL_mixer
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
}

MusicManager::~MusicManager()
{
	Mix_CloseAudio();
}

void MusicManager::PlayMusic(const char* name)
{
	Mix_Music* musicFile = nullptr;
	for (auto& musicPair : music)
	{
		if (musicPair.first == name)
		{
			musicFile = musicPair.second;
			break;
		}
	}

	if (musicFile != nullptr)
	{
		Mix_PlayMusic(musicFile, -1);
	}
}

void MusicManager::AddMusic(const char* path, const char* name)
{
	Mix_Music* musicFile = Mix_LoadMUS(path);

	if (musicFile != nullptr)
	{
		//music.insert(std::make_pair(name, musicFile));
		Mix_PlayMusic(musicFile, -1);
	}
	else
	{
		std::cout << "Music was nullptr" << std::endl;
	}
}

void MusicManager::PlaySound(const char* name)
{

}

void MusicManager::AddSound(const char* path, const char* name)
{

}
