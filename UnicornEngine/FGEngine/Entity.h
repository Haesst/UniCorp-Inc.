#pragma once

#include "Sprite.h"
#include "ICollidable.h"
#include "Vector2D.h"

namespace FG
{
	class Camera;
	class Sprite;
	class Collidable;
	class Vector2D;

	class Entity : public Sprite, public Collidable
	{
	public:
		virtual ~Entity() {}

		virtual void Update(float deltaTime) {}
		virtual void Render(Camera* const camera) {}

		virtual void SetPosition(Vector2D position) {}
		virtual Vector2D GetPosition() { return Vector2D(0, 0); }
	};
}