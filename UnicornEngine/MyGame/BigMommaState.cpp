#include "BigMommaState.h"

#include <EntityManager.h>

#include "BigMommaEnemy.h"

#include <iostream>

void BigMommaState::AttackPlayer::Enter(BigMommaEnemy* entity)
{
	player = FG::EntityManager::Instance()->GetPlayer();
}

void BigMommaState::AttackPlayer::Execute(BigMommaEnemy* entity)
{
	FG::Vector2D position = entity->GetPosition();
	FG::Vector2D playerPosition = player->GetPosition();

	float differenceX = position.x - playerPosition.x;

	float xDirection = 0.0f;
	float yDirection = 0.0f; 

	if (position.x < playerPosition.x && (differenceX > 5.0f || differenceX < -5.0f))
	{
		xDirection = 0.4f;
	}
	else if (position.x > playerPosition.x && (differenceX > 5.0f || differenceX < -5.0f))
	{
		xDirection = -0.4f;
	}

	if (position.y < 5)
	{
		yDirection = 3.0f;
	}
	else if (position.y < 300.0f && position.y < (playerPosition.y - 200.0f))
	{
		yDirection = 0.4f;
	}
	else if (playerPosition.y - position.y < 400.0f)
	{
		yDirection = -0.4f;
	}

	entity->SetPosition(FG::Vector2D(position.x + xDirection, position.y + yDirection));

	if (entity->GetCurrentShotTime() <= 0.0f && position.y > 0)
	{
		std::cout << entity->GetCurrentShotTime() << std::endl;
		entity->Shoot();
	}
}

void BigMommaState::AttackPlayer::Exit(BigMommaEnemy* entity)
{

}
