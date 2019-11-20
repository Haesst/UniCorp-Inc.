#pragma once

template <class T>
class FSMState
{
public:
	virtual void Enter(T* entity) = 0;
	virtual void Execute(T* entity) = 0;
	virtual void Exit(T* entity) = 0;
};