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
#include <Vector2D.h>

#include "Player.h"
#include "Background.h"
#include "ConcreteFactories.h"
#include "FactoryManager.h"
#include "UI.h"
#include "SoundManager.h"
#include "Highscore.h"
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

	highscoreManager = new Highscore();

	CreateBackground();
	CreatePlayer();

	UI::Instance()->Initialize(spriteManager, camera->GetInternalRenderer(), window->GetInternalWindow());

	FG::EntityManager::Instance()->AddEntity("BigMomma", FG::Vector2D(50, 50));

	return true;
}

void GameApplication::Run()
{
	float elapsedTime = 0.0;

	float currentTime = 3.0f;
	float timeBetweenSpawn = 3.0f;
	int spawnAmount = 2;

	std::string enemyTypes[3] = { "Enemy", "SmallEnemy", "FollowingEnemy" };

	bool quit = false;
	while (!quit)
	{
		elapsedTime += time.DeltaTime();
		currentTime -= time.DeltaTime();
		// Start the timer
		time.StartFrame();
		// Update input
		inputManager->Update(quit);

		if (elapsedTime >= 10.0f)
		{
			//std::cout << "More than 10 sec has passed! Increasing spawn amount!" << std::endl;
			//std::cout << "Elapsed time is: "; std::cout << elapsedTime << std::endl;
			spawnAmount = 5;
		}
		if (currentTime <= 0.0f)
		{
			SpawnWave(enemyTypes, timeBetweenSpawn, spawnAmount);
			currentTime = timeBetweenSpawn;
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
			std::cout << "You have been killed! Game over." << std::endl;
			std::cout << "Enter your name to see if you got a highscore!" << std::endl;
			std::cin >> x;

			highscoreManager->AddToFile(player, x);

			if (!x.empty())
			{
				player->LifesLeft(3);
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
		//FG::EntityManager::Instance()->AddEntity("Enemy",);
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

	bigMommaFactory = new FG::BigMommaFactory(spriteManager);
	factoryManager->AddFactory("BigMomma", bigMommaFactory);
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

void GameApplication::SpawnWave(std::string enemyTypes[], float spawnFrequency, int spawnAmount)
{
	int i;
	int n = 3;
	std::string temp = enemyTypes[0];
	for (i = 0; i < n - 1; i++)
	{
		enemyTypes[i] = enemyTypes[i + 1];
	}
	enemyTypes[n - 1] = temp;
	FG::Vector2D position = {};
	position.x = 500.0f;
	position.y = 250.0f;
	FG::EntityManager::Instance()->AddEntity(enemyTypes[0], position);
	std::cout << "spawning from list:" + enemyTypes[0] << std::endl;

}