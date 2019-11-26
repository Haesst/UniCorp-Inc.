#include "SpiralEnemy.h"
#include <SpriteManager.h>
#include <iostream>
#include "MusicManager.h"


SpiralEnemy::SpiralEnemy()
{
}


SpiralEnemy::SpiralEnemy(FG::SpriteManager* spriteManagerRef, FG::Vector2D* direction) : direction(direction)
{
	position.x = 100.0f;
	position.y = 100.0f;
	Active = false;
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
	//enemyState = new EnemyState();
	//enemyState->Configure(this);
	//enemyState->ChangeState(new EnemyState::AttackPlayer());
	UpdateCollider();
	this->direction = direction;
	//myTagau = Tag::Enemyau;
}

SpiralEnemy::~SpiralEnemy()
{
}

void SpiralEnemy::Update(float deltaTime)
{
	position += *direction * speed;
	
	rect = { (int)position.x, (int)position.y, 36, 30 };
}

void SpiralEnemy::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}

void SpiralEnemy::onCollision(Tag tagau)
{
	switch (tagau)
	{
		//case Tag::Enemyau: std::cout << "Enemy collided with Enemy" << std::endl ; break;
		//case Tag::Playerau: std::cout << "Enemy collided with Player" << std::endl; break;
		case Tag::PlayerBulletau: EnemyDies(); break;
	}
}

void SpiralEnemy::EnemyDies()
{
	MusicManager::Instance()->PlaySound("EnemyExplosion");
	Active = false;
}