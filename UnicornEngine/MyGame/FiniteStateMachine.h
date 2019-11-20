#pragma once

#include "FSMState.h"
#include <memory>

namespace FG
{
	class InputManager;
	class Entity;
}

template <class T>
class FiniteStateMachine
{
private:
	T* owner;
	FSMState<T>* currentState;
public:
	void Configure(T* owner) 
	{
		this->owner = owner;
	}
	void Update()
	{
		if (currentState != nullptr)
		{
			currentState->Execute(owner);
		}
	}
	void ChangeState(FSMState<T>* newState)
	{
		if (currentState != nullptr)
		{
			currentState->Exit(owner);
			delete currentState;
		}

		currentState = newState;

		if (newState != nullptr)
		{
			currentState->Enter(owner);
		}
	}
public:
	virtual ~FiniteStateMachine() {}
};