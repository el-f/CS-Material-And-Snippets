#pragma once
#include "State.h"
class GoToForestState :
	public State
{
public:
	GoToForestState();
	~GoToForestState();
	void MakeTransition(Player* owner);
	void OnStateEnter(Player* owner);
	void OnStateExit(Player* owner);

};

