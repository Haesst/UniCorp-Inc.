#include "CollisionManager.h"
#include "Collider.h"

FG::CollisionManager::CollisionManager()
{
}

FG::CollisionManager::~CollisionManager()
{
}

bool FG::CollisionManager::CheckCollision(Collider colRef1, Collider colRef2)
{
	if (colRef1.bounds.top <= colRef2.bounds.bottom || 
		colRef1.bounds.bottom >= colRef2.bounds.top ||
		colRef1.bounds.right >= colRef2.bounds.left ||
		colRef1.bounds.left <= colRef2.bounds.right)
	{
		return true;
	}
	else { return false; }
	
}
