#include "SpriteManager.h"

#include <string.h>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include "Window.h"

bool FG::SpriteManager::Initialize(SDL_Window* windowRef)
{
	window = windowRef;
	return true;
}

void FG::SpriteManager::Draw(Sprite* sprite)
{

}

void FG::SpriteManager::Shutdown()
{
}
