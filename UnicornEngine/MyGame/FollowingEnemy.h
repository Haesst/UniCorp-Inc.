#pragma once

#include "Enemy.h"
#include "FollowingEnemyState.h";
#include <Vector2D.h>


class FollowingEnemy : public Enemy
{
private:
	FollowingEnemyState* enemyState;
	FG::SpriteManager* spriteManager;
	FG::Vector2D lastFramePosition;
	FG::Vector2D currentFrameVector;

private:
	void onCollision(Tag tagau) override;

public:

	FollowingEnemy(FG::SpriteManager* spriteManagerRef, FG::Vector2D position);

	void Update(float deltaTime) override;
	void Render(FG::Camera* const camera) override;
	void LateUpdate(float deltaTime) override;

	float GetCurrentShotTime() override;
	void Shoot() override;

protected:
	void EnemyDies() override;
};