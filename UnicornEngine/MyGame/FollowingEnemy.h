#pragma once

#include "Enemy.h"
#include "FollowingEnemyState.h";


class FollowingEnemy : public Enemy
{
private:
	FollowingEnemyState* enemyState;
	FG::SpriteManager* spriteManager;

private:
	void onCollision(Tag tagau) override;

public:

	FollowingEnemy(FG::SpriteManager* spriteManagerRef);

	void Update(float deltaTime) override;
	void Render(FG::Camera* const camera) override;

	float GetCurrentShotTime() override;
	void Shoot() override;

};