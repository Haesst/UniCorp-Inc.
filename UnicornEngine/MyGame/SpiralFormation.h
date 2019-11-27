#pragma once
#include "Vector2D.h"
#include "EntityManager.h"
#include "SpriteManager.h"
#include <cmath>

namespace FG
{
}

class SpiralFormation
{
public:
	SpiralFormation() {}
	SpiralFormation(FG::SpriteManager* spriteManager);
	~SpiralFormation() {}

	int enemyNum = 64;
	int counter = 0;
	float angle = M_PI / 8;
	void Spawn();

private:
	FG::Vector2D position;
	FG::SpriteManager* spriteManager;
};