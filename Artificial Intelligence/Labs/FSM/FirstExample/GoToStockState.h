#pragma once
#include "State.h"

const int SX = 25;
const int SY = 20;

class GoToStockState :
	public State
{
public:
	GoToStockState();
	~GoToStockState();
	void MakeTransition(Player* owner);
	void OnStateEnter(Player* owner);
	void OnStateExit(Player* owner);

};

