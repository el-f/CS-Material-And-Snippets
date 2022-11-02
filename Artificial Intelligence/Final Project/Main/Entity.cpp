#include "Entity.h"
#include "EscapingState.h"

Entity::Entity(int y, int x, State *state) : r(y), c(x), currentState(state) {
    currentState->OnStateEnter(this);
}

void Entity::move(int new_r, int new_c, int _board[][BOARD_W]) {
    // sanity check
    if (abs(new_r - r) + abs(new_c - c) != 1) {
        return;
    }

    // get cell type of old position
    auto cell_type = _board[r][c];

    // old position is now empty
    if (isOnGoldCoin) {
        _board[r][c] = COIN;
        isOnGoldCoin = false;
    } else {
        _board[r][c] = SPACE;
    }

    // move to new position
    r = new_r;
    c = new_c;

    // set new position to cell type of old position
    _board[new_r][new_c] = cell_type;
}

void Entity::nextState() {
    currentState->MakeTransition(this);
}

