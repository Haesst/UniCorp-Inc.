#include "EntityManager.h"
#include "Entity.h"
#include "CollisionManager.h"

namespace FG
{
	EntityManager::EntityManager(FG::CollisionManager* collisionManagerRef)
	{
		collisionManager = collisionManagerRef;
	}
	EntityManager::~EntityManager()
	{
	}
	void EntityManager::Shutdown()
	{
		for (auto& it : entities)
		{
			for (auto ent = it.second.begin(); ent != it.second.end(); ent++)
			{
				delete* ent;
			}
		}

		entities.clear();
	}
	void EntityManager::Update(float deltaTime)
	{
		for (auto& it : entities)
		{
			for (auto& entity : it.second)
			{
				if (entity->Active)
				{
					entity->Update(deltaTime);
				}
			}
		}
	}
	void EntityManager::Render(Camera* camera)
	{
		for (auto& it : entities)
		{
			for (auto& entity : it.second)
			{
				if (entity->Active)
				{
					entity->Render(camera);
				}
			}
		}
	}
	void EntityManager::AddEntity(Entity* entity, const std::string& Tag)
	{
		auto it = entities.find(Tag);
		if (it == entities.end())
		{
			entities.insert({ Tag, std::vector<Entity*>() }); //insert takes two values //{} a set of values
			it = entities.find(Tag);
		}
		it->second.push_back(entity);
	}

	void EntityManager::CheckEntitiesCollision()
	{

		for (auto& firstList : entities)
		{
			for (auto& firstIT : firstList.second)
			{
				if (firstIT->Active)
				{
					for (auto& secondList : entities)
					{
						for (auto& secondIT : secondList.second)
						{
							if (firstIT != secondIT && secondIT->Active)
							{
								//Do something
								if (collisionManager->CheckCollision(firstIT->myCollider, secondIT->myCollider))
								{
									firstIT->onCollision(secondIT->myTagau);
									secondIT->onCollision(firstIT->myTagau);
								}

							}
							else { /*Do nothing*/ }
						}
					}
				}
			}
		}

		
	}

	
	
}

/*
for(auto& ent1 : entities)
{
for(auto& ent2 : entities)
{
if(ent2 != ent1 && ent2.active)
{
checkCollision() {}
}
}
}

*/