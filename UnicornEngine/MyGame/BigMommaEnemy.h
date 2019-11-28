#pragma once
#include "Enemy.h"

class BigMommaState;

class BigMommaEnemy : public Enemy
{
private:
	BigMommaState* enemyState = nullptr;

	float laserTime = 1.5f;
	void onCollision(Tag tagau) override;

public:
	BigMommaEnemy(FG::SpriteManager* spriteManagerRef, FG::Vector2D position);

	void Update(float deltaTime) override;
	void Render(FG::Camera* const camera) override;
	void Shoot() override;
	float GetCurrentShotTime() override;

protected:
	void EnemyDies() override;

};