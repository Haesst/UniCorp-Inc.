#pragma once

#include "FiniteStateMachine.h"
#include "FSMState.h"

class SmallEnemy;

class SmallEnemyState : public FiniteStateMachine<SmallEnemy>
{
public:
	class AttackPlayer : public FSMState<SmallEnemy>
	{
	private:
		float minY = 10.0f;
		float maxY = 400.0f;

		FG::Entity* player = nullptr;

	public:
		void Enter(SmallEnemy* entity) override;
		void Execute(SmallEnemy* entity) override;
		void Exit(SmallEnemy* entity) override;
	};
	
	class Flee : public FSMState<SmallEnemy>
	{
	private:
		FG::Entity* player = nullptr;
		
	public:
		void Enter(SmallEnemy* entity) override;
		void Execute(SmallEnemy* entity) override;
		void Exit(SmallEnemy* entity) override;
	};
};

