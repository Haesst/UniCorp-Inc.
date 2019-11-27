#pragma once
#include <AbstractFactory.h>

#include "Enemy.h"
#include "FollowingEnemy.h"
#include "SmallEnemy.h"

#include <iostream>

namespace FG
{
	class EnemyFactory : public AFactory //inherits from AFactory
	{
	public:
		EnemyFactory() {}
		EnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~EnemyFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity() { return new Enemy(spriteManager); }
	};

	class FollowingEnemyFactory : public AFactory
	{
	public:
		FollowingEnemyFactory() {}
		FollowingEnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~FollowingEnemyFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity() { return new FollowingEnemy(spriteManager); }
	};

	class SmallEnemyFactory : public AFactory
	{
	public:
		SmallEnemyFactory() {}
		SmallEnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~SmallEnemyFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity() { return new SmallEnemy(spriteManager); }
	};
}