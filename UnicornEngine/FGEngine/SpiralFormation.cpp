#include "SpiralFormation.h"
#include "Vector2D.h"
#include <cmath>
#include "EntityManager.h"
#include "spiral"


void FG::SpiralFormation::Spawn()
{
	Vector2D direction;

	int count = 0;
	if (count<enemyNum)
	{
		/*SpiralEnemy* spiralEnemy = new FollowingEnemy(spriteManager);
		followingEnemy->Active = true;*/

		direction = Vector2D(cos(angle * count),sin(angle*count)).Normalized();
		FG::EntityManager::Instance()->AddEntity("SpiralEnemy");
		count++;
	}
}
