#pragma once

#include "FiniteStateMachine.h"
#include "FSMState.h"

class Player;

class PlayerState : public FiniteStateMachine<Player>
{

public:
	class Idle : public FSMState<Player>
	{
	public:


		void Enter(Player* entity) override;


		void Execute(Player* entity) override;


		void Exit(Player* entity) override;

	};

};

