#include "DescendingEnemyState.h"
#include "DescendingEnemy.h"

#include <Entity.h>
#include <EntityManager.h>

void DescendingEnemyState::Idle::Enter(DescendingEnemy* entity)
{}

void DescendingEnemyState::Idle::Execute(DescendingEnemy* entity)
{
	FG::Vector2D curPos = entity->GetPosition();
	entity->SetPosition(FG::Vector2D(curPos.x, curPos.y + 1));
}

void DescendingEnemyState::Idle::Exit(DescendingEnemy* entity)
{}

void DescendingEnemyState::AttackPlayer::Enter(DescendingEnemy* entity)
{
	this->currentY = entity->GetPosition().y;
}

void DescendingEnemyState::AttackPlayer::Execute(DescendingEnemy* entity)
{
	FG::Vector2D curPos = entity->GetPosition();

	entity->SetPosition(FG::Vector2D(curPos.x, curPos.y + 1));

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

void DescendingEnemyState::AttackPlayer::Exit(DescendingEnemy* entity)
{}
