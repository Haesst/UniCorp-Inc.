#pragma once

namespace FG
{
	class Entity;

	class AFactory
	{
	public:
		AFactory() {}
		virtual ~AFactory() {}

		virtual Entity* CreateEntity(Vector2D pos) = 0;
	};
}