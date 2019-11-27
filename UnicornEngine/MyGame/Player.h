#pragma once

#include <Entity.h>
#include <Vector2D.h>

namespace FG
{
	class InputManager;
	class Camera;
	class SpriteManager;
}

class PlayerState;

class Player : public FG::Entity
{
public:
	Player(FG::InputManager* inputManager, FG::Camera* camera, FG::SpriteManager* spriteManagerRef);

	virtual void Update(float deltaTime) override;
	virtual void Render(FG::Camera* const camera) override;

	int LifesLeft() { return lifes; }
	int LifesLeft(int lifes) { this->lifes = lifes; return lifes; }

	int GetScore() { return score; }
	void AddToScore(int score);

private:
	Player() {}

	void MovePlayer(float deltaTime);
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;
	PlayerState* playerState = nullptr;

	//FG::Vector2D position;
	FG::SpriteManager* spriteManager = nullptr;

	float timeBetweenShots = 0.3f;
	float currentShotTimer = 0.0f;

	int lifes = 3;
	int score = 0;

	// Inherited via Entity
	virtual void onCollision(Tag tagau) override;

};