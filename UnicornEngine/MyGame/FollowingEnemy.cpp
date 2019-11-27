#include "FollowingEnemy.h"
#include "SoundManager.h"
#include "Projectile.h"
#include "Player.h"
#include "UI.h"

#include <SpriteManager.h>
#include <EntityManager.h>

#include <iostream>

void FollowingEnemy::onCollision(Tag tagau)
{
	if (tagau == Tag::PlayerBulletau)
	{
		health--;

		if (health <= 0)
		{
			EnemyDies();
		}
	}
}

FollowingEnemy::FollowingEnemy(FG::SpriteManager* spriteManagerRef)
{
	health = 2;
	score = 20;
	Active = true;
	timeBetweenShots = 1.1f;
	position.x = 10.0f;
	position.y = 50.0f;
	spriteManager = spriteManagerRef;

	sprite = spriteManager->CreateSprite("../TestingAssets/FollowingEnemy.png", 1, 1, 37, 33);

	rect = { 0,0,37,33 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	rect = { (int)position.x, (int)position.y, 37, 33 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	enemyState = new FollowingEnemyState();
	enemyState->Configure(this);
	enemyState->ChangeState(new FollowingEnemyState::AttackPlayer());
	myTagau = Tag::Enemyau;
}

void FollowingEnemy::Update(float deltaTime)
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

void FollowingEnemy::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}

float FollowingEnemy::GetCurrentShotTime()
{
	return currentShotTime;
}

void FollowingEnemy::Shoot()
{
	Projectile* bullet = new Projectile(FG::Vector2D(0, 1), FG::Vector2D(position.x, position.y + 40.0f), spriteManager, Projectile::BulletType::EnemyBullet);

	bullet->Active = true;
	FG::EntityManager::Instance()->AddEntity(bullet, "EnemyBullet");
	SoundManager::Instance()->PlaySound("EnemyShot");
	currentShotTime = timeBetweenShots;
}

void FollowingEnemy::EnemyDies()
{
	Player* player = dynamic_cast<Player*>(FG::EntityManager::Instance()->GetPlayer());
	player->AddToScore(score);
	UI::Instance()->UpdateScore();
	SoundManager::Instance()->PlaySound("EnemyExplosion");
	Active = false;
}
