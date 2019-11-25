#pragma once

namespace FG
{
	class SpriralFormation
	{
	public:
		SpriralFormation() {}
		~SpriralFormation() {}

		int enemyNum = 0;
		float angle = 0.f;

	private:
		void Spawn();
	};
}