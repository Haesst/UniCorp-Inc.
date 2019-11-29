#pragma once

#include <Entity.h>

namespace FG
{
	class Vector2D;
	class SpriteManager;
}

class Projectile : public FG::Entity
{
public:
	enum class BulletType
	{
		PlayerBullet,
		PlayerBigBullet,
		EnemyBullet,
	};

protected:
	float speed;
	float lifetime = 3.0f;
	FG::Vector2D direction;
	FG::SpriteManager* spriteManager;
	BulletType bulletType;

public:
	Projectile(FG::Vector2D direction, FG::Vector2D position, FG::SpriteManager* spriteManager, BulletType bulletType, float speed = 350.0f);
	~Projectile();

	// Inherited via Entity
	virtual void Update(float deltaTime) override;
	virtual void Render(FG::Camera* const camera) override;

	virtual void onCollision(Tag tagau) override;

protected:
	Projectile(FG::Vector2D direction, FG::Vector2D position, FG::SpriteManager* spriteManager, float speed = 350.0f);
};

