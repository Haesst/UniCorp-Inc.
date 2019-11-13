#include "Collider.h"

FG::Collider::Collider()
{
	bounds.bottom = square.y + square.h;
	bounds.top = square.y;
	bounds.right = square.x + square.w;
	bounds.left = square.x;
}

FG::Collider::~Collider()
{

}
