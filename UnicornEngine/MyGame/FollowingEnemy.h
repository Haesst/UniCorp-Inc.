#pragma once

#include "Enemy.h"
#include "FollowingEnemyState.h";
#include <Vector2D.h>


class FollowingEnemy : public Enemy
{
private:
	FollowingEnemyState* enemyState;
	FG::SpriteManager* spriteManager;

private:
	void onCollision(Tag tagau) override;

public:

	FollowingEnemy(FG::SpriteManager* spriteManagerRef, FG::Vector2D position);

	void Update(float deltaTime) override;
	void Render(FG::Camera* const camera) override;

	float GetCurrentShotTime() override;
	void Shoot() override;

};