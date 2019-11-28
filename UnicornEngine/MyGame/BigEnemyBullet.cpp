#include "BigEnemyBullet.h"
#include "SpriteManager.h"

BigEnemyBullet::BigEnemyBullet(FG::Vector2D direction, FG::Vector2D position, FG::SpriteManager* spriteManager, float speed /* = 225.0f */)
	: Projectile(direction, position, spriteManager, speed)
{
	myTagau = EnemyBulletau;
	sprite = spriteManager->CreateSprite("../TestingAssets/BigShot.png", 1, 1, 17, 20);
	rect = { (int)position.x, (int)position.y, 34,40 };

	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	UpdateCollider();
}

BigEnemyBullet::~BigEnemyBullet()
{
}

void BigEnemyBullet::Update(float deltaTime)
{
	// Todo: Change lifetime to instead destroy them when they hit the top
	lifetime -= deltaTime;
	if (lifetime <= 0.0f)
	{
		Active = false;
	}

	position += direction * speed * deltaTime;

	rect = { (int)position.x, (int)position.y, 34, 40 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	UpdateCollider();
}

void BigEnemyBullet::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
}

void BigEnemyBullet::onCollision(Tag tagau)
{
	switch (tagau)
	{
	case Playerau:
		Active = false;
		break;
	}
}
