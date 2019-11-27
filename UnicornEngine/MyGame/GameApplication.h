#pragma once

#include <Application.h>
#include <Time.h>
#include <SDL_image.h>

namespace FG
{
	class Window;
	class InputManager;
	class Camera;
	class EntityManager;
	class SpriteManager;
	class CollisionManager;
	class EnemyFactory;
	class FollowingEnemyFactory;
	class SmallEnemyFactory;
	class FactoryManager;
}

class Player; //Forward declaration : there is a class but you don't have to know what it does yet
class Enemy;
class UI;
class Background;
class SDL_Texture;
class MusicManager;

class GameApplication : public FG::Application
{
public:
	virtual bool Initialize() override;
	virtual void Run() override;
	virtual void Shutdown() override;
	void CreateEnemies();
private:
	void InitializeSounds();
	void CreateFactories();
	void CreateBackground();
	void CreatePlayer();
private:
	FG::Window* window = nullptr;
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;
	//FG::EntityManager* entityManager = nullptr;
	FG::SpriteManager* spriteManager = nullptr;
	FG::CollisionManager* collisionManager = nullptr;

	FG::FactoryManager* factoryManager = nullptr;
	FG::EnemyFactory* enemyFactory = nullptr;
	FG::FollowingEnemyFactory* followingEnemyFactory = nullptr;
	FG::SmallEnemyFactory* smallEnemyFactory = nullptr;

	FG::Time time;

	UI* ui = nullptr;
	Background* background = nullptr;
	Background* backgroundBigStars = nullptr;
	Background* backgroundSmallStars = nullptr;
	Player* player = nullptr;
	Enemy* enemy = nullptr;
};

FG::Application* FG::CreateApplication()
{
	return new GameApplication();
}