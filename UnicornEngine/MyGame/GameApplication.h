#pragma once

#include <Application.h>
#include <Time.h>

namespace FG
{
	class Window;
	class InputManager;
	class Camera;
	class EntityManager;
	class SpriteManager;
	class CollisionManager;
}

class Player; //Forward declaration : there is a class but you dont have to know what it does yet
class Enemy;

class GameApplication : public FG::Application
{
public:
	virtual bool Initialize() override;
	virtual void Run() override;
	virtual void Shutdown() override;
	void CreateEnemies();
private:
	FG::Window* window = nullptr;
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;
	FG::EntityManager* entityManager = nullptr;
	FG::SpriteManager* spriteManager = nullptr;
	FG::CollisionManager* collisionManager = nullptr;

	FG::Time time;

	Player* player = nullptr;
	Enemy* enemy = nullptr;

	constexpr static int FPS = 120;
	constexpr static float frameDelay = 1000 / FPS;
};

FG::Application* FG::CreateApplication()
{
	return new GameApplication();
}