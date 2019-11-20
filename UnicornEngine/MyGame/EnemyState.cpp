#include "EnemyState.h"
#include <iostream>

void EnemyState::Idle::Enter(Enemy* entity)
{
}

void EnemyState::Idle::Execute(Enemy* entity)
{
	std::cout << "Enemy idle." << std::endl;
}

void EnemyState::Idle::Exit(Enemy* entity)
{
}
