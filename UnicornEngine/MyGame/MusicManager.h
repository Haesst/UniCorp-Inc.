#pragma once
#include <map>
#include <SDL_mixer.h>

class MusicManager
{
private:
	std::map<char*, Mix_Chunk*> soundEffects;
	std::map<char*, Mix_Music*> music;

public:
	MusicManager();
	~MusicManager();

	void PlayMusic(const char* name);
	void AddMusic(const char* path, const char* name);
	void PlaySound(const char* name);
	void AddSound(const char* path, const char* name);
};