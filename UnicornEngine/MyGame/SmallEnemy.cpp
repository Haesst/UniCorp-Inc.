#include "SmallEnemy.h"
#include "FSMState.h"
#include "SoundManager.h"
#include "BigEnemyBullet.h"
#include "Player.h"
#include "UI.h"

#include <SpriteManager.h>
#include <EntityManager.h>
#include <Camera.h>

#include <iostream>

void SmallEnemy::onCollision(Tag tagau)
{
	switch (tagau)
	{
	case PlayerBulletau:
		EnemyDies();
		break;
	}
}

SmallEnemy::SmallEnemy(FG::SpriteManager* spriteManagerRef, FG::Vector2D pos, bool startingLeft/* = true*/)
{
	position.x = pos.x;
	position.y = pos.y;
	score = 15;
	health = 1;
	Active = true;

	if (position.x > 0)
	{
		startingLeft = false;
	}

	if (startingLeft)
	{
		goingRight = true;
	}
	else
	{
		goingRight = false;
	}

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
	CheckIfVisible();

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
	if (window == nullptr)
	{
		window = camera->GetWindow()->GetInternalWindow();
	}

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

	BigEnemyBullet* bullet = new BigEnemyBullet(FG::Vector2D(0, 1), FG::Vector2D(position.x, position.y + 40.0f), spriteManager);

	bullet->Active = true;
	FG::EntityManager::Instance()->AddEntity(bullet, "BigEnemyBullet");
	SoundManager::Instance()->PlaySound("BigEnemyBullet");
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

void SmallEnemy::EnemyDies()
{
	Player* player = dynamic_cast<Player*>(FG::EntityManager::Instance()->GetPlayer());
	player->AddToScore(score);
	UI::Instance()->UpdateScore();
	SoundManager::Instance()->PlaySound("EnemyExplosion");
	Active = false;
}
