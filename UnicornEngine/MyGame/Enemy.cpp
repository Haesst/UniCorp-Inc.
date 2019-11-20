#include "Enemy.h"
#include "Config.h"
#include <SpriteManager.h>
#include <Collider.h>
#include <iostream>

Enemy::Enemy() {}

void Enemy::onCollision(Tag tagau)
{
	switch (tagau)
	{
		case Tag::Enemyau: std::cout << "Enemy collided with Enemy" << std::endl ; break;
		case Tag::Playerau: std::cout << "Enemy collided with Player" << std::endl; break;
	}
}

Enemy::Enemy(FG::SpriteManager* spriteManagerRef)
{
	spriteManager = spriteManagerRef;
	sprite = spriteManager->CreateSprite("../TestingAssets/FIREBALL.png", 1, 1, 900, 800);
	rect = { 400,50,90,80 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	rect = { (int)position.x, (int)position.y, 92, 98 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	//UpdateCollider();

	myTagau = Tag::Enemyau;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	rect = { (int)position.x, (int)position.y, 92, 98 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	UpdateCollider();
}

void Enemy::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}
