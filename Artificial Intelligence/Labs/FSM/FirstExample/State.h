#pragma once
#include "Player.h"
// pure virtual class (interface)

class Player;
class State
{
public:
	State();
	~State();

	virtual void MakeTransition(Player* owner) = 0;
	virtual void OnStateEnter(Player* owner) = 0;
	virtual void OnStateExit(Player* owner) = 0;
};

