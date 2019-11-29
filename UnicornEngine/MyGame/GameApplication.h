#pragma once

#include <Application.h>
#include <Time.h>
#include <SDL_image.h>
#include <string>

namespace FG
{
	class Window;
	class InputManager;
	class Camera;
	class SpriteManager;
	class CollisionManager;

	class FactoryManager;
	class EnemyFactory;
	class FollowingEnemyFactory;
	class SmallEnemyFactory;
	class DescendingEnemyFactory;
	class SpiralEnemyFactory;
	class BigMommaFactory;

	class PowerupFactory;
	class PowerupLifeFactory;
	class PowerupSpreadFactory;
	class PowerupMultiSpreadFactory;
	class PowerupRingshotFactory;
}

class Player; //Forward declaration : there is a class but you don't have to know what it does yet
class Enemy;
class UI;
class Background;
class SDL_Texture;
class SoundManager;
class Highscore;
class SpiralFormation;

class GameApplication : public FG::Application
{
public:
	virtual bool Initialize() override;
	virtual void Run() override;
	virtual void Shutdown() override;
	void CreateEnemies();

	static const int GetWindowHeight() { return height; }
	static const int GetWindowWidth() { return width; }
private:
	void InitializeSounds();
	void CreateFactories();
	void CreateBackground();
	void CreatePlayer();
	void SpawnWave(std::string enemyTypes[], int spawnAmount);
	void SpawnPowerup(std::string enemyTypes[]);
	void FormationV(std::string enemyType, int spawnAmount);
	void FormationLine(std::string enemyType, int spawnAmount);
	void FormationSmallEnemy(std::string enemyType, int spawnAmount);
	void FormationBigMomma(std::string enemyType, int spawnAmount);

private:
	FG::Window* window = nullptr;
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;
	FG::SpriteManager* spriteManager = nullptr;
	FG::CollisionManager* collisionManager = nullptr;

	FG::FactoryManager* factoryManager = nullptr;
	FG::EnemyFactory* enemyFactory = nullptr;
	FG::FollowingEnemyFactory* followingEnemyFactory = nullptr;
	FG::SmallEnemyFactory* smallEnemyFactory = nullptr;
	FG::DescendingEnemyFactory* descendingEnemyFactory = nullptr;
	FG::SpiralEnemyFactory* spiralEnemyFactory = nullptr;
	FG::BigMommaFactory* bigMommaFactory = nullptr;

	FG::PowerupFactory* powerupFactory = nullptr;
	FG::PowerupLifeFactory* powerupLifeFactory = nullptr;
	FG::PowerupSpreadFactory* powerupSpreadFactory = nullptr;
	FG::PowerupMultiSpreadFactory* powerupMultiSpreadFactory = nullptr;
	FG::PowerupRingshotFactory* powerupRingshotFactory = nullptr;

	FG::Time time;

	UI* ui = nullptr;
	Background* background = nullptr;
	Background* backgroundBigStars = nullptr;
	Background* backgroundSmallStars = nullptr;
	Player* player = nullptr;
	Enemy* enemy = nullptr;
	Highscore* highscoreManager = nullptr;
	SpiralFormation* spiralFormation = nullptr;

	// THEO
	float spawnSpiralRate = 1 / 4.f;
	float spawnSpiralTimer = 0.f;

	static const int height = 900;
	static const int width = 640;
};

FG::Application* FG::CreateApplication()
{
	return new GameApplication();
}