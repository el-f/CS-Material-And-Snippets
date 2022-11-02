#include "EscapingState.h"
#include "ChasingState.h"


void EscapingState::MakeTransition(Entity *owner) {
    owner->getCurrentState()->OnStateExit(owner);
    owner->setCurrentState(new ChasingState());
    owner->getCurrentState()->OnStateEnter(owner);
}

void EscapingState::OnStateEnter(Entity *owner) {
    owner->setIsChasing(false);
}

void EscapingState::OnStateExit(Entity *owner) {
    owner->setIsChasing(true);
}