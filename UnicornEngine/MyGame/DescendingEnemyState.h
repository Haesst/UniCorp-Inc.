#pragma once

#include "FiniteStateMachine.h"
#include "FSMState.h"

class DescendingEnemy;

class DescendingEnemyState : public FiniteStateMachine<DescendingEnemy>
{
public:
	class AttackPlayer : public FSMState<DescendingEnemy>
	{
	private:
		float maxX = 500.0f;
		float minX = 10.0f;

		float currentY = 0;
		bool goingRight = true;

	public:
		void Enter(DescendingEnemy* entity) override;
		void Execute(DescendingEnemy* entity) override;
		void Exit(DescendingEnemy* entity) override;
	};
	class Idle : public FSMState<DescendingEnemy>
	{
	public:
		void Enter(DescendingEnemy* entity) override;
		void Execute(DescendingEnemy* entity) override;
		void Exit(DescendingEnemy* entity) override;
	};
};

