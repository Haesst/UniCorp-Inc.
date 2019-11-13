#pragma once

namespace FG
{
	class Collider;

	class CollisionManager
	{
	public:
		CollisionManager();
		~CollisionManager();

		bool CheckCollision(Collider colRef1, Collider colRef2);
	};

}