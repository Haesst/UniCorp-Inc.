#include "SmallEnemy.h"
#include "FSMState.h"
#include "MusicManager.h"
#include "Projectile.h"

#include <SpriteManager.h>
#include <EntityManager.h>

void SmallEnemy::onCollision(Tag tagau)
{
}

SmallEnemy::SmallEnemy(FG::SpriteManager* spriteManagerRef, bool startingLeft/* = true*/)
{
	Active = true;

	if (startingLeft)
	{
		position.x = 10.0f;
		goingRight = true;
	}
	else
	{
		position.x = 460.0f;
		goingRight = false;
	}

	position.y = 50.0f;
	spriteManager = spriteManagerRef;

	sprite = spriteManager->CreateSprite("../TestingAssets/SmallEnemy.png", 1, 1, 37, 33);

	rect = { 0,0,37,33 };
	myCollider->square.w = rect.w;
	myCollider->square.h = rect.h;
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	rect = { (int)position.x, (int)position.y, 37, 33 };
	myCollider->square.x = rect.x;
	myCollider->square.y = rect.y;

	enemyState = new SmallEnemyState();
	enemyState->Configure(this);
	enemyState->ChangeState(new SmallEnemyState::AttackPlayer());
	myTagau = Tag::Enemyau;
}

void SmallEnemy::Update(float deltaTime)
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

void SmallEnemy::Render(FG::Camera* const camera)
{
	spriteManager->Draw(sprite, rect);
	spriteManager->DebugDraw(myCollider->square);
}

float SmallEnemy::GetCurrentShotTime()
{
	return currentShotTime;
}

void SmallEnemy::Shoot()
{
	fired = true;

	Projectile* bullet = new Projectile(FG::Vector2D(0, 1), FG::Vector2D(position.x, position.y + 40.0f), spriteManager, Projectile::BulletType::EnemyBullet);

	bullet->Active = true;
	FG::EntityManager::Instance()->AddEntity(bullet, "EnemyBullet");
	MusicManager::Instance()->PlaySound("EnemyShot");
	currentShotTime = timeBetweenShots;
	shotsToFire--;
}

bool SmallEnemy::HaveFired()
{
	return fired;
}

bool SmallEnemy::GoingRight()
{
	return goingRight;
}

void SmallEnemy::ChangeState(FSMState<SmallEnemy>* state)
{
	enemyState->ChangeState(state);
}

int SmallEnemy::ShotsToFire()
{
	return shotsToFire;
}
