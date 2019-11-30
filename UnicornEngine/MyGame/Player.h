#pragma once

#include <Entity.h>
#include <Vector2D.h>
#include <string>

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

	bool activePowerup = false;
	bool immortal = false;
	float immortalCounter = 0;
	float immortalTime = 1.6f;
	float immortalFlashCounter = 0.0f;
	float timeBetweenFlash = 0.2f;
	bool flashAlpha = false;

	std::string currentPowerup = "";
	float powerupDuration = 0.0f;

	int GetScore() { return score; }
	void AddToScore(int score);
	void DefeatedBoss();
	void ResetStats() { score = 0; defeatedBosses = 0; }
	int defeatedBosses = 0;

private:
	Player() {}

	void MovePlayer(float deltaTime);
	FG::InputManager* inputManager = nullptr;
	FG::Camera* camera = nullptr;
	PlayerState* playerState = nullptr;

	//FG::Vector2D position;
	FG::SpriteManager* spriteManager;

	float timeBetweenShots = 0.3f;
	float currentShotTimer = 0.0f;

	int lifes = 3;
	int score = 0;

	// Inherited via Entity
	virtual void onCollision(Tag tagau) override;

};