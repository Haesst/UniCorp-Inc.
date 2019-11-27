#pragma once
#include <AbstractFactory.h>
#include <Vector2D.h>

#include "Enemy.h"
#include "FollowingEnemy.h"
#include "SmallEnemy.h"


namespace FG
{
	class EnemyFactory : public AFactory //inherits from AFactory
	{
	public:
		EnemyFactory() {}
		EnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~EnemyFactory() {}

		SpriteManager* spriteManager = nullptr;
		Vector2D position;

		virtual Entity* CreateEntity() { return new Enemy(spriteManager, position); }
	};

	class FollowingEnemyFactory : public AFactory
	{
	public:
		FollowingEnemyFactory() {}
		FollowingEnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~FollowingEnemyFactory() {}

		SpriteManager* spriteManager = nullptr;
		Vector2D position;

		virtual Entity* CreateEntity() { return new FollowingEnemy(spriteManager, position); }
	};

	class SmallEnemyFactory : public AFactory
	{
	public:
		SmallEnemyFactory() {}
		SmallEnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~SmallEnemyFactory() {}

		SpriteManager* spriteManager = nullptr;
		Vector2D position;

		virtual Entity* CreateEntity() { return new SmallEnemy(spriteManager, position); }
	};
}