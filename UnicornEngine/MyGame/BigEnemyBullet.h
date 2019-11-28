#pragma once

#include "Projectile.h"

class BigEnemyBullet : public Projectile
{

public:

	BigEnemyBullet(FG::Vector2D direction, FG::Vector2D position, FG::SpriteManager* spriteManager, float speed = 225.0f);
	~BigEnemyBullet();

	void Update(float deltaTime) override;


	void Render(FG::Camera* const camera) override;


	void onCollision(Tag tagau) override;

};

