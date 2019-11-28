#pragma once

#include "FiniteStateMachine.h"
#include "FSMState.h"

class BigMommaEnemy;
namespace FG
{
	class Entity;
}

class BigMommaState : public FiniteStateMachine<BigMommaEnemy>
{
public:
	class AttackPlayer : public FSMState<BigMommaEnemy>
	{
	private:
		float maxX = 500.0f;
		float minX = 10.0f;
		FG::Entity* player = nullptr;

	public:
		void Enter(BigMommaEnemy* entity) override;
		void Execute(BigMommaEnemy* entity) override;
		void Exit(BigMommaEnemy* entity) override;
	};
};

