#pragma once

#include "IFiniteStateMachine.h"

class PlayerState : public IFiniteStateMachine
{

public:
	void Update(FG::Entity* entity, float deltaTime) override;


	void Entry(FG::Entity* entity) override {};


	void Exit(FG::Entity* entity) override {};

};

