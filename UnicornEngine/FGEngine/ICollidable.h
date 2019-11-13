#pragma once

namespace FG
{
	class Collider;
	class Collidable
	{
	public:
		Collidable();
		Collidable(Collider* collider);
		virtual ~Collidable(); //i write over sth, override

		virtual void onCollision(Collider* theOtherCollider);

		Collider* myCollider; 
	};
}