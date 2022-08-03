#include "GLUT.h"

#include <ctime>
#include <queue>
#include <iostream>
#include <set>
#include <map>

/*
    Authors:
        Elazar Fine
        Maor Ofek
    Base By:
        Victor Taubkin
*/

using namespace std;

const int WALL = 0;
const int SPACE = 1;
const int START = 2;
const int TARGET = 3;
const int FRONTIER_FORWARD = 4;
const int FRONTIER_BACKWARD = 5;
const int VISITED_FORWARD = 6;
const int VISITED_BACKWARD = 7;
const int PATH = 8;

const int MAZE_H = 100, MAZE_W = 100; // maze size
int maze[MAZE_H][MAZE_W] = {0};

bool bfs_is_running = false;

typedef pair<int, int> cell;

queue<cell *> grays_forward;
queue<cell *> grays_backward;

set <cell> directions = {
        make_pair(0, 1),
        make_pair(0, -1),
        make_pair(1, 0),
        make_pair(-1, 0)
};

struct cell_comparer {
    bool operator()(cell *a, cell *b) const {
        return *a < *b;
    }
};

map<cell *, cell *, cell_comparer> parent;

set<int> forward_valid_moves = {SPACE, TARGET, FRONTIER_BACKWARD};
set<int> backward_valid_moves = {SPACE, START, FRONTIER_FORWARD};

void InitMaze();

void clear(std::queue<cell *> &q) {
    std::queue<cell *>().swap(q);
}

void clear(std::map<cell *, cell *, cell_comparer> &m) {
    std::map<cell *, cell *, cell_comparer>().swap(m);
}

void init() {
    srand(time(nullptr)); // seed random numbers
    glClearColor(0, 0, 0.2, 0); // RGB - sets background color
    glOrtho(0, MAZE_W, 0, MAZE_H, -1, 1); // setup coordinate system
    InitMaze();
}

void InitMaze() {
    int y, x;

    // the border is WALL by default
    for (y = 1; y < MAZE_H - 1; y++)
        for (x = 1; x < MAZE_W - 1; x++) {
            if (y % 2 == 1) { // more SPACES
                if (rand() % 100 < 85)
                    maze[y][x] = SPACE;
                else
                    maze[y][x] = WALL;
            } else { // y is even: more walls
                if (rand() % 100 < 70)
                    maze[y][x] = WALL;
                else
                    maze[y][x] = SPACE;
            }
        }
    auto S = new cell(MAZE_H / 2, MAZE_W / 2);
    grays_forward.push(S);
    maze[MAZE_H / 2][MAZE_W / 2] = START;

    auto E = new cell(rand() % (MAZE_H - 1), rand() % (MAZE_W - 1));
    grays_backward.push(E);
    maze[E->first][E->second] = TARGET;
}


void DrawMaze() {
    int y, x;

    for (y = 0; y < MAZE_H; y++)
        for (x = 0; x < MAZE_W; x++) {
            // set color
            switch (maze[y][x]) {
                case WALL:
                    glColor3d(0, 0, 0);// black
                    break;
                case SPACE:
                    glColor3d(1, 1, 1); // white
                    break;
                case START:
                    glColor3d(0.5, 0.7, 1);// light blue
                    break;
                case TARGET:
                    glColor3d(0.9, 0.1, 0.1); // red
                    break;
                case FRONTIER_FORWARD:
                    glColor3d(0.5, 0.5, 1); // dark blue
                    break;
                case FRONTIER_BACKWARD:
                    glColor3d(1, 0.5, 0.5); // dark red
                    break;
                case VISITED_FORWARD:
                    glColor3d(0.7, 0.7, 1); // light blue
                    break;
                case VISITED_BACKWARD:
                    glColor3d(1, 0.7, 0.7); // light red
                    break;
                case PATH:
                    glColor3d(0.7, 0, 0.7); // magenta
                    break;
            }
            glBegin(GL_POLYGON);
            glVertex2d(x, y);
            glVertex2d(x, y + 1);
            glVertex2d(x + 1, y + 1);
            glVertex2d(x + 1, y);
            glEnd();
        }
}

void RestorePath(cell *c) {
    while (parent.find(c) != parent.end()) { // while cell has parent
        maze[c->first][c->second] = PATH;
        c = parent[c];
    }
    maze[c->first][c->second] = PATH; // start point is also a path but has no parent
}

void CheckNeighbor(int row, int col, cell *current, bool is_forward) {
    if (!bfs_is_running) return;
    if ((is_forward && (maze[row][col] == FRONTIER_BACKWARD || maze[row][col] == TARGET)) ||
        (!is_forward && (maze[row][col] == FRONTIER_FORWARD || maze[row][col] == START))) {
        cout << "The solution has been found\n";
        bfs_is_running = false;
        RestorePath(current);
        RestorePath(new cell(row, col));
    } else {
        auto neighbour = new cell(row, col);
        if (is_forward) {
            grays_forward.push(neighbour);
            maze[row][col] = FRONTIER_FORWARD;
        } else {
            grays_backward.push(neighbour);
            maze[row][col] = FRONTIER_BACKWARD;
        }
        parent[neighbour] = current;  // add current as parent
    }
}

void BfsIteration(bool is_forward) {
    if (grays_forward.empty() || grays_backward.empty()) {
        cout << "There is no path between the start and the target\n";
        bfs_is_running = false;
        return;
    }

    cell *frontier;
    if (is_forward) {
        frontier = grays_forward.front();
        grays_forward.pop();
    } else {
        frontier = grays_backward.front();
        grays_backward.pop();
    }

    int r = frontier->first, c = frontier->second;
    maze[r][c] = is_forward ? VISITED_FORWARD : VISITED_BACKWARD;

    auto valid_moves = is_forward ? forward_valid_moves : backward_valid_moves;
    for (auto &dir: directions) {
        if (valid_moves.find(maze[r + dir.first][c + dir.second]) != valid_moves.end()) {
            CheckNeighbor(r + dir.first, c + dir.second, frontier, is_forward);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // fills all the frame buffer with background color

    DrawMaze();
    glutSwapBuffers();// show what was drawn in "frame buffer"
}

void idle() {
    if (bfs_is_running) BfsIteration(true);
    if (bfs_is_running) BfsIteration(false);

    glutPostRedisplay(); // calls indirectly to display
}

void reset() {
    clear(grays_forward);
    clear(grays_backward);
    clear(parent);
    InitMaze();
    bfs_is_running = false;
}

void menu(int choice) {
    switch (choice) {
        case 1: // run bfs
            bfs_is_running = true;
            break;
        case 2: // reset
            reset();
            break;
        case 3: // exit
            exit(0);
        default:
            break;
    }
}

void keyPressed(unsigned char key, int x, int y) {
    switch (key) {
        case ' ': // play / pause
            bfs_is_running ^= true;
            break;
        case 'r': // reset
            reset();
            break;
        default:
            break;
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double means it uses double buffer
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(600, 100);
    glutCreateWindow("Path Finder");

    glutDisplayFunc(display); // refresh function
    glutIdleFunc(idle); // runs all the time in the background

    glutCreateMenu(menu); // add menu
    glutAddMenuEntry("Run BFS", 1);
    glutAddMenuEntry("Reset", 2);
    glutAddMenuEntry("Exit Program", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutKeyboardFunc(keyPressed); // add keyboard shortcuts

    init();

    glutMainLoop();
}