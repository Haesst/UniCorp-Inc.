#pragma once

#include "FiniteStateMachine.h"
#include "FSMState.h"

class Enemy;

class EnemyState : public FiniteStateMachine<Enemy>
{
public:
	class AttackPlayer : public FSMState<Enemy>
	{
	private:
		float maxX = 500.0f;
		float minX = 10.0f;

		float currentY = 0;
		bool goingRight = true;
	
	public:
		void Enter(Enemy* entity) override;
		void Execute(Enemy* entity) override;
		void Exit(Enemy* entity) override;
	};
	class Idle : public FSMState<Enemy>
	{
	public:
		void Enter(Enemy* entity) override;
		void Execute(Enemy* entity) override;
		void Exit(Enemy* entity) override;
	};
};

