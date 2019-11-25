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
	Enemy(FG::SpriteManager* spriteManagerRef);
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
	FG::SpriteManager* spriteManager;
	EnemyState* enemyState = nullptr;

	// Inherited via Entity
	virtual void onCollision(Tag tagau) override;
	void EnemyDies();
protected:
	float timeBetweenShots = 1.6f;
	float currentShotTime = timeBetweenShots;
};