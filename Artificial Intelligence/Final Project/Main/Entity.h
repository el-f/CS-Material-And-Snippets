#pragma once

#include "util.h"

class State;

class Entity {
private:
    State *currentState;
    bool isChasing = false;
    bool isOnGoldCoin = false;
public:
    int r, c; // current position
    State *getCurrentState() { return currentState; }

    void setCurrentState(State *pNewState) { currentState = pNewState; }

    void move(int new_r, int new_c, int _board[][BOARD_W]);

    Entity(int y, int x, State *state);

    bool getIsChasing() const { return isChasing; }

    void setIsChasing(bool value) { isChasing = value; }

    bool getIsOnGoldCoin() const { return isOnGoldCoin; }

    void setIsOnGoldCoin(bool value) { isOnGoldCoin = value; }

    void nextState();
};

