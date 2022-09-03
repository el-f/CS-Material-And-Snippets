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
const int FRONTIER = 4;
const int VISITED = 5;
const int PATH = 6;

const int MAZE_H = 100, MAZE_W = 100; // maze size
int maze[MAZE_H][MAZE_W] = {0};

set<pair<int, int>> directions = {
        make_pair(0, 1),
        make_pair(0, -1),
        make_pair(1, 0),
        make_pair(-1, 0)
};

set<int> valid_moves = {SPACE, TARGET};

bool search_is_running = false;
bool is_astar = true;

struct cell {
    int r, c, g;

    cell(int _r, int _c, int _g) : r(_r), c(_c), g(_g) {}

    cell(int _r, int _c) : r(_r), c(_c), g(0) {}
};

struct cell_ref_comparer {
    bool operator()(cell *a, cell *b) const {
        return a->r == b->r ? a->c < b->c : a->r < b->r;
    }
};

cell *E; // target cell (end)

// manhattan distance from cell to target
int manhattan_distance(cell *current) {
    return abs(current->r - E->r) + abs(current->c - E->c);
}

struct cell_cost_comparer {
    bool operator()(cell *a, cell *b) const {
        int a_h = manhattan_distance(a), b_h = manhattan_distance(b);
        return is_astar
               ? a->g + a_h > b->g + b_h // A*         - f(n) = g(n) + h(n)
               : a_h > b_h;              // Best First - f(n) = h(n)
    }
};

priority_queue<cell *, vector<cell *>, cell_cost_comparer> pq;

map<cell *, cell *, cell_ref_comparer> parent;

void clear(priority_queue<cell *, vector<cell *>, cell_cost_comparer> &q) {
    priority_queue<cell *, vector<cell *>, cell_cost_comparer>().swap(q);
}

void clear(map<cell *, cell *, cell_ref_comparer> &m) {
    map<cell *, cell *, cell_ref_comparer>().swap(m);
}

void init_maze() {
    int y, x;

    // the border is WALL by default
    for (y = 1; y < MAZE_H - 1; y++) {
        for (x = 1; x < MAZE_W - 1; x++) {
            if (y % 2 == 1) { // more SPACES
                maze[y][x] = rand() % 100 < 85 ? SPACE : WALL;
            } else { // y is even: more walls
                maze[y][x] = rand() % 100 < 70 ? WALL : SPACE;
            }
        }
    }

    auto S = new cell(MAZE_H / 2, MAZE_W / 2);
    pq.push(S);
    maze[MAZE_H / 2][MAZE_W / 2] = START;

    E = new cell(max(1, rand() % (MAZE_H - 1)), max(1, rand() % (MAZE_W - 1)));
    maze[E->r][E->c] = TARGET;
}

void init() {
    srand(time(nullptr)); // seed random numbers
    glClearColor(0, 0, 0.2, 0); // RGB - sets background color
    glOrtho(0, MAZE_W, 0, MAZE_H, -1, 1); // setup coordinate system
    init_maze();
}

void draw_maze() {
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
                case FRONTIER:
                    glColor3d(0.5, 0.5, 1); // dark blue
                    break;
                case VISITED:
                    glColor3d(0.7, 0.7, 1); // light blue
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

int restore_path(cell *c) {
    int path_len = 0;
    while (parent.find(c) != parent.end()) { // while cell has parent
        maze[c->r][c->c] = PATH;
        c = parent[c];
        path_len++;
    }
    maze[c->r][c->c] = PATH; // start point is also a path but has no parent
    return path_len;
}

void check_neighbor(int row, int col, cell *current) {
    if (!search_is_running) return;
    auto neighbour = new cell(row, col, current->g + 1);
    parent[neighbour] = current;
    if (maze[row][col] == TARGET) {
        cout << "The solution has been found (using " << (is_astar ? "A*" : "Best First") << " search)" << endl;
        search_is_running = false;
        int path_len = restore_path(neighbour);
        cout << "Path length: " << path_len << endl;
    } else {
        pq.push(neighbour);
        maze[row][col] = FRONTIER;
    }
}

void search_iteration() {
    if (pq.empty()) {
        cout << "There is no path between the start and the target\n";
        search_is_running = false;
        return;
    }

    cell* frontier = pq.top();
    pq.pop();

    int r = frontier->r, c = frontier->c;
    maze[r][c] = VISITED;

    for (auto &dir: directions) {
        if (valid_moves.find(maze[r + dir.first][c + dir.second]) != valid_moves.end()) {
            check_neighbor(r + dir.first, c + dir.second, frontier);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // fills all the frame buffer with background color

    draw_maze();
    glutSwapBuffers();// show what was drawn in "frame buffer"
}

void idle() {
    if (search_is_running) search_iteration();

    glutPostRedisplay(); // calls indirectly to display
}

void reset(boolean use_old_setup = false) {
    clear(pq);
    clear(parent);
    if (!use_old_setup) init_maze();
    else {
        maze[E->r][E->c] = TARGET;
        auto S = new cell(MAZE_H / 2, MAZE_W / 2);
        pq.push(S);
        maze[MAZE_H / 2][MAZE_W / 2] = START;

        // change all path cells to spaces
        for (auto &row: maze)
            for (int &cell: row)
                if (cell == PATH || cell == FRONTIER || cell == VISITED)
                    cell = SPACE;
    }
    search_is_running = false;
}

void menu(int choice) {
    switch (choice) {
        case 1: // run A*
            search_is_running = true;
            is_astar = true;
            break;
        case 2: // run Best First Search
            search_is_running = true;
            is_astar = false;
            break;
        case 3: // reset (new maze)
            reset();
            break;
        case 4: // reset (same maze)
            reset(true);
            break;
        case 5: // exit
            exit(0);
        default:
            break;
    }
}

void key_pressed(unsigned char key, int x, int y) {
    switch (key) {
        case ' ': // play / pause
            search_is_running ^= true;
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
    glutAddMenuEntry("Run A*", 1);
    glutAddMenuEntry("Run Best First Search", 2);
    glutAddMenuEntry("Reset (new maze)", 3);
    glutAddMenuEntry("Reset (same maze)", 4);
    glutAddMenuEntry("Exit Program", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutKeyboardFunc(key_pressed); // add keyboard shortcuts

    init();

    glutMainLoop();
}