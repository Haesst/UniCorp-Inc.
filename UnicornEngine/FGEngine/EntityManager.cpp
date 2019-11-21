#include "EntityManager.h"
#include "Entity.h"
#include "CollisionManager.h"
#include "FactoryManager.h"

namespace FG
{
	EntityManager::EntityManager(FG::CollisionManager* collisionManagerRef, FG::FactoryManager* facManagerRef)
	{
		collisionManager = collisionManagerRef;
		factoryManager = facManagerRef;
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

	void EntityManager::AddEntity(const std::string& Tag)
	{
		auto it = entities.find(Tag);
		if (it == entities.end())
		{
			entities.insert({ Tag, std::vector<Entity*>() }); //insert takes two values //{} a set of values
			it = entities.find(Tag);
		}
		it->second.push_back(factoryManager->RunFactory(Tag));

		std::cout << Tag << " list contains #" << it->second.size() << " items." << std::endl;
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

	FG::Entity* EntityManager::GetObject(const std::string& Tag)
	{
		auto it = entities.find(Tag);
		if (it == entities.end())
		{
			AddEntity(Tag);
			it = entities.find(Tag);
		}

		if (it->second.empty())
		{
			it->second.push_back(factoryManager->RunFactory(Tag));
		}

		for (size_t i = 0; i < it->second.size(); i++)
		{
			if (!it->second[i]->Active)
			{
				//it->second[i]->Active = true;
				return it->second[i];
				//Entity* GiveMeAnObject = factoryManager->RunFactory(Tag);
				//return GiveMeAnObject;
			}
			else if (i == it->second.size())
			{
				it->second.push_back(factoryManager->RunFactory(Tag));
			}
		}
	}
}
