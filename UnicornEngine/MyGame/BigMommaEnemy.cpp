#include "BigMommaEnemy.h"

#include <SpriteManager.h>
#include <EntityManager.h>

#include "BigMommaState.h"
#include "LaserBeam.h"
#include "SoundManager.h"
#include "Player.h"
#include "UI.h"

void BigMommaEnemy::onCollision(Tag tagau)
{
	if (tagau == PlayerBulletau)
	{
		health--;
		if (health <= 0)
		{
			EnemyDies();
		}
	}
}

BigMommaEnemy::BigMommaEnemy(FG::SpriteManager* spriteManagerRef, FG::Vector2D position)
{
	Active = true;
	this->position = position;
	spriteManager = spriteManagerRef;
	score = 50;
	health = 10;
	timeBetweenShots = 2.0f;

	sprite = spriteManager->CreateSprite("../TestingAssets/BigMomma.png", 0, 0, 60, 64);

	rect = { (int)position.x, (int)position.y, 60, 64 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;
	myTagau = Tag::Enemyau;

	enemyState = new BigMommaState();
	enemyState->Configure(this);
	enemyState->ChangeState(new BigMommaState::AttackPlayer());
}

void BigMommaEnemy::Update(float deltaTime)
{
	if (currentShotTime > 0)
	{
		currentShotTime -= deltaTime;
	}

	enemyState->Update();

	rect = { (int)position.x, (int)position.y, 60, 64 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	UpdateCollider();
}

void BigMommaEnemy::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}

void BigMommaEnemy::Shoot()
{
	LaserBeam* bullet = new LaserBeam(FG::Vector2D(0, 1), FG::Vector2D(position.x, position.y + 40.0f), spriteManager, this, laserTime);

	bullet->Active = true;
	FG::EntityManager::Instance()->AddEntity(bullet, "EnemyBullet");
	SoundManager::Instance()->PlaySound("EnemyShot");
	currentShotTime = timeBetweenShots + laserTime;
}

float BigMommaEnemy::GetCurrentShotTime()
{
	return currentShotTime;
}

void BigMommaEnemy::EnemyDies()
{
	Player* player = dynamic_cast<Player*>(FG::EntityManager::Instance()->GetPlayer());
	player->AddToScore(score);
	UI::Instance()->UpdateScore();
	SoundManager::Instance()->PlaySound("EnemyExplosion");
	Active = false;
}
