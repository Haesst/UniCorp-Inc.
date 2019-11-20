#pragma once
#include <iostream>
#include <string.h>
#include <map>
/*
User story <3
map, to know the factories
a function that sets my objects in the factory so that they can be produced

AddFactory()
RunFactory()


*/

namespace FG
{
	class AFactory; //Forward Declaration
	class Entity;

	class FactoryManager
	{
	public:
		FactoryManager();
		~FactoryManager();

		std::map<std::string, AFactory*> factories;

		void AddFactory(const std::string& Namae, AFactory* factory);
		Entity* RunFactory(const std::string& Namae);

	};

}