#include "ChoppingState.h"
#include "GoToStockState.h"



ChoppingState::ChoppingState()
{
}


ChoppingState::~ChoppingState()
{
}

void ChoppingState::MakeTransition(Player * owner)
{
	owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false
	owner->setCurrentState(new GoToStockState());
	owner->getCurrentState()->OnStateEnter(owner); //  set the relevant info 
}

void ChoppingState::OnStateEnter(Player * owner)
{
	owner->setIsGettingWood(true);
	owner->setIsMoving(false);
}

void ChoppingState::OnStateExit(Player * owner)
{
	owner->setIsGettingWood(false);

}
