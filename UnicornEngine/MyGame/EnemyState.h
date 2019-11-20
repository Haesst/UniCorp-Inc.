#pragma once

#include "FiniteStateMachine.h"
#include "FSMState.h"

class Enemy;

class EnemyState : public FiniteStateMachine<Enemy>
{
public:
	class Idle : public FSMState<Enemy>
	{
	public:
		void Enter(Enemy* entity) override;
		void Execute(Enemy* entity) override;
		void Exit(Enemy* entity) override;
	};
};

