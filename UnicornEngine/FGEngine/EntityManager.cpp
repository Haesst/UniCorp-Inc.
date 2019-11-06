#include "EntityManager.h"

#include "Entity.h"

namespace FG
{
	void EntityManager::Shutdown()
	{
		for (auto it = entities.begin(); it != entities.end(); it++)
		{
			delete* it;
		}

		entities.clear();
	}
	void EntityManager::Update(float deltaTime)
	{
		for (auto& entity : entities)
		{
			entity->Update(deltaTime);
		}
	}
	void EntityManager::Render(Camera* camera)
	{
		for (auto& entity : entities)
		{
			entity->Render(camera);
		}
	}
	void EntityManager::AddEntity(Entity* entity)
	{
		entities.push_back(entity);
	}
}