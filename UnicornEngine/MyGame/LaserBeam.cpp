#include "LaserBeam.h"

#include <SpriteManager.h>

LaserBeam::LaserBeam(FG::Vector2D direction, FG::Vector2D position, FG::SpriteManager* spriteManager, Entity* owner, float lifetime, float speed /*= 0.0f*/)
	: Projectile(direction, position, spriteManager, speed), owner(owner)
{
	myTagau = EnemyBulletau;
	sprite = spriteManager->CreateSprite("../TestingAssets/LaserBeam.png", 1, 1, 32, 900);
	rect = { (int)position.x, (int)position.y, 64,900 };

	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	this->lifetime = lifetime;
}

LaserBeam::~LaserBeam()
{

}

void LaserBeam::Update(float deltaTime)
{
	currentTime += deltaTime;
	if (currentTime >= lifetime)
	{
		Active = false;
	}

	if (owner->Active == false)
	{
		Active = false;
	}

	FG::Vector2D ownerPosition = owner->GetPosition();

	position = FG::Vector2D(ownerPosition.x - 4, ownerPosition.y + 64.0f);

	rect = { (int)position.x, (int)position.y, 64, 900 };

	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	UpdateCollider();
}

void LaserBeam::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
}

void LaserBeam::onCollision(Tag tagau)
{
	if (tagau == Playerau)
	{
		Active = false;
	}
}
