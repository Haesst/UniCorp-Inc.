#include "GameApplication.h"

#include <Logger.h>
#include <Window.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SpriteManager.h>

bool GameApplication::Initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		FG::Logger::Log(IMG_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	// Create a window
	window = new FG::Window();
	if (!window->Initialize("My Game", 1024, 768))
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}
	spriteManager = new FG::SpriteManager();
	if (!spriteManager->Initialize(window->GetInternalWindow()))
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	return true;
}

void GameApplication::Run()
{
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) > 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = true;
			default:
				break;
			}
		}
	}
}

void GameApplication::Shutdown()
{
	// Reverse order
	if (window)
	{
		window->Shutdown();
		delete window;
		window = nullptr;
	}
	if (spriteManager)
	{
		spriteManager->Shutdown();
		delete spriteManager;
		spriteManager = nullptr;
	}
	SDL_Quit();

	IMG_Quit();
}
