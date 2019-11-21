#include "Projectile.h"

#include <Vector2D.h>
#include <Camera.h>
#include <SpriteManager.h>

Projectile::Projectile(FG::Vector2D direction, FG::SpriteManager* spriteManager, float speed /* = 350.0f */)
	: direction(direction), spriteManager(spriteManager), speed(speed)
{
	sprite = spriteManager->CreateSprite("../TestingAssets/bullet.png", 1, 1, 6, 36);
	rect = { 0,0, 6, 36 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
}

Projectile::~Projectile()
{}

void Projectile::Update(float deltaTime)
{
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
}
