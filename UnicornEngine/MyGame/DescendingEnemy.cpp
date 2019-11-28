#include "DescendingEnemy.h"
#include "DescendingEnemyState.h"
#include "Config.h"
#include "SoundManager.h"
#include "Projectile.h"
#include "Player.h"
#include "UI.h";

#include <SpriteManager.h>
#include <EntityManager.h>
#include <Collider.h>
#include <iostream>
#include <Vector2D.h>

DescendingEnemy::DescendingEnemy() {}

void DescendingEnemy::onCollision(Tag tagau)
{
	switch (tagau)
	{
		//case Tag::Enemyau: std::cout << "Enemy collided with Enemy" << std::endl ; break;
	case Tag::Playerau: std::cout << "Enemy collided with Player" << std::endl; break;
	case Tag::PlayerBulletau: DescendingEnemyDies(); break;
	}
}

void DescendingEnemy::DescendingEnemyDies()
{
	Player* player = dynamic_cast<Player*>(FG::EntityManager::Instance()->GetPlayer());
	player->AddToScore(score);
	UI::Instance()->UpdateScore();
	SoundManager::Instance()->PlaySound("EnemyExplosion");
	Active = false;
}

float DescendingEnemy::GetCurrentShotTime()
{
	return currentShotTime;
}

DescendingEnemy::DescendingEnemy(FG::SpriteManager* spriteManagerRef, FG::Vector2D pos)
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
	descendingEnemyState = new DescendingEnemyState();
	descendingEnemyState->Configure(this);
	descendingEnemyState->ChangeState(new DescendingEnemyState::AttackPlayer());
	//UpdateCollider();

	myTagau = Tag::Enemyau;
}

DescendingEnemy::~DescendingEnemy()
{
	delete descendingEnemyState;
	descendingEnemyState = nullptr;
}

void DescendingEnemy::Update(float deltaTime)
{
	if (currentShotTime > 0)
	{
		currentShotTime -= deltaTime;
	}

	descendingEnemyState->Update();
	rect = { (int)position.x, (int)position.y, 36, 30 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	UpdateCollider();
}

void DescendingEnemy::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}

void DescendingEnemy::SetState(FSMState<DescendingEnemy>* state)
{
	descendingEnemyState->ChangeState(state);
}

void DescendingEnemy::Shoot()
{
	Projectile* bullet = new Projectile(FG::Vector2D(0, 1), FG::Vector2D(position.x + 15.0f, position.y + 40.0f), spriteManager, Projectile::BulletType::EnemyBullet);
	bullet->Active = true;
	FG::EntityManager::Instance()->AddEntity(bullet, "EnemyBullet");
	SoundManager::Instance()->PlaySound("EnemyShot");
	currentShotTime = timeBetweenShots;
}
