#pragma once

namespace FG
{
	class InputManager;
	class Entity;
}

class IFiniteStateMachine
{
public:
	virtual ~IFiniteStateMachine() {}

	virtual void Update(FG::Entity* entity, float deltaTime) = 0;
	virtual void Entry(FG::Entity* entity) = 0;
	virtual void Exit(FG::Entity* entity) = 0;

};