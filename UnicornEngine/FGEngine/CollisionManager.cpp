#include "CollisionManager.h"
#include "Collider.h"
#include "ICollidable.h"

FG::CollisionManager::CollisionManager()
{
}

FG::CollisionManager::~CollisionManager()
{
}

bool FG::CollisionManager::CheckCollision(FG::Collider* colRef1, FG::Collider* colRef2)
{
	if (colRef1->bounds.right < colRef2->bounds.left ||
		colRef2->bounds.right < colRef1->bounds.right||
		colRef1->bounds.bottom < colRef2->bounds.top ||
		colRef2->bounds.bottom < colRef1->bounds.top)
	{
		return false;
	}
	else { return true; }
	
}
