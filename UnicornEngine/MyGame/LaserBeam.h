#pragma once

#include "Projectile.h"

class LaserBeam : public Projectile
{
private:
	Entity* owner;
	
	float lifeTime;
	float currentTime = 0.0f;

public:

	LaserBeam(FG::Vector2D direction, FG::Vector2D position, FG::SpriteManager* spriteManager, Entity* owner, float lifetime, float speed = 0.0f);
	~LaserBeam();

	void Update(float deltaTime) override;


	void Render(FG::Camera* const camera) override;


	void onCollision(Tag tagau) override;

};

