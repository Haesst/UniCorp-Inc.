#include "GameApplication.h"

#include <Logger.h>
#include <Window.h>
#include <InputManager.h>
#include <Camera.h>
#include <EntityManager.h>
#include <SpriteManager.h>

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

bool GameApplication::Initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) < 0)
	{
		FG::Logger::Log(IMG_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	// Create a window
	window = new FG::Window();
	if (!window->Initialize("UniCorp, Inc.", 1024, 768))
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	camera = new FG::Camera();
	if (!camera->Initialize(window))
	{
		return false;
	}
	spriteManager = new FG::SpriteManager();
	spriteManager->Initialize(window->GetInternalWindow(), camera->GetInternalRenderer());

	inputManager = new FG::InputManager();
	inputManager->Initialize();

	entityManager = new FG::EntityManager();

	player = new Player(inputManager, camera, spriteManager);
	entityManager->AddEntity(player);

	return true;
}

void GameApplication::Run()
{
	bool quit = false;
	while (!quit)
	{
		int startFrame = SDL_GetTicks();
		// Start the timer
		time.StartFrame();
		// Update input
		inputManager->Update(quit);

		//Update entities
		entityManager->Update(time.DeltaTime());
		// Tell camera to start render frame
		camera->StartRenderFrame();
		// Render every entity
		entityManager->Render(camera);
		// Tell camera to end render frame
		camera->EndRenderFrame();
		// End the timer

		int frameTime = SDL_GetTicks() - startFrame;

		if (frameTime < GameApplication::frameDelay)
		{
			SDL_Delay(GameApplication::frameDelay - frameTime);
		}


		time.EndFrame();
	}
}

void GameApplication::Shutdown()
{
	if (player)
	{
		delete player;
		player = nullptr;
	}
	// Reverse order
	if (entityManager)
	{
		delete entityManager;
		entityManager = nullptr;
	}
	
	if (inputManager)
	{
		delete inputManager;
		inputManager = nullptr;
	}

	if (spriteManager)
	{
		spriteManager->Shutdown();
		delete spriteManager;
		spriteManager = nullptr;
	}
	if (camera)
	{
		camera->Shutdown();
		delete camera;
		camera = nullptr;
	}
	if (window)
	{
		window->Shutdown();
		delete window;
		window = nullptr;
	}
	IMG_Quit();
	
	SDL_Quit();
}
