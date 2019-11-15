#pragma once

#include "Sprite.h"
#include "ICollidable.h"
#include "Collider.h"

namespace FG
{ 
	class Camera;
	class Sprite;
	class Collidable;
	class Entity: public Sprite, public Collidable
	{
	public:
		virtual ~Entity() {}

		void UpdateCollider()
		{
			myCollider->bounds.bottom = myCollider->square.y + myCollider->square.h;
			myCollider->bounds.top = myCollider->square.y;
			myCollider->bounds.right = myCollider->square.x + myCollider->square.w;
			myCollider->bounds.left = myCollider->square.x;
		}

		virtual void Update(float deltaTime) {}
		virtual void Render(Camera* const camera) {}
		Sprite* sprite = nullptr;
		SDL_Rect rect;

		float movementSpeed = 250.0f;

	};
}