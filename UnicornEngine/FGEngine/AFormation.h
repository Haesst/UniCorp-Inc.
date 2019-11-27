#pragma once
#include <vector>


namespace FG
{
	class Vector2D;

	class AFormation
	{
	protected:
		AFormation(){}
		~AFormation(){}

		std::vector<Vector2D> formationPos;

	};
}