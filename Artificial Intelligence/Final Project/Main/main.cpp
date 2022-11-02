#pragma warning(disable : 6386)
#include "GLUT.h"
#include "main.h"
#include "Entity.h"
#include "EscapingState.h"
#include "ChasingState.h"

#include <ctime>
#include <queue>
#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>

/*
    Authors:
        Elazar Fine
        Maor Ofek
*/

cell put_random_sized_room_at_random_location(int room_idx, int num_of_rooms) {
    int per_row = (int) sqrt(num_of_rooms);
    int room_size_x = 10 + rand() % 10;
    int room_size_y = 10 + rand() % 10;
    int room_x =
            ((BOARD_W - 1) / per_row) * (room_idx % per_row) + rand() % max(1, ((BOARD_W - 1) / per_row - room_size_x));
    int room_y =
            (((BOARD_H - 1) / per_row) * min(BOARD_H - 1 - (rand() % BOARD_H / (room_idx + 1)), room_idx / per_row) +
             rand() % max(1, ((BOARD_H - 1) / per_row - room_size_y))) % (BOARD_H - 1);

    for (int i = room_y; i < min(BOARD_H, room_y + room_size_y); i++) {
        for (int j = room_x; j < min(BOARD_W, room_x + room_size_x); j++) {
            board[i][j] = SPACE;
        }
    }

    // return y, x coordinates of center of placed room
    return {room_y + room_size_y / 2, room_x + room_size_x / 2};
}

// search function able to do both A* and Dijkstra (BFS if all weights are 1)
cell search(
        cell &start,                    // reference to start cell (because we always have a start cell)
        cell *target,                   // pointer to target cell (because we might not have a target cell)
        bool paint_path,                // whether to paint the path on the board (for room connections)
        bool is_chasing = true,         // whether to chase the target or escape from it ('stupid' escape)
        CellType target_type = NONE,    // what type of cell to chase/escape from in case we don't have a target cell
        bool is_entity = false          // whether searching for room building or for pacman/ghost
) {
    map<cell, cell, cell_ref_comparer> parent;
    map<cell, int, cell_ref_comparer> visited;

    auto E = target;

    auto cell_comparer = [&](const cell &a, const cell &b) {
        /*
         * Here is the choice of if we are using A* or Dijkstra (in our case technically BFS).
         * If we don't know the target, we use Dijkstra.
         * If we do know the target, we use A*.
         * By setting the heuristic to 0, we get Dijkstra.
         * A*       : f(n) = g(n) + h(n)
         * Dijkstra : f(n) = g(n)
         */
        int a_heuristic = E == nullptr ? 0 : manhattan_distance(a, E);
        int b_heuristic = E == nullptr ? 0 : manhattan_distance(b, E);
        return is_chasing ? visited[a] + a_heuristic > visited[b] + b_heuristic
                          : visited[a] + a_heuristic < visited[b] + b_heuristic;
    };

    priority_queue<cell, vector<cell>, decltype(cell_comparer)> frontier(cell_comparer);

    frontier.push(start);
    visited[start] = 0;

    bool found_path = false;

    cell current = cell(start.r, start.c);

    while (!frontier.empty()) {
        current = cell(frontier.top().r, frontier.top().c);
        frontier.pop();

        if ((target != nullptr && current.r == target->r && current.c == target->c) ||
            board[current.r][current.c] == target_type) {
            found_path = true;
            break;
        }

        for (auto &direction: DIRECTIONS) {
            int new_r = current.r + direction.first;
            int new_c = current.c + direction.second;

            // Don't go out of bounds
            if (new_r < 0 || new_r >= BOARD_H - 1 || new_c < 0 || new_c >= BOARD_W - 1) {
                continue;
            }

            // If it's an entity searching:
            if (is_entity && (
                    board[new_r][new_c] == WALL ||                    // Don't go through walls
                    board[new_r][new_c] == board[start.r][start.c])   // Ghosts can't go through each other
                    ) {
                continue;
            }

            int new_cost = visited[current] + (board[new_r][new_c] == WALL ? 2 : 1);

            auto neighbor = cell(new_r, new_c);

            if (visited.find(neighbor) == visited.end() || new_cost < visited[neighbor]) {
                visited[neighbor] = new_cost;
                parent[neighbor] = current;
                frontier.push(neighbor);
            }
        }
    }

    cell last_parent = parent[current];

    if (found_path) {
        // reconstruct path
        while (current.r != start.r || current.c != start.c) {
            if (paint_path) {
                board[current.r][current.c] = SPACE;

                // if in a tunnel ( walls on both sides (L+R / U+D) have a chance of putting a coin there
                if ((board[current.r][current.c - 1] == WALL && board[current.r][current.c + 1] == WALL ||
                     board[current.r - 1][current.c] == WALL && board[current.r + 1][current.c] == WALL) &&
                    rand() % 5 == 0
                        ) {
                    board[current.r][current.c] = COIN;
                    gold_coins++;
                }
            }

            last_parent = current;
            current = parent[current];
        }
    }

    // return y, x coordinates of next step in path
    return {last_parent.r, last_parent.c};
}

