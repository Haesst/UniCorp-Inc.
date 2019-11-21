#pragma once
#include <AbstractFactory.h>

#include "Enemy.h"

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

}