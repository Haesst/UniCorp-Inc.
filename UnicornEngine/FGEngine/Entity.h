#pragma once

namespace FG
{
	class Camera;

	class Entity
	{
	public:
		virtual ~Entity() {}

		virtual void Update(float deltaTime) {}
		virtual void Render(Camera* const camera) {}
	};
}