cell get_cell_in_opposite_direction(cell &current, cell &next_move_to_target) {
    // if we get a direction to a target that we want to run away from, we have 3 other directions to choose from
    // we choose the one that is the furthest from the target so our order of preference is:
    // 1. go in the opposite direction of the target
    // 2. go to either of the sides
    // we choose the first one that is not a wall or a ghost, if there is no such direction, we have no choice but to go
    // to the target
    int dr = next_move_to_target.r - current.r;
    int dc = next_move_to_target.c - current.c;
    cell opposite_direction = cell(current.r - dr, current.c - dc);
    if (board[opposite_direction.r][opposite_direction.c] != WALL &&
        board[opposite_direction.r][opposite_direction.c] != GHOST) {
        return opposite_direction;
    }

    for (auto &direction: DIRECTIONS) {
        if (direction.first == -dr && direction.second == -dc) {
            continue;
        }
        cell side_direction = cell(current.r + direction.first, current.c + direction.second);
        if (board[side_direction.r][side_direction.c] != WALL &&
            board[side_direction.r][side_direction.c] != GHOST) {
            return {side_direction.r, side_direction.c};
        }
    }

    return next_move_to_target;
}

void connect_rooms() {
    for (int i = 0; i < rooms.size(); i++) {
        cout << "making connections for room #" << i + 1 << endl;
        for (int j = 0; j < rooms.size(); j++) {
            if (i == j) {
                continue;
            }
            search(rooms[i], &rooms[j], true);
        }
    }
}

void init_pacman() {
    int y, x;

    for (y = 1; y < BOARD_H - 1; y++) {
        for (x = 1; x < BOARD_W - 1; x++) {
            board[y][x] = WALL;
        }
    }

    // place rooms randomly and save their centers
    int num_rooms = rand() % 2 + 9;
    for (int i = 0; i < num_rooms; i++) {
        rooms.push_back(put_random_sized_room_at_random_location(i, num_rooms));
    }

    // connect rooms using A* search
    connect_rooms();

    // init entities with their starting positions and states
    board[rooms[0].r][rooms[0].c] = PACMAN;
    pacman = new Entity(rooms[0].r, rooms[0].c, new EscapingState());

    for (int i = 1; i <= 3; i++) {
        int ghost_i_room_idx = 2 * i + rand() % 2;
        board[rooms[ghost_i_room_idx].r][rooms[ghost_i_room_idx].c] = GHOST;
        ghosts.push_back(new Entity(rooms[ghost_i_room_idx].r, rooms[ghost_i_room_idx].c, new ChasingState()));
    }

}

void init() {
    cout << "|------------------------------------|" << endl;
    cout << "|          Welcome to Pacman!        |" << endl;
    cout << "|------------------------------------|" << endl;
    cout << "| made by: Elazar Fine and Maor Ofek |" << endl;
    cout << "|____________________________________|" << endl << endl;

    srand(time(nullptr)); // seed random numbers
    glClearColor(0, 0, 0.2, 0); // RGB - sets background color
    glOrtho(0, BOARD_W, 0, BOARD_H, -1, 1); // setup coordinate system
    cout << "Initializing pacman..." << endl;
    init_pacman();
    cout << "Pacman initialized!" << endl << endl;
}

void handle_pacman_eating_gold_coin() {
    // if pacman ate all the gold coins, he wins
    if (--gold_coins == 0) {
        cout << "Pacman ate all the gold coins! Pacman wins!" << endl;
        game_over = true;
    }
}

void handle_pacman_ghost_collision() {
    if (game_over) return;

    // check if pacman and ghost are in the same cell
    // if they are check which one is in a state of escaping
    // if pacman is in a state of escaping, pacman loses and the game ends
    // if ghost is in a state of escaping, the ghost disappears and the game continues
    // if all ghosts get eaten pacman wins and the game ends
    for (auto &ghost: ghosts) {
        if (pacman->r == ghost->r && pacman->c == ghost->c) {
            if (pacman->getIsChasing()) {
                cout << "Pacman ate a ghost" << endl;

                board[pacman->r][pacman->c] = PACMAN;

                // remove ghost from board
                ghosts.erase(remove(ghosts.begin(), ghosts.end(), ghost), ghosts.end());

                // if all ghosts are eaten pacman wins
                if (ghosts.empty()) {
                    cout << "All ghosts are gone, Pacman wins!" << endl;
                    game_over = true;
                }
            } else {
                cout << "Pacman was eaten by a ghost!" << endl;
                cout << "Game over!" << endl;
                game_over = true;
            }
            break;
        }
    }
}

