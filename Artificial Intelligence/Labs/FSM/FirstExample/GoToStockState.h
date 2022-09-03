#pragma once
#include "State.h"

const int SX = 30;
const int SY = 30;

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

