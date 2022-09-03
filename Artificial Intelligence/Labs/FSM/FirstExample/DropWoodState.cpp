#include "DropWoodState.h"
#include "GoToForestState.h"


DropWoodState::DropWoodState()
{
}


DropWoodState::~DropWoodState()
{
}

void DropWoodState::MakeTransition(Player * owner)
{
	owner->getCurrentState()->OnStateExit(owner); // set the relevant bool flags to false
	owner->setCurrentState(new GoToForestState());
	owner->getCurrentState()->OnStateEnter(owner); //  set the relevant info

}

void DropWoodState::OnStateEnter(Player * owner)
{
	owner->setIsDroppingWood(true);
	owner->setIsMoving(false);
}

void DropWoodState::OnStateExit(Player * owner)
{
	owner->setIsDroppingWood(false);

}
