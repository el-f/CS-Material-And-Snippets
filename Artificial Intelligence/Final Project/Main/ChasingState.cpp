#include "ChasingState.h"
#include "EscapingState.h"

void ChasingState::MakeTransition(Entity *owner) {
    owner->getCurrentState()->OnStateExit(owner);
    owner->setCurrentState(new EscapingState());
    owner->getCurrentState()->OnStateEnter(owner);
}

void ChasingState::OnStateEnter(Entity *owner) {
    owner->setIsChasing(true);
}

void ChasingState::OnStateExit(Entity *owner) {
    owner->setIsChasing(false);
}
