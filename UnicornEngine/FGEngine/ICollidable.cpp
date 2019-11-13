#include "ICollidable.h"
#include "Collider.h"

FG::Collidable::Collidable()
{
	myCollider = new FG::Collider();
}

FG::Collidable::Collidable(Collider* collider)
{
	myCollider = collider;
}

FG::Collidable::~Collidable()
{
	delete myCollider;
	myCollider = nullptr;
}

void FG::Collidable::onCollision(Collider* theOtherCollider)
{
}
