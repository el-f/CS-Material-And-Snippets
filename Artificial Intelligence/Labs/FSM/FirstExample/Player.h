#pragma once
#include "State.h"



class State;

const int MSZ = 100;
const double MAX_WOODS = 1000;
const double SPEED = 0.1;

class Player
{
private:
	State* currentState;
	double x, y; // current position
	double tx, ty; // target
	double numWoods;
	double dx, dy; // motion direction
	bool isMoving, isGettingWood, isDroppingWood;
	

public:
	Player();
	~Player();
	State* getCurrentState() { return currentState; }
	void setCurrentState(State* pNewState) { currentState = pNewState; }
	void DrawMe();
	void Execute();
	void setIsMoving(bool value) { isMoving = value; }
	void setIsGettingWood(bool value) { isGettingWood = value; }
	void setIsDroppingWood(bool value) { isDroppingWood = value; }
	void setDirection(int targetX, int targetY);
};

