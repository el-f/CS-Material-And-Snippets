#include "GoToStockState.h"
#include "DropWoodState.h"



GoToStockState::GoToStockState()
{
}


GoToStockState::~GoToStockState()
{
}

void GoToStockState::MakeTransition(Player *owner)
{
	owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false
	owner->setCurrentState(new DropWoodState());
	owner->getCurrentState()->OnStateEnter(owner); //  set the relevant info

}

void GoToStockState::OnStateEnter(Player * owner)
{
	owner->setIsMoving(true);
	owner->setDirection(SX, SY);
}

void GoToStockState::OnStateExit(Player * owner)
{
	owner->setIsMoving(false);

}
