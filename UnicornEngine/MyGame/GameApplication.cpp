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

	//FG::EntityManager::Instance()->AddEntity("BigMomma", FG::Vector2D(50, 50));

	return true;
}

void GameApplication::Run()
{
	float elapsedTime = 0.0;

	float currentTime = 3.0f;
	float timeForPowerup = 3.0f;
	float timeBetweenPowerups = 5.0f;
	float timeBetweenSpawn = 8.0f;
	int spawnAmount = 10;

	std::string enemyTypes[4] = { "FollowingEnemy", "Enemy", "SmallEnemy",  "BigMomma" };

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
			SpawnWave(enemyTypes, spawnAmount);
			currentTime = timeBetweenSpawn;
		}
		if (timeForPowerup <= 0.0f)
		{
			//TODO: continue here after pushing
			//Spawn powerup
		}

		//Update entities
		FG::EntityManager::Instance()->Update(time.DeltaTime());
		FG::EntityManager::Instance()->CheckEntitiesCollision();
		// Tell camera to start render frame
		camera->StartRenderFrame();
		// Render every entity
		FG::EntityManager::Instance()->Render(camera);
		UI::Instance()->Render(camera);
		// Tell camera to end render frame
		camera->EndRenderFrame();
		FG::EntityManager::Instance()->LateUpdate(time.DeltaTime());
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

	descendingEnemyFactory = new FG::DescendingEnemyFactory(spriteManager);
	factoryManager->AddFactory("DescendingEnemy", descendingEnemyFactory);

	//TODO: Fix spawning of spiral enemies, as they take a pointer to a direction
	/*spiralEnemyFactory = new FG::SpiralEnemyFactory(spriteManager);
	factoryManager->AddFactory("SpiralEnemyFactory", spiralEnemyFactory);*/

	powerupFactory = new FG::PowerupFactory(spriteManager);
	factoryManager->AddFactory("Powerup", powerupFactory);
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

void GameApplication::SpawnWave(std::string enemyTypes[], int spawnAmount)
{
	/*There is presumably a better way to handle these positions, with less duplication.
	However, in my attempts to refactor them, the original position and diff values (origpos & origdiff)
	are modified by any future changes to the position or diff variables. Unclear why.*/
	FG::Vector2D position;
	position.x = 20.0f;
	position.y = 20.0f;
	FG::Vector2D origpos = position;
	FG::Vector2D diff = position;
	FG::Vector2D origdiff = diff;
	origpos.x = position.x;
	origpos.y = position.y;
	diff.x = 40.0f;
	origdiff.x = diff.x;
	if (enemyTypes[0] == "BigMomma")
	{
		spawnAmount = 1;
	}

	if (enemyTypes[0] == "FollowingEnemy" || enemyTypes[0] == "SmallEnemy")
	{
		for (size_t i = 0; i < spawnAmount; i++) //Spawns everything in a line
		{
			position.x += diff.x + 15;
			FG::EntityManager::Instance()->AddEntity(enemyTypes[0], position);
		}
	}
	else
	{
		for (size_t i = 0; i < spawnAmount; i++)
		{
			if (i % 2 != 0) // ODD numbers
			{
				position.x = origpos.x + diff.x;
				diff.x += origdiff.x;
			}
			else //EVEN numbers. First number is even (thus, first spawned enemy enters this)
			{
				if (i > 0)
				{
					position.x = origpos.x - diff.x;
					position.y += 35.0f; // Flip this to make them spawn in V-pattern
				}
				else //First enemy spawn pos is unchanged
				{
					position.x -= diff.x;
				}
			}
			FG::EntityManager::Instance()->AddEntity(enemyTypes[0], position);
		}
	}
	int i;
	int n = 4;

	std::string temp = enemyTypes[0]; //Shuffles all enemy types around so the next enemy type spawns.
	for (i = 0; i < n - 1; i++)
	{
		enemyTypes[i] = enemyTypes[i + 1];
	}
	enemyTypes[n - 1] = temp;
}