void do_pacman_iteration() {
    auto pacman_location = cell(pacman->r, pacman->c);

    // get next move for pacman depending on his state
    cell pacman_next_move = search(
            pacman_location, // current pacman location
            nullptr,                        // pacman never knows where the ghosts are
            false,                          // don't paint path
#ifdef USE_SMART_ESCAPE
            true,                        	// use smart escape
#else
            pacman->getIsChasing(),         // is chasing the ghosts
#endif
            GHOST,                          // target type is a ghost
            true
    );

#ifdef USE_SMART_ESCAPE
    if (!pacman->getIsChasing()) {
        pacman_next_move = get_cell_in_opposite_direction(pacman_location, pacman_next_move);
    }
#endif

    // if next cell is a gold coin, pacman eats it
    if (board[pacman_next_move.r][pacman_next_move.c] == COIN) {
        handle_pacman_eating_gold_coin();
    }

    pacman->move(pacman_next_move.r, pacman_next_move.c, board);

    // check if pacman and ghost are in the same cell
    handle_pacman_ghost_collision();

    if (game_over) return;

    // now ghosts move
    for (const auto &ghost: ghosts) {
        auto ghost_location = cell(ghost->r, ghost->c);

        // get next move for ghost depending on his state
        cell ghost_next_move = search(
                ghost_location,                 // current ghost location
                new cell(pacman->r, pacman->c), // ghost knows where pacman is
                false,                          // don't paint path
#ifdef USE_SMART_ESCAPE
				true,                        	// use smart escape
#else
				pacman->getIsChasing(),         // is chasing the ghosts
#endif
                PACMAN,                         // target type is pacman
                true
        );

#ifdef USE_SMART_ESCAPE
        if (!ghost->getIsChasing()) {
            ghost_next_move = get_cell_in_opposite_direction(ghost_location, ghost_next_move);
        }
#endif

        // if ghosts steps on coin, remember it, so it can be restored when the ghost moves away
        if (board[ghost_next_move.r][ghost_next_move.c] == COIN) {
            ghost->setIsOnGoldCoin(true);
        }

        ghost->move(ghost_next_move.r, ghost_next_move.c, board);
    }

    // check if pacman and ghost are in the same cell
    handle_pacman_ghost_collision();

    // don't reset at set times since the game can get into a loop of pacman and ghost using the same paths over and over
    // resetting the board at random times makes the game more interesting and unpredictable, enabling both pacman and ghost to win
    if (random_reset_iterations == -1) {
        random_reset_iterations = rand() % RESET_ITERATIONS + 1;
    }

    // every random number of iterations pacman and ghosts change state
    if (iterations % random_reset_iterations == 0) {
        random_reset_iterations = rand() % RESET_ITERATIONS + 1;

        pacman->nextState();
        for (const auto &ghost: ghosts) {
            ghost->nextState();
        }
    }

    iterations++;
}

void draw_scene() {
    int y, x;

    for (y = 0; y < BOARD_H; y++)
        for (x = 0; x < BOARD_W; x++) {
            // set color
            switch (board[y][x]) {
                case WALL:
                    glColor3d(0.296875, 0, 0); // slight red
                    break;
                case SPACE:
                    glColor3d(1, 1, 1); // white
                    break;
                case PACMAN:
                    glColor3d(0.85, 0.85, 0); // yellow (slightly dark for visibility)
                    break;
                case GHOST:
                    glColor3d(1, 0.078125, 0.576);
                    break;
                case COIN:
                    glColor3d(1, 0.5, 0); // orange
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


void display() {
    glClear(GL_COLOR_BUFFER_BIT); // fills all the frame buffer with background color
    draw_scene();
    glutSwapBuffers();// show what was drawn in "frame buffer"
}


void idle() {
    if (is_running && !game_over) {
        do_pacman_iteration();
    }

    glutPostRedisplay(); // calls indirectly to display
}

void menu(int choice) {
    switch (choice) {
        case 1: // start game
            is_running = true;
            break;
        case 2: // exit
            exit(0);
        default:
            break;
    }
}

void key_pressed(unsigned char key, int x, int y) {
    switch (key) {
        case ' ': // play / pause
            is_running = !is_running;
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
    glutCreateWindow("Pacman");

    glutDisplayFunc(display); // refresh function
    glutIdleFunc(idle); // runs all the time in the background

    glutCreateMenu(menu); // add menu
    glutAddMenuEntry("Start", 1);
    glutAddMenuEntry("Exit Program", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutKeyboardFunc(key_pressed); // add keyboard shortcuts

    init();

    glutMainLoop();
}