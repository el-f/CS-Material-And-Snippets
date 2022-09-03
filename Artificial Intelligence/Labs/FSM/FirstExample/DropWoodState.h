#pragma once
#include "State.h"
class DropWoodState :
	public State
{
public:
	DropWoodState();
	~DropWoodState();
	void MakeTransition(Player* owner);
	void OnStateEnter(Player* owner);
	void OnStateExit(Player* owner);

};

