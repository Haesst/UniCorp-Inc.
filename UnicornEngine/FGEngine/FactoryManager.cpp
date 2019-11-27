#include "FactoryManager.h"
#include "AbstractFactory.h"
#include "Vector2D.h"
FG::FactoryManager::FactoryManager()
{
	
}

FG::FactoryManager::~FactoryManager()
{
}

void FG::FactoryManager::AddFactory(const std::string& Namae, AFactory* factory)
{
	auto it = factories.find(Namae); //it = iterator which saves the returned factory from the factory list.
	
	if (it == factories.end())
	{
		factories.insert({ Namae, factory });
	}
	else
	{
		std::cout << "There is already a factory using tag: " << Namae << std::endl;
	}
}

FG::Entity* FG::FactoryManager::RunFactory(const std::string& Namae, Vector2D position)
{
	auto it = factories.find(Namae);
	if (it == factories.end())
	{
		std::cout << "Cant proceed further, No factory for: " << Namae << std::endl;
	}
	else
	{
		return it->second->CreateEntity();
	}
}
