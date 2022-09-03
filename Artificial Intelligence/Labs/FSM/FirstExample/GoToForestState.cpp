#include "GoToForestState.h"
#include "ChoppingState.h"

const int FX = MSZ - 20;
const int FY = MSZ - 20;


GoToForestState::GoToForestState()
{
}


GoToForestState::~GoToForestState()
{
}

void GoToForestState::MakeTransition(Player * owner)
{
	owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false
	owner->setCurrentState(new ChoppingState());
	owner->getCurrentState()->OnStateEnter(owner); //  set the relevant info

}

void GoToForestState::OnStateEnter(Player * owner)
{
	owner->setIsMoving(true);
	owner->setDirection(FX,FY);
}

void GoToForestState::OnStateExit(Player * owner)
{
	owner->setIsMoving(false);

}
