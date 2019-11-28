#pragma once
#include <AbstractFactory.h>
#include <Vector2D.h>

#include "Enemy.h"
#include "FollowingEnemy.h"
#include "SmallEnemy.h"
#include "BigMommaEnemy.h"


namespace FG
{
	class EnemyFactory : public AFactory //inherits from AFactory
	{
	public:
		EnemyFactory() {}
		EnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~EnemyFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new Enemy(spriteManager, pos); }
	};

	class FollowingEnemyFactory : public AFactory
	{
	public:
		FollowingEnemyFactory() {}
		FollowingEnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~FollowingEnemyFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new FollowingEnemy(spriteManager, pos); }
	};

	class SmallEnemyFactory : public AFactory
	{
	public:
		SmallEnemyFactory() {}
		SmallEnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~SmallEnemyFactory() {}

		SpriteManager* spriteManager = nullptr;
		
		virtual Entity* CreateEntity(Vector2D pos) { return new SmallEnemy(spriteManager, pos); }
	};

	class BigMommaFactory : public AFactory
	{
	public:
		BigMommaFactory() {}
		BigMommaFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~BigMommaFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new BigMommaEnemy(spriteManager, pos); }
	};
}