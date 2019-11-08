#include "SpriteManager.h"

#include <string.h>
#include <iostream>
#include "SpriteManager.h"
#include "Sprite.h"

#include <SDL_image.h>

bool FG::SpriteManager::Initialize(SDL_Window* windowRef, SDL_Renderer* rendererRef)
{
	window = windowRef;
	renderer = rendererRef;

	return true;
}

void FG::SpriteManager::Shutdown()
{
	window = nullptr;
	renderer = nullptr;
}

FG::Sprite* FG::SpriteManager::CreateSprite(std::string file, int x, int y, int w, int h)
{
	auto it = textures.find(file);
	if (it == textures.end())
	{
		SDL_Surface* surface = IMG_Load(file.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		textures.insert(std::pair<std::string, SDL_Texture*>(file, texture));
		it = textures.find(file);
	}

	FG::Sprite* sprite = new FG::Sprite(it->second, x, y, w, h);
	sprites.push_back(sprite);
	return sprite;
}

void FG::SpriteManager::Clear()
{
	SDL_RenderClear(renderer);
}

void FG::SpriteManager::Present()
{
	SDL_RenderPresent(renderer);
}

void FG::SpriteManager::Draw(Sprite* sprite, SDL_Rect rect)
{
	SDL_RenderCopy(renderer, sprite->GetTexture(), &sprite->GetSource(), &rect);
}
