#include "FollowingEnemyState.h"
#include "FollowingEnemy.h"
#include "Entity.h"
#include "EntityManager.h"

#include <iostream>

void FollowingEnemyState::AttackPlayer::Enter(FollowingEnemy* entity)
{
	player = FG::EntityManager::Instance()->GetPlayer();
}

void FollowingEnemyState::AttackPlayer::Execute(FollowingEnemy* entity)
{

	FG::Vector2D position = entity->GetPosition();
	FG::Vector2D playerPosition = player->GetPosition();

	float differenceX = position.x - playerPosition.x;
	
	float xDirection = 0.0f;
	float yDirection = 0.0f;
	if (position.x < playerPosition.x && (differenceX > 5.0f || differenceX < -5.0f))
	{
		xDirection = 1.0f;
	}
	else if (position.x > playerPosition.x && (differenceX > 5.0f || differenceX < -5.0f))
	{
		xDirection = -1.0f;
	}

	if (position.y < 300.0f && position.y < (playerPosition.y - 200.0f))
	{
		yDirection = 1.0f;
	}
	else if (playerPosition.y - position.y < 200.0f)
	{
		yDirection = -1.0f;
	}

	entity->SetPosition(FG::Vector2D(position.x + xDirection, position.y + yDirection));

	if (entity->GetCurrentShotTime() <= 0.0f && (differenceX < 5.0f && differenceX > -5.0f))
	{
		entity->Shoot();
	}
}

void FollowingEnemyState::AttackPlayer::Exit(FollowingEnemy* entity)
{
}
