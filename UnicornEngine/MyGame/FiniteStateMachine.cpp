//#include "FiniteStateMachine.h"
//#include "FSMState.h"
//
//void FiniteStateMachine<T>::Configure(T* owner)
//{
//	this->owner = owner;
//}
//
//template <class T>
//void FiniteStateMachine<T>::Update()
//{
//	if (currentState != nullptr)
//	{
//		currentState->Execute(owner);
//	}
//}
//
//template <class T>
//void FiniteStateMachine<T>::ChangeState(FSMState<T>* newState)
//{
//	if (currentState != nullptr)
//	{
//		currentState->Exit(owner);
//	}
//
//	currentState = newState;
//
//	if (newState != nullptr)
//	{
//		currentState->Enter(owner);
//	}
//}