#pragma once
#include <vector>
#include "CollisionManager.h"

#include <map>
#include <string>
/*
Tips: Allocate the memory you are gonna need. then see how you use it
Data that im gonna need/memory im gonna use
CollisionManager pointer
Use of the fucntion CheckCollision to check the collision in my entities

For that, i need two Collider pointers that my CheckcCollsion function takes.
They exist in the Entity which holds the colliders.

Entities exist in Entities list

User story <3
I need as collision manager to take a hold of the collisions to get a collision of my entities
I need my entities list to get entities cz i need my colliders.
I need a functionm that iterates thrpugh the list to check my entities' colliders
*/

namespace FG
{
	class Entity;
	class Camera;
	class CollisionManager;
	class FactoryManager;

	class EntityManager
	{
	public:
		EntityManager() {}
		EntityManager(FG::CollisionManager* collisionManagerRef, FG::FactoryManager* facManagerRef);
		~EntityManager();

		void Shutdown();
		void Update(float deltaTime);
		void Render(Camera* camera);
		void AddEntity(Entity* entity, const std::string& Tag);
		void AddEntity(const std::string& Tag);
		void CheckEntitiesCollision();

		CollisionManager* collisionManager = nullptr;
		FactoryManager* factoryManager = nullptr;
		
	private:
		std::map<std::string, std::vector<Entity*>> entities; //a variable: a list of entities that is called entities
	};
}