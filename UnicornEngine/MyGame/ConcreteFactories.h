#pragma once
#include <AbstractFactory.h>
#include <Vector2D.h>

#include "Enemy.h"
#include "FollowingEnemy.h"
#include "SmallEnemy.h"
#include "SpiralEnemy.h"
#include "DescendingEnemy.h"
#include "BigMommaEnemy.h"

#include "Powerup.h"
#include "PowerupLife.h"
#include "PowerupSpread.h"
#include "PowerupMultiSpread.h"
#include "PowerupRingshot.h"
#include "PowerupMoveSpeed.h"
#include "PowerupAttackSpeed.h"

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

	class DescendingEnemyFactory : public AFactory
	{
	public:
		DescendingEnemyFactory() {}
		DescendingEnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~DescendingEnemyFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new DescendingEnemy(spriteManager, pos); }
	};
	/*
	class SpiralEnemyFactory : public AFactory
	{
	public:
		SpiralEnemyFactory() {}
		SpiralEnemyFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~SpiralEnemyFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new SpiralEnemy(spriteManager, pos); }
	};*/
	class BigMommaFactory : public AFactory
	{
	public:
		BigMommaFactory() {}
		BigMommaFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~BigMommaFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new BigMommaEnemy(spriteManager, pos); }
	};



	class PowerupFactory : public AFactory //inherits from AFactory
	{
	public:
		PowerupFactory() {}
		PowerupFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~PowerupFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new Powerup(spriteManager, pos); }
	};


	class PowerupLifeFactory : public AFactory //inherits from AFactory
	{
	public:
		PowerupLifeFactory() {}
		PowerupLifeFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~PowerupLifeFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new PowerupLife(spriteManager, pos); }
	};


	class PowerupSpreadFactory : public AFactory //inherits from AFactory
	{
	public:
		PowerupSpreadFactory() {}
		PowerupSpreadFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~PowerupSpreadFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new PowerupSpread(spriteManager, pos); }
	};


	class PowerupMultiSpreadFactory : public AFactory //inherits from AFactory
	{
	public:
		PowerupMultiSpreadFactory() {}
		PowerupMultiSpreadFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~PowerupMultiSpreadFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new PowerupMultiSpread(spriteManager, pos); }
	};


	class PowerupRingshotFactory : public AFactory //inherits from AFactory
	{
	public:
		PowerupRingshotFactory() {}
		PowerupRingshotFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~PowerupRingshotFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new PowerupRingshot(spriteManager, pos); }
	};

	class PowerupMoveSpeedFactory : public AFactory //inherits from AFactory
	{
	public:
		PowerupMoveSpeedFactory() {}
		PowerupMoveSpeedFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~PowerupMoveSpeedFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new PowerupMoveSpeed(spriteManager, pos); }
	};

	class PowerupAttackSpeedFactory : public AFactory //inherits from AFactory
	{
	public:
		PowerupAttackSpeedFactory() {}
		PowerupAttackSpeedFactory(FG::SpriteManager* spriteManagerRef) { spriteManager = spriteManagerRef; }
		~PowerupAttackSpeedFactory() {}

		SpriteManager* spriteManager = nullptr;

		virtual Entity* CreateEntity(Vector2D pos) { return new PowerupAttackSpeed(spriteManager, pos); }
	};
}