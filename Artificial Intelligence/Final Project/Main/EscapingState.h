#pragma once

#include "State.h"

class EscapingState : public State {

public:

    EscapingState() = default;

    ~EscapingState() = default;

    void MakeTransition(Entity *owner) override;

    void OnStateEnter(Entity *owner) override;

    void OnStateExit(Entity *owner) override;
};

