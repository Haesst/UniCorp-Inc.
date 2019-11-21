#include "Enemy.h"
#include "Config.h"
#include "EnemyState.h"
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
		case Tag::Bulletau: Active = false; break;
	}
}

Enemy::Enemy(FG::SpriteManager* spriteManagerRef)
{
	Active = true;
	spriteManager = spriteManagerRef;
	sprite = spriteManager->CreateSprite("../TestingAssets/enemy.png", 1, 1, 36, 30);
	rect = { 0,0,36,30 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	rect = { (int)position.x, (int)position.y, 36, 30 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	enemyState = new EnemyState();
	enemyState->Configure(this);
	enemyState->ChangeState(new EnemyState::Idle());
	//UpdateCollider();

	myTagau = Tag::Enemyau;
}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
	enemyState->Update();
	rect = { (int)position.x, (int)position.y, 36, 30 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	UpdateCollider();
}

void Enemy::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}
