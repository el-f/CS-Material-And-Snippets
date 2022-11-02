#pragma once
// pure virtual class (interface)

#include "Entity.h"
class State
{
public:
	virtual void MakeTransition(Entity* owner) = 0;
	virtual void OnStateEnter(Entity* owner) = 0;
	virtual void OnStateExit(Entity* owner) = 0;
};
