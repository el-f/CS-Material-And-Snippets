#pragma once
#include "State.h"
class ChoppingState :
	public State
{
public:
	ChoppingState();
	~ChoppingState();
	void MakeTransition(Player* owner);
	void OnStateEnter(Player* owner);
	void OnStateExit(Player* owner);

};

