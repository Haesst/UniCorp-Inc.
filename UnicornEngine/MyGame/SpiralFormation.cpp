#include "SpiralFormation.h"
#include "Vector2D.h"
#include <cmath>
#include "EntityManager.h"
#include "SpiralEnemy.h"



#include <iostream>


SpiralFormation::SpiralFormation(FG::SpriteManager* spriteManager)
{
	this->spriteManager = spriteManager;
}

void SpiralFormation::Spawn()
{
	

	
	if (counter < enemyNum)
	{
		FG::Vector2D* direction = new FG::Vector2D(FG::Vector2D(cos(angle * counter), sin(angle * counter)).Normalized());
		SpiralEnemy* spiralEnemy = new SpiralEnemy(spriteManager, direction);
		spiralEnemy->Active = true;
		FG::EntityManager::Instance()->AddEntity(spiralEnemy, "SpiralEnemy");
		counter++;
	}
}
