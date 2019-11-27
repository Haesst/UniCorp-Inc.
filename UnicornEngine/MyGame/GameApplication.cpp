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
#include "Background.h"
#include "ConcreteFactories.h"
#include "FactoryManager.h"
#include "UI.h"
#include "SoundManager.h"

#include "Entity.h"

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
	if (!window->Initialize("UniCorp, Inc.", width, height))
	{
		FG::Logger::Log(SDL_GetError(), FG::Logger::RemovePathFromFile(__FILE__), __LINE__);
		return false;
	}

	camera = new FG::Camera();
	if (!camera->Initialize(window))
	{
		return false;
	}

	InitializeSounds();

	spriteManager = new FG::SpriteManager();
	spriteManager->Initialize(window->GetInternalWindow(), camera->GetInternalRenderer());

	CreateFactories();

	FG::EntityManager::Instance()->Initialize(collisionManager, factoryManager);

	inputManager = new FG::InputManager();
	inputManager->Initialize();

	collisionManager = new FG::CollisionManager();

	CreateBackground();
	CreatePlayer();

	UI::Instance()->Initialize(spriteManager, camera->GetInternalRenderer(), window->GetInternalWindow());


	return true;
}

void GameApplication::Run()
{
	float timeBetweenSpawn = 3.0f;
	float timeBetweenSpawn2 = 5.0f;
	float timeBetweenSpawn3 = 7.0f;
	float currentTime = 3.0f;
	float currentTime2 = 5.0f;
	float currentTime3 = 7.0f;

	std::string enemyTypes[3] = { "Enemy", "SmallEnemy", "FollowingEnemy" };

	bool quit = false;
	while (!quit)
	{
		currentTime -= time.DeltaTime();
		currentTime2 -= time.DeltaTime();
		currentTime3 -= time.DeltaTime();
		// Start the timer
		time.StartFrame();
		// Update input
		inputManager->Update(quit);


		if (currentTime <= 0.0f)
		{
			int i;
			int n = 3;
			std::string temp = enemyTypes[0];
			for (i = 0; i < n - 1; i++)
			{
				enemyTypes[i] = enemyTypes[i + 1];
			}
			enemyTypes[n - 1] = temp;
			FG::EntityManager::Instance()->AddEntity(enemyTypes[0]);
			currentTime = timeBetweenSpawn;
			std::cout << "spawning from list:" + enemyTypes[0] << std::endl;
		}


		if (currentTime <= 0.0f)
		{
			FG::EntityManager::Instance()->AddEntity("Enemy");
			currentTime = timeBetweenSpawn;
		}

		if (currentTime2 <= 0.0f)
		{
			FG::EntityManager::Instance()->AddEntity("FollowingEnemy");
			currentTime2 = timeBetweenSpawn2;
		}

		if (currentTime3 <= 0.0f)
		{
			std::cout << "Small enemy incoming" << std::endl;
			FG::EntityManager::Instance()->AddEntity("SmallEnemy");
			currentTime3 = timeBetweenSpawn3;
		}

		FG::EntityManager::Instance()->CheckEntitiesCollision();
		//Update entities
		FG::EntityManager::Instance()->Update(time.DeltaTime());
		// Tell camera to start render frame
		camera->StartRenderFrame();
		// Render every entity
		FG::EntityManager::Instance()->Render(camera);
		UI::Instance()->Render(camera);
		// Tell camera to end render frame
		camera->EndRenderFrame();
		// End the timer
		time.EndFrame();

		if (player->LifesLeft() <= 0)
		{
			//Todo: Add Game over screen w. scores here
			std::string x;
			std::cout << "You have been killed! Game over. Press any key to continue." << std::endl;
			std::cin >> x;

			if (!x.empty())
			{
				FG::EntityManager::Instance()->ClearEntities();
				CreateBackground();
				CreatePlayer();
				UI::Instance()->ResetUI();
				UI::Instance()->UpdateScore();

				Run();
			}
			//quit = true;
		}

	}
}

void GameApplication::Shutdown()
{
	if (player)
	{
		delete player;
		player = nullptr;
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
		FG::EntityManager::Instance()->AddEntity("Enemy");
	}
}

void GameApplication::InitializeSounds()
{
	SoundManager::Instance()->AddSound("../TestingAssets/PlayerShot.wav", "PlayerShot");
	SoundManager::Instance()->AddSound("../TestingAssets/EnemyShot.wav", "EnemyShot");
	SoundManager::Instance()->AddSound("../TestingAssets/EnemyExplosion.wav", "EnemyExplosion");

	SoundManager::Instance()->AddMusic("../TestingAssets/newbattle.wav", "GameMusic");
	SoundManager::Instance()->PlayMusic("GameMusic");
}

void GameApplication::CreateFactories()
{
	factoryManager = new FG::FactoryManager();
	enemyFactory = new FG::EnemyFactory(spriteManager);
	factoryManager->AddFactory("Enemy", enemyFactory);

	followingEnemyFactory = new FG::FollowingEnemyFactory(spriteManager);
	factoryManager->AddFactory("FollowingEnemy", followingEnemyFactory);

	smallEnemyFactory = new FG::SmallEnemyFactory(spriteManager);
	factoryManager->AddFactory("SmallEnemy", smallEnemyFactory);
}

void GameApplication::CreateBackground()
{
	background = new Background("../TestingAssets/GalaxyUno.png", spriteManager, 5);
	backgroundBigStars = new Background("../TestingAssets/ParallaxBigStars.png", spriteManager, 4);
	backgroundSmallStars = new Background("../TestingAssets/ParallaxSmallStars.png", spriteManager, 3);
	FG::EntityManager::Instance()->AddEntity(background, "Background");
	FG::EntityManager::Instance()->AddEntity(backgroundBigStars, "Background");
	FG::EntityManager::Instance()->AddEntity(backgroundSmallStars, "Background");
}

void GameApplication::CreatePlayer()
{
	if (player)
	{
		delete player;
	}
	player = new Player(inputManager, camera, spriteManager);
	player->ResetScore();
	player->SetPosition(FG::Vector2D(280, 800));
	player->Active = true;
	FG::EntityManager::Instance()->AddEntity(player, "Player");
	player->LifesLeft(3);
}