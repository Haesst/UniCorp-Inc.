#pragma once

namespace FG
{
	class Collider;
	class ICollidable;

	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();

		bool CheckCollision(FG::Collider* colRef1, FG::Collider* colRef2);
	};

}