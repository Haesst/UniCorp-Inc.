#pragma once
#include <unordered_map>
#include <SDL_mixer.h>

typedef std::unordered_map<const char*, Mix_Music*> MusicMap_t;
typedef std::unordered_map<const char*, Mix_Chunk*> SoundMap_t;

class MusicManager
{
private:
	SoundMap_t soundEffects;
	MusicMap_t music;

public:
	static MusicManager* Instance();
	~MusicManager();

	void PlayMusic(const char* name);
	void AddMusic(const char* path, const char* name);
	void PlaySound(const char* name);
	void AddSound(const char* path, const char* name);
private:
	MusicManager();
};