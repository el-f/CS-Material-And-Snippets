#pragma once

#include "State.h"

class ChasingState : public State {
public:
    ChasingState() = default;

    ~ChasingState() = default;

    void MakeTransition(Entity *owner) override;

    void OnStateEnter(Entity *owner) override;

    void OnStateExit(Entity *owner) override;
};
