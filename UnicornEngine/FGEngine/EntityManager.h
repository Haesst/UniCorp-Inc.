#pragma once

#include <vector>

namespace FG
{
	class Entity;
	class Camera;

	class EntityManager
	{
	public:
		void Shutdown();
		void Update(float deltaTime);
		void Render(Camera* camera);
		void AddEntity(Entity* entity);
	private:
		std::vector<Entity*> entities;
	};
}