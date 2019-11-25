#include "EnemyState.h"
#include "Enemy.h"

#include <Entity.h>
#include <EntityManager.h>

void EnemyState::Idle::Enter(Enemy* entity)
{}

void EnemyState::Idle::Execute(Enemy* entity)
{
	FG::Vector2D curPos = entity->GetPosition();
	entity->SetPosition(FG::Vector2D(curPos.x + 1, curPos.y + 1));
}

void EnemyState::Idle::Exit(Enemy* entity)
{}

void EnemyState::AttackPlayer::Enter(Enemy* entity)
{
	this->currentY = entity->GetPosition().y;
}

void EnemyState::AttackPlayer::Execute(Enemy* entity)
{
	FG::Vector2D curPos = entity->GetPosition();

	if (goingRight)
	{
		if (curPos.x < maxX)
		{
			entity->SetPosition(FG::Vector2D(curPos.x + 1, curPos.y));
		}
		else
		{
			if (currentY + 40.0f > curPos.y)
			{
				entity->SetPosition(FG::Vector2D(curPos.x, curPos.y + 1));
			}
			else
			{
				goingRight = false;
				currentY = curPos.y;
			}
		}
	}
	else
	{
		if (curPos.x > minX)
		{
			entity->SetPosition(FG::Vector2D(curPos.x - 1, curPos.y));
		}
		else
		{
			if (currentY + 20.0f > curPos.y)
			{
				entity->SetPosition(FG::Vector2D(curPos.x, curPos.y + 1));
			}
			else
			{
				goingRight = true;
				currentY = curPos.y;
			}
		}
	}

	if (entity->GetCurrentShotTime() <= 0)
	{
		FG::Entity* player = FG::EntityManager::Instance()->GetPlayer();

		float differenceBetweenPlayer = 500.0f;

		if (player != nullptr)
			differenceBetweenPlayer = player->GetPosition().x - entity->GetPosition().x;

		if (differenceBetweenPlayer < 5 && differenceBetweenPlayer > -5)
			entity->Shoot();
			
	
	}
}

void EnemyState::AttackPlayer::Exit(Enemy* entity)
{}
