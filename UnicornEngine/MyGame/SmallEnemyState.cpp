#include "SmallEnemyState.h"
#include "SmallEnemy.h"

#include <EntityManager.h>
#include <Entity.h>

void SmallEnemyState::AttackPlayer::Enter(SmallEnemy* entity)
{
	player = FG::EntityManager::Instance()->GetPlayer();
}

void SmallEnemyState::AttackPlayer::Execute(SmallEnemy* entity)
{
	FG::Vector2D position = entity->GetPosition();
	FG::Vector2D playerPosition = player->GetPosition();

	float directionX = 0.0f;
	float directionY = 0.0f;

	if (position.y < (playerPosition.y - 200.0f))
	{
		directionY = 3;
	}
	else
	{
		if ((playerPosition.y - position.y) < 200.0f)
		{
			directionY = -3;
		}
	}

	if (entity->GoingRight())
	{
		directionX = 3;
	}
	else
	{
		directionX = -3;
	}

	entity->SetPosition(FG::Vector2D(position.x + directionX, position.y + directionY));

	if (entity->GetPosition().y >= maxY)
	{
		entity->ChangeState(new SmallEnemyState::Flee);
	}

	float xDistance = position.x - playerPosition.x;
	if (xDistance < 5.0f && xDistance > -5.0f && position.y < 0)
	{
		if (entity->GetCurrentShotTime() <= 0.0f && entity->ShotsToFire() > 0)
		{
			entity->Shoot();
		}
	}
}

void SmallEnemyState::AttackPlayer::Exit(SmallEnemy* entity)
{
}

void SmallEnemyState::Flee::Enter(SmallEnemy* entity)
{
	player = FG::EntityManager::Instance()->GetPlayer();
}

void SmallEnemyState::Flee::Execute(SmallEnemy* entity)
{
	float xDirection = 0.0f;
	float yDirection = -3.0f;

	if (entity->GoingRight())
	{
		xDirection = 3.0f;
	}
	else
	{
		xDirection = -3.0f;
	}

	entity->SetPosition(FG::Vector2D(entity->GetPosition().x + xDirection, entity->GetPosition().y + yDirection));

	if (entity->GetPosition().y < 0.0f)
	{
		entity->Active = false;
	}

	float xDifference = entity->GetPosition().x - player->GetPosition().x;

	if (xDifference < 5.0f && entity->position.y > 0 && xDifference > -5.0f)
	{
		if (entity->GetCurrentShotTime() <= 0.0f && entity->ShotsToFire() > 0)
		{
			entity->Shoot();
		}
	}
}

void SmallEnemyState::Flee::Exit(SmallEnemy* entity)
{
}
