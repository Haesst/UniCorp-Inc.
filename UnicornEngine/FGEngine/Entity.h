#pragma once

#include "Sprite.h"
#include "ICollidable.h"

namespace FG
{
	class Camera;
	class Sprite;
	class Collidable;
	class Entity: public Sprite, public Collidable
	{
	public:
		virtual ~Entity() {}

		virtual void Update(float deltaTime) {}
		virtual void Render(Camera* const camera) {}

	};
}