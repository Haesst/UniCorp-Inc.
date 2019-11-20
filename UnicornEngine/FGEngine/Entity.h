#pragma once

#include "Sprite.h"
#include "ICollidable.h"
#include "Collider.h"
#include "Config.h"
#include "Vector2D.h"

namespace FG
{
	class Camera;
	class Sprite;
	class Collidable;

	class Entity : public Sprite, public Collidable
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
		Tag myTagau;
		Vector2D position;

		bool Active = true;

		float movementSpeed = 250.0f;

		virtual Vector2D GetPosition() { return position; }
		virtual void SetPosition(Vector2D position) { this->position = position; }

		// Inherited via Collidable
		virtual void onCollision(Tag tagau) = 0;

	};
}