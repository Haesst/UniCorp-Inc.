#pragma once

#include "Enemy.h"
#include "SmallEnemyState.h"

class SmallEnemy : public Enemy
{
private:
	SmallEnemyState* enemyState;
	FG::SpriteManager* spriteManager;

	int health = 1;
	int shotsToFire = 3;

	float rechargeShots = 1.6f;
	float timeBetweenShots = 0.1f;
	float currentShotTime = 0.0f;

	bool fired = false;
	bool goingRight = false;

private:
	void onCollision(Tag tagau) override;

public:

	SmallEnemy(FG::SpriteManager* spriteManagerRef, bool startingLeft = true);

	void Update(float deltaTime) override;
	void Render(FG::Camera* const camera) override;

	float GetCurrentShotTime() override;
	void Shoot() override;

	bool HaveFired();
	bool GoingRight();

	void ChangeState(FSMState<SmallEnemy>* state);
	int ShotsToFire();
};