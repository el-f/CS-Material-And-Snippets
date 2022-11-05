#pragma once

#include <set>
#include <cmath>

using namespace std;

const int BOARD_H = 80, BOARD_W = 80; // board size

enum CellType {
    WALL,
    SPACE,
    PACMAN,
    GHOST,
    COIN,
    NONE
};

// can move up, down, left, right.
const set<pair<int, int>> DIRECTIONS = {
        make_pair(0, 1),
        make_pair(0, -1),
        make_pair(1, 0),
        make_pair(-1, 0)
};


struct cell {
    int r, c;

    cell(int _r, int _c) : r(_r), c(_c) {}

    cell() : r(-1), c(-1) {}

    bool operator==(const cell& other) const {
        return r == other.r && c == other.c;
    }
};

