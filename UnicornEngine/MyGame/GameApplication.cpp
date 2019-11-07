#include "GameApplication.h"

#include <Logger.h>
#include <Window.h>
#include <InputManager.h>
#include <Camera.h>
#include <EntityManager.h>

#include <SDL.h>

bool GameApplication::Initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
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

	inputManager = new FG::InputManager();
	inputManager->Initialize();

	entityManager = new FG::EntityManager();

	player = new Player(inputManager, camera);
	entityManager->AddEntity(player);

	return true;
}

void GameApplication::Run()
{
	bool quit = false;
	while (!quit)
	{
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

	if (camera)
	{
		camera->Shutdown();
		delete camera;
		camera = nullptr;
	}

	if (inputManager)
	{
		delete inputManager;
		inputManager = nullptr;
	}

	if (window)
	{
		window->Shutdown();
		delete window;
		window = nullptr;
	}

	SDL_Quit();
}
