#include "Player.h"
#include "GoToForestState.h"
#include "GLUT.H"
#include <math.h>



Player::Player()
{
	x = rand() % MSZ;
	y = rand() % MSZ;
	isMoving = false;
	isGettingWood = false;
	isDroppingWood = false;
	numWoods = 0;
	currentState = new GoToForestState();
	currentState->OnStateEnter(this);
}


Player::~Player()
{
}

void Player::DrawMe()
{
	glColor3d(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.5, y);
	glVertex2d(x , y+1);
	glVertex2d(x + 0.5, y);
	glVertex2d(x , y- 1);
	glEnd();

	glColor3d(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(x - 0.5, y);
	glVertex2d(x, y + 1);
	glVertex2d(x + 0.5, y);
	glVertex2d(x, y - 1);
	glEnd();

	glColor3d(0.8, 0.4, 0);
	//wood
	glBegin(GL_POLYGON);
	glVertex2d(x - 0.5, y-1+numWoods/MAX_WOODS);
	glVertex2d(x - 0.5, y - 1);
	glVertex2d(x - 1.5, y - 1);
	glVertex2d(x - 1.5, y - 1 + numWoods / MAX_WOODS);
	glEnd();
	// cart
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex2d(x - 0.5, y);
	glVertex2d(x - 0.5, y - 1);
	glVertex2d(x - 1.5, y - 1);
	glVertex2d(x - 1.5, y);
	glEnd();

}

void Player::Execute()
{
	double dist;
	// if the flag isMoving true then move player
	if (isMoving)
	{
		x += dx * SPEED;
		y += dy * SPEED;
		dist = sqrt(pow(tx - x, 2) + pow(ty - y, 2));
		if (dist < rand() % 7)
			currentState->MakeTransition(this);
	}
	else if (isGettingWood)
	{
		numWoods += 1;
		if(numWoods>=MAX_WOODS)
			currentState->MakeTransition(this);
	}
	else if (isDroppingWood)
	{
		numWoods -= 1;
		if (numWoods <= 0)
			currentState->MakeTransition(this);

	}
}

void Player::setDirection(int targetX, int targetY)
{
	tx = targetX + ((rand() % 10) * (rand() % 2 ? 1 : -1));
	ty = targetY;
	double dist = sqrt(pow(tx - x, 2) + pow(ty - y, 2));
	dx = (tx - x) / dist;
	dy = (ty - y) / dist;
}
