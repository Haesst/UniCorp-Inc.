#pragma once
#include "Config.h"

namespace FG
{
	class Collider;
	class Collidable
	{
	public:
		Collidable();
		Collidable(Collider* collider);
		virtual ~Collidable(); //i write over sth, override

		virtual void onCollision(Tag tagau) = 0;

		Collider* myCollider; 
	};
}