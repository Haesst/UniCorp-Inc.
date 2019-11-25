#pragma once

#include "FiniteStateMachine.h"
#include "FSMState.h"

class FollowingEnemy;
namespace FG
{
	class Entity;
}

class FollowingEnemyState : public FiniteStateMachine<FollowingEnemy>
{
public:
	class AttackPlayer : public FSMState<FollowingEnemy>
	{
	private:
		float maxX = 500.0f;
		float minX = 10.0f;
		FG::Entity* player = nullptr;

	public:
		void Enter(FollowingEnemy* entity) override;
		void Execute(FollowingEnemy* entity) override;
		void Exit(FollowingEnemy* entity) override;
	};
};

