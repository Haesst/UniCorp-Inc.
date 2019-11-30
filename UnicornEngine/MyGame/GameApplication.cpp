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
	int defeatedBosses = 0;
	std::string enemyTypes[5] = { "DescendingEnemy", "SmallEnemy", "SmallEnemy", "FollowingEnemy", "BigMomma" };
	std::string powerupTypes[6] = { "PowerupMoveSpeed", "PowerupAttackSpeed", "PowerupRingshot", "PowerupSpread", "PowerupMultiSpread", "PowerupLife" };
	bool quit = false;
	while (!quit)
	{
		elapsedTime += time.DeltaTime();
		currentTime -= time.DeltaTime();
		timeForPowerup -= time.DeltaTime();
		// Start the timer
		time.StartFrame();
		// Update input
		inputManager->Update(quit);


		spawnAmount = 10 + (4 * player->defeatedBosses);

		if (currentTime <= 0.0f)
		{
			SpawnWave(enemyTypes, spawnAmount);
			currentTime = timeBetweenSpawn;
		}

		if (timeForPowerup <= 0.0f)
		{
			SpawnPowerup(powerupTypes);
			timeForPowerup = timeBetweenPowerups;
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
			//Clearing the screen
			FG::EntityManager::Instance()->ClearEntities();
			//Displaying the game over window (position at -900y so hidden by default)
			camera->StartRenderFrame();
			SDL_Rect hsrect = UI::Instance()->DrawHighscoreWindow();
			camera->EndRenderFrame();
			//Lowers the window gently into view
			while (hsrect.y < 0)
			{
				hsrect.y += 10;
				camera->StartRenderFrame();
				UI::Instance()->LowerHighscoreWindow(hsrect);
				camera->EndRenderFrame();
			}
			//Fetches the highscores
			Highscore::arrayWrapper wrapper;
			wrapper = highscoreManager->DisplayScores(wrapper);
			//Displays all the scores, one after the other
			int temp = 0;
			int w = 100;
			int h = 50;
			for (auto& text : wrapper.list) {
				if (temp % 2 == 0) //every OTHER, excluding first
				{
					w = 50;
					h += 75;
				}
				else
				{
					w = 350;
				}
				UI::Instance()->DrawHighscores(text.value, w, h);
				temp++;
			}
			camera->EndRenderFrame();
			//Waits for input to see if score was good enough
			//Todo: check if player scored before asking for name.
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
	SoundManager::Instance()->AddSound("../TestingAssets/PlayerDamage.wav", "PlayerDamage", 1.0f);
	SoundManager::Instance()->AddSound("../TestingAssets/EnemyShot.wav", "EnemyShot");
	SoundManager::Instance()->AddSound("../TestingAssets/LaserBeam.wav", "LaserBeam");
	SoundManager::Instance()->AddSound("../TestingAssets/BigEnemyBullet.wav", "BigEnemyBullet");
	SoundManager::Instance()->AddSound("../TestingAssets/EnemyExplosion.wav", "EnemyExplosion");
	SoundManager::Instance()->AddSound("../TestingAssets/Powerup.wav", "Powerup");
	SoundManager::Instance()->AddSound("../TestingAssets/LifePickup.wav", "LifePickup");
	SoundManager::Instance()->AddSound("../TestingAssets/PowerupTriple.wav", "PowerupTriple");

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

	powerupLifeFactory = new FG::PowerupLifeFactory(spriteManager);
	factoryManager->AddFactory("PowerupLife", powerupLifeFactory);

	powerupSpreadFactory = new FG::PowerupSpreadFactory(spriteManager);
	factoryManager->AddFactory("PowerupSpread", powerupSpreadFactory);

	powerupMultiSpreadFactory = new FG::PowerupMultiSpreadFactory(spriteManager);
	factoryManager->AddFactory("PowerupMultiSpread", powerupMultiSpreadFactory);

	powerupRingshotFactory = new FG::PowerupRingshotFactory(spriteManager);
	factoryManager->AddFactory("PowerupRingshot", powerupRingshotFactory);

	powerupMoveSpeedFactory = new FG::PowerupMoveSpeedFactory(spriteManager);
	factoryManager->AddFactory("PowerupMoveSpeed", powerupMoveSpeedFactory);

	powerupAttackSpeedFactory = new FG::PowerupAttackSpeedFactory(spriteManager);
	factoryManager->AddFactory("PowerupAttackSpeed", powerupAttackSpeedFactory);
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
	player->ResetStats();
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
	std::string enemySpawning = enemyTypes[0];

	if (enemySpawning == "BigMomma")
	{
		spawnAmount = player->defeatedBosses + 1;
		FormationBigMomma(enemySpawning, spawnAmount);
	}
	else if (enemySpawning == "DescendingEnemy")
	{
		FormationV(enemySpawning, spawnAmount);
	}
	else if (enemySpawning == "FollowingEnemy")
	{
		FormationLine(enemySpawning, spawnAmount);
	}
	else if (enemySpawning == "SmallEnemy")
	{
		FormationSmallEnemy(enemySpawning, spawnAmount);
	}
	else //Just in case of unexpected enemy: Spawn in a line.
	{
		FormationLine(enemySpawning, spawnAmount);
	}

	//Finally, shuffle around enemy types so the next one in the list spawns.
	int i;
	int n = 5;

	std::string temp = enemyTypes[0];
	for (i = 0; i < n - 1; i++)
	{
		enemyTypes[i] = enemyTypes[i + 1];
	}
	enemyTypes[n - 1] = temp;
}

void GameApplication::SpawnPowerup(std::string powerupTypes[])
{ //todo: make the types switch up, maybe add more effects
	FG::Vector2D position;
	position.x = rand() % 1000 + 5, position.y = -100;

	FG::EntityManager::Instance()->AddEntity(powerupTypes[0], position);
	//Shuffles all powerup types around so the next type spawns.
	int i;
	int n = 6;
	

	std::string temp = powerupTypes[0];
	for (i = 0; i < n - 1; i++)
	{
		powerupTypes[i] = powerupTypes[i + 1];
	}
	powerupTypes[n - 1] = temp;
}

void GameApplication::FormationV(std::string enemyType, int spawnAmount)
{
	FG::Vector2D leftPos = { width/2, 50};
	FG::Vector2D rightPos = { width/2, 50};
	FG::Vector2D diff = {30, 30};
	for (size_t i = 0; i < spawnAmount; i++)
	{
		if (i % 2 != 0) // ODD numbers
		{
			FG::EntityManager::Instance()->AddEntity(enemyType, rightPos);
			rightPos.x += diff.x;
			rightPos.y -= diff.y;
		}
		else //EVEN numbers. First number is even (thus, first spawned enemy enters this)
		{
			FG::EntityManager::Instance()->AddEntity(enemyType, leftPos);
			leftPos.x -= diff.x;
			leftPos.y -= diff.y;
		}
	}
}

void GameApplication::FormationLine(std::string enemyType, int spawnAmount)
{
	FG::Vector2D position = {0, 0};
	FG::Vector2D diff = {20, 20};
	for (size_t i = 0; i < spawnAmount; i++) //Spawns everything in a line
	{
		if (i == 10 || i == 20 ||i == 30)
		{
			position.y -= 30;
		}
		FG::EntityManager::Instance()->AddEntity(enemyType, position);
		position.x += diff.x;
	}
}

void GameApplication::FormationSmallEnemy(std::string enemyType, int spawnAmount)
{
	FG::Vector2D leftPos = {0, 50};
	FG::Vector2D rightPos = {width, 50};
	FG::Vector2D diff = {40, 40};
	for (size_t i = 0; i < spawnAmount; i++)
	{
		if (i % 2 != 0) // ODD numbers
		{
			FG::EntityManager::Instance()->AddEntity(enemyType, rightPos);
			rightPos.x += diff.x;
			rightPos.y -= diff.y;
		}
		else //EVEN numbers. First number is even (thus, first spawned enemy enters this)
		{
			if (i > 0)
			{
				leftPos.x -= diff.x;
				leftPos.y -= diff.y;
			}
			FG::EntityManager::Instance()->AddEntity(enemyType, leftPos);
		}
	}
}

void GameApplication::FormationBigMomma(std::string enemyType, int spawnAmount)
{
	FG::Vector2D defaultPos = { width / 2, -75 };
	FG::Vector2D leftPos = { defaultPos.x / 2, defaultPos.y};
	FG::Vector2D rightPos = {defaultPos.x + leftPos.x, defaultPos.y};
	FG::Vector2D finalPos = { defaultPos.x, defaultPos.y };

	for (size_t i = 0; i < spawnAmount; i++)
	{
		if (i == 0 || i == 6 || i == 11) //central row
		{ FG::EntityManager::Instance()->AddEntity(enemyType, defaultPos); }
		else if (i == 1) //left row. The second big momma does not increase Y-pos.
		{ FG::EntityManager::Instance()->AddEntity(enemyType, leftPos); }
		else if (i == 2 || i == 7 || i == 12) //right-most row
		{ FG::EntityManager::Instance()->AddEntity(enemyType, rightPos); }
		else if (i == 3 || i == 8) //middle left row
		{
			defaultPos.y -= 75, leftPos.y -= 75, rightPos.y -= 75, finalPos.y -= 75;
			finalPos.x = leftPos.x + (leftPos.x / 2);
			FG::EntityManager::Instance()->AddEntity(enemyType, finalPos);
		}
		else if (i == 4 || i == 9) //middle right row
		{
			finalPos.x = defaultPos.x + (leftPos.x / 2);
			FG::EntityManager::Instance()->AddEntity(enemyType, finalPos);
		}
		else if (i == 5 || i == 10) //leftmost row, exclusing the first wave of bigmommas
		{
			defaultPos.y -= 75, leftPos.y -= 75, rightPos.y -= 75, finalPos.y -= 75;
			FG::EntityManager::Instance()->AddEntity(enemyType, leftPos);
		}
		else //Only if the player has 14+ big mommas do you end up here.
		{
			std::cout << "Ended in else for bigmomma, not good!" << std::endl;
			FG::EntityManager::Instance()->AddEntity(enemyType, defaultPos);
		}
	}
	player->DefeatedBoss();
}
