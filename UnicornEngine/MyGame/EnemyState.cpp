#include "EnemyState.h"
#include "Enemy.h"
#include <iostream>

void EnemyState::Idle::Enter(Enemy* entity)
{
}

void EnemyState::Idle::Execute(Enemy* entity)
{
	FG::Vector2D curPos = entity->GetPosition();
	entity->SetPosition(FG::Vector2D(curPos.x + 1, curPos.y + 1));
}

void EnemyState::Idle::Exit(Enemy* entity)
{
}
