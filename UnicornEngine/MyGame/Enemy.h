#pragma once

#include <string>
#include <Entity.h>
#include <Vector2D.h>
#include "FSMState.h"

namespace FG //i have identified that these two classes exist in FG/engine.
{
	class SpriteManager;
	class Camera;
}

class EnemyState;

class Enemy : public FG::Entity
{
public:
	Enemy();
	Enemy(FG::SpriteManager* spriteManagerRef, FG::Vector2D position);
	~Enemy();

	virtual void Update(float deltaTime) override; //*?
	virtual void Render(FG::Camera* const camera) override;

	void SetState(FSMState<Enemy>* state);
	virtual void Shoot();
	virtual float GetCurrentShotTime();

	//FG::Vector2D position;

private:
	void MoveEnemy(float deltaTime);
	//FG::Vector2D position;
	EnemyState* enemyState = nullptr;

	// Inherited via Entity
	virtual void onCollision(Tag tagau) override;
protected:
	virtual void EnemyDies();
	void CheckIfVisible();

protected:
	FG::SpriteManager* spriteManager;
	SDL_Window* window = nullptr;

	float timeBetweenShots = 1.6f;
	float currentShotTime = timeBetweenShots;

	int health = 1;
	int score = 10;

};