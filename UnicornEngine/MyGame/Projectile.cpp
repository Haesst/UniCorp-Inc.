#include "Projectile.h"

#include <Vector2D.h>
#include <Camera.h>
#include <SpriteManager.h>

#include <iostream>

Projectile::Projectile(FG::Vector2D direction, FG::Vector2D position, FG::SpriteManager* spriteManager, BulletType bulletType, float speed /* = 350.0f */)
	: direction(direction), spriteManager(spriteManager), speed(speed)
{
	if (bulletType == BulletType::PlayerBullet)
	{
		sprite = spriteManager->CreateSprite("../TestingAssets/bullet.png", 1, 1, 6, 36);
	}
	else
	{
		sprite = spriteManager->CreateSprite("../TestingAssets/EnemyBullet.png", 1, 1, 6, 36);
	}

	this->position = position;

	rect = { (int)position.x,(int)position.y, 6, 36 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	UpdateCollider();
	
	myTagau = Bulletau;
}

Projectile::~Projectile()
{
}

void Projectile::Update(float deltaTime)
{
	// Todo: Change lifetime to instead destroy them when they hit the top
	lifetime -= deltaTime;
	if (lifetime <= 0.0f)
	{
		Active = false;
	}

	position += direction * speed * deltaTime;

	rect = { (int)position.x, (int)position.y, 3, 36 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	UpdateCollider();
}

void Projectile::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	//spriteManager->DebugDraw(myCollider->square);
}

void Projectile::onCollision(Tag tagau)
{
	switch (tagau)
	{
	case Playerau:
		Active = false;
		break;
	case Enemyau:
		Active = false;
		break;
	case Bulletau:
		break;
	default:
		break;
	}
}