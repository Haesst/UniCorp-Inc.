#include "SpriteManager.h"

#include <string.h>
#include <iostream>
#include "SpriteManager.h"
#include "Sprite.h"
#include <cassert>
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

FG::Sprite* FG::SpriteManager::CreateSprite(const char* file, int x, int y, int w, int h)
{
	auto it = textures.find(file);
	if (it == textures.end())
	{
		SDL_Surface* surface = IMG_Load(file);
		//SDL_Surface* surface = SDL_LoadBMP(file.c_str());

		assert(surface);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		assert(texture);
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
	SDL_Texture* texture = sprite->GetTexture();
	SDL_SetTextureAlphaMod(texture, 255.0f);
	SDL_RenderCopy(renderer, texture, &sprite->GetSource(), &rect);
}

void FG::SpriteManager::Draw(Sprite* sprite, SDL_Rect rect, SDL_Color colorModifier)
{

	SDL_Texture* texture = sprite->GetTexture();
	SDL_SetTextureColorMod(texture, colorModifier.r, colorModifier.g, colorModifier.b);

	SDL_RenderCopy(renderer, texture, &sprite->GetSource(), &rect);
}

void FG::SpriteManager::Draw(Sprite* sprite, SDL_Rect rect, SDL_Color colorModifier, float alpha)
{

	SDL_Texture* texture = sprite->GetTexture();
	SDL_SetTextureColorMod(texture, colorModifier.r, colorModifier.g, colorModifier.b);
	SDL_SetTextureAlphaMod(texture, alpha);

	SDL_RenderCopy(renderer, texture, &sprite->GetSource(), &rect);
}

void FG::SpriteManager::Draw(Sprite* sprite, SDL_Rect rect, float alpha)
{
	SDL_Texture* texture = sprite->GetTexture();
	SDL_SetTextureAlphaMod(texture, alpha);

	SDL_RenderCopy(renderer, texture, &sprite->GetSource(), &rect);
}

void FG::SpriteManager::DebugDraw(SDL_Rect debugrect)
{
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawRect(renderer, &debugrect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}
