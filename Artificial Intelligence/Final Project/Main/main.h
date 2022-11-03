#pragma once

#include <vector>
#include "util.h"
#include "Entity.h"


/*
 * instead of running the path finding algorithm with reverse sorted priority queue to escape,
 * we can just run it normally to find the shortest path and then just go the opposite direction.
 * this has a HUGE performance boost, and both the ghosts AND pacman are able to win using it :)
 */
#define USE_SMART_ESCAPE 1;

constexpr unsigned int RESET_ITERATIONS = 50;
unsigned int random_reset_iterations = -1;

using namespace std;

int board[BOARD_H][BOARD_W]{};

bool is_running = false;
bool game_over = false;

Entity *pacman;
vector<Entity *> ghosts;
vector<cell> rooms;

unsigned int gold_coins = 0;
unsigned long iterations = 1;

struct cell_ref_comparer {
    bool operator()(const cell &a, const cell& b) const {
        return a.r == b.r ? a.c < b.c : a.r < b.r;
    }
};

int manhattan_distance(const cell& current, cell* target) {
    return abs(current.r - target->r) + abs(current.c - target->c);
}
