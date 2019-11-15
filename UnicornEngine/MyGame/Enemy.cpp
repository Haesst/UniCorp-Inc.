#include "Enemy.h"
#include <SpriteManager.h>
#include <Collider.h>

Enemy::Enemy(){}

void Enemy::onCollision(FG::Collider* theOtherCollider)
{
}

Enemy::Enemy(FG::SpriteManager* spriteManagerRef) : spriteManager(spriteManagerRef)
{
	sprite = spriteManager->CreateSprite("../TestingAssets/FIREBALL.png", 1, 1, 900, 800);
	rect = { 400,50,90,80 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	UpdateCollider();
}

void Enemy::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}
