#include "Enemy.h"
#include "Config.h"
#include "EnemyState.h"
#include "SoundManager.h"
#include "Projectile.h"
#include "Player.h"
#include "UI.h";

#include <SpriteManager.h>
#include <EntityManager.h>
#include <Collider.h>
#include <iostream>
#include <Vector2D.h>

Enemy::Enemy() {}

void Enemy::onCollision(Tag tagau)
{
	switch (tagau)
	{
		//case Tag::Enemyau: std::cout << "Enemy collided with Enemy" << std::endl ; break;
		case Tag::Playerau: std::cout << "Enemy collided with Player" << std::endl; break;
		case Tag::PlayerBulletau: EnemyDies(); break;
	}
}

void Enemy::EnemyDies()
{
	Player* player = dynamic_cast<Player*>(FG::EntityManager::Instance()->GetPlayer());
	player->AddToScore(score);
	UI::Instance()->UpdateScore();
	SoundManager::Instance()->PlaySound("EnemyExplosion");
	Active = false;
}

float Enemy::GetCurrentShotTime()
{
	return currentShotTime;
}

Enemy::Enemy(FG::SpriteManager* spriteManagerRef, FG::Vector2D pos)
{
	position.x = pos.x;
	position.y = pos.y;

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
	enemyState->ChangeState(new EnemyState::AttackPlayer());
	//UpdateCollider();

	myTagau = Tag::Enemyau;
}

Enemy::~Enemy()
{
	delete enemyState;
	enemyState = nullptr;
}

void Enemy::Update(float deltaTime)
{
	if (currentShotTime > 0)
	{
		currentShotTime -= deltaTime;
	}

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

void Enemy::SetState(FSMState<Enemy>* state)
{
	enemyState->ChangeState(state);
}

void Enemy::Shoot()
{
	Projectile* bullet = new Projectile(FG::Vector2D(0, 1), FG::Vector2D(position.x + 15.0f, position.y + 40.0f), spriteManager, Projectile::BulletType::EnemyBullet);
	bullet->Active = true;
	FG::EntityManager::Instance()->AddEntity(bullet, "EnemyBullet");
	SoundManager::Instance()->PlaySound("EnemyShot");
	currentShotTime = timeBetweenShots;
}
