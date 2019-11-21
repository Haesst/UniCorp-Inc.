#include "GameApplication.h"
#include <iostream>

#include <Logger.h>
#include <Window.h>
#include <InputManager.h>
#include <Camera.h>
#include <EntityManager.h>
#include <SpriteManager.h>
#include <CollisionManager.h>
#include <SDL.h>
#include <SDL_image.h>

#include "Player.h"
#include "Enemy.h"
#include "ConcreteFactories.h"
#include "FactoryManager.h"
#include "UI.h"

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

	factoryManager = new FG::FactoryManager();
	enemyFactory = new FG::EnemyFactory(spriteManager);
	factoryManager->AddFactory("Enemy", enemyFactory);

	inputManager = new FG::InputManager();
	inputManager->Initialize();

	collisionManager = new FG::CollisionManager();

	entityManager = new FG::EntityManager(collisionManager, factoryManager);

	ui = new UI("UI", spriteManager);
	entityManager->AddEntity(ui, "UI");

	int temp[] = { 1,2,3,4 };
	//enemy = new Enemy(temp, "test", spriteManager);
	player = new Player(inputManager, camera, spriteManager, entityManager);
	player->Active = true;
	entityManager->AddEntity(player, "Player");
	//entityManager->AddEntity(enemy, "Enemy");
	
	entityManager->AddEntity("Enemy");

	entityManager->AddEntity("Enemy");

	entityManager->AddEntity("Enemy");

	//CreateEnemies();


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

		entityManager->CheckEntitiesCollision();
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
	
	if (inputManager)
	{
		delete inputManager;
		inputManager = nullptr;
	}

	if (collisionManager)
	{
		delete collisionManager;
		collisionManager = nullptr;
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

void GameApplication::CreateEnemies()
{
	for (int i = 0; i < 5; i++)
	{
		int temp[] = { 1,2,3,4 };
		entityManager->AddEntity("Enemy");
	}
}
