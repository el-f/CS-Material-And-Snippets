#include "GLUT.h"

#include <ctime>
#include <vector>
#include "Cell.h"
#include <iostream>
#include "Node.h"
#include <queue>
#include "CompareNodes.h"

using namespace std;

const int B_SIZE = 100;

const int NUM_NODES = 600;
const int NUM_EDGES = 1100;

Node nodes[NUM_NODES];
Edge edges[NUM_EDGES];

bool uc_is_running = false;

priority_queue<Node *, vector<Node *>, CompareNodes> pq;

void InitGraph();

void init() {
    srand(time(nullptr)); // seed random numbers
    glClearColor(1, 1, 1, 0); // RGB - sets background color
    glOrtho(0, B_SIZE, 0, B_SIZE, -1, 1); // setup coordinate system
    InitGraph();
}

double Distance(int index1, int index2) {
    double x1, y1, x2, y2;

    x1 = nodes[index1].getX();
    y1 = nodes[index1].getY();
    x2 = nodes[index2].getX();
    y2 = nodes[index2].getY();

    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void InitGraph() {
    int i, n1, n2;
    double x, y, distance;

    // set random Nodes
    for (i = 0; i < NUM_NODES; i++) {
        x = rand() % B_SIZE;
        y = rand() % B_SIZE;
        nodes[i].setX(x);
        nodes[i].setY(y);
        nodes[i].setIndex(i);
    }

    // set random Edges
    for (i = 0; i < NUM_EDGES; i++) {
        do {
            n1 = rand() % NUM_NODES;
            n2 = rand() % NUM_NODES;
            distance = Distance(n1, n2);
        } while (distance > 11);

        edges[i].setFirstIndex(n1);
        edges[i].setSecondIndex(n2);
        edges[i].setCost(distance);
        nodes[n1].AddEdge(edges[i]);
        nodes[n2].AddEdge(edges[i]);
    }

    // init pq
    nodes[0].setColor(START);
    nodes[0].setG(0);
    pq.push(&nodes[0]);

    nodes[1].setColor(WHITE_TARGET);

}

void RestorePathInGraph(Node *pn) {
    pn = pn->getParent();
    while (pn->getParent() != nullptr) {
        pn->setColor(PATH);
        pn = pn->getParent();
    }
}

void UpdatePQ(Node *pCurrent, int neighbor_index, double cost) {
    Node *pn;
    vector<Node *> tempQ;
    while (!pq.empty() && pq.top()->getIndex() != neighbor_index) {
        tempQ.push_back(pq.top());
        pq.pop();
    }
    // Now either pq is empty or pq.top is what we are looking for
    if (pq.empty()) {
        cout << "A gray Node wasn't found in PQ\n";
        exit(1);
    }
    // the neighbor was found
    pn = pq.top();
    pq.pop();
    pn->setG(pCurrent->getG() + cost); // update G
    pn->setParent(pCurrent); // update parent
    pq.push(pn);
    while (!tempQ.empty()) {
        pq.push(tempQ.back());
        tempQ.pop_back();
    }
}

void CheckNeighborInGraph(Node *pCurrent, int neighbor_index, double cost) {
    switch (nodes[neighbor_index].getColor()) {
        case WHITE:
            nodes[neighbor_index].setColor(GRAY);
            nodes[neighbor_index].setParent(pCurrent);
            nodes[neighbor_index].setG(pCurrent->getG() + cost);
            pq.push(&nodes[neighbor_index]);
            break;
        case GRAY:
        case GRAY_TARGET:
            if (nodes[neighbor_index].getG() > pCurrent->getG() + cost)
                UpdatePQ(pCurrent, neighbor_index, cost);
            break;
        case WHITE_TARGET:
            nodes[neighbor_index].setColor(GRAY_TARGET);
            nodes[neighbor_index].setParent(pCurrent);
            nodes[neighbor_index].setG(pCurrent->getG() + cost);
            pq.push(&nodes[neighbor_index]);
            break;
    }
}

// The algorithm is based on 
void UCIteration() {
    Node *pCurrent;
    int neighbor_index;

    if (pq.empty()) {
        cout << "There is no solution\n";
        uc_is_running = false;
    } else // pq is not empty
    {
        pCurrent = pq.top(); // pq.top is the "best" (defined in CompareNodes: G) Node

        if (pCurrent->getColor() == GRAY_TARGET) {
            cout << "The solution has been found\n";
            uc_is_running = false;
            RestorePathInGraph(pCurrent);
            return;
        }

        pq.pop();
        if (pCurrent->getColor() == GRAY)
            pCurrent->setColor(BLACK);
        // scan all the neighbors and pick non-Black and non-start
        for (auto it: pCurrent->GetOutgoing()) // it is iterator on (outgoing) edges
        {
            if (it.getFirstIndex() == pCurrent->getIndex())
                neighbor_index = it.getSecondIndex();
            else
                neighbor_index = it.getFirstIndex();

            if (nodes[neighbor_index].getColor() != BLACK && nodes[neighbor_index].getColor() != START)
                CheckNeighborInGraph(pCurrent, neighbor_index, it.getCost());
        }

    }
}

void DrawGraph() {
    int i;
    double x1, y1, x2, y2;

    // first draw edges
    for (i = 0; i < NUM_EDGES; i++) {
        x1 = nodes[edges[i].getFirstIndex()].getX();
        y1 = nodes[edges[i].getFirstIndex()].getY();
        x2 = nodes[edges[i].getSecondIndex()].getX();
        y2 = nodes[edges[i].getSecondIndex()].getY();
        edges[i].DrawMe(x1, y1, x2, y2);
    }

    // second draw nodes
    for (i = 0; i < NUM_NODES; i++)
        nodes[i].DrawMe();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // fills all the frame buffer with background color

    DrawGraph();
    glutSwapBuffers();// show what was drawn in "frame buffer"
}

void idle() {
    if (uc_is_running)
        UCIteration();

    glutPostRedisplay(); // calls indirectly to display
}

void reset() {
    // clear pq
    priority_queue<Node *, vector<Node *>, CompareNodes> empty;
    swap(pq, empty);

    // clear arrays
    fill_n(nodes, NUM_NODES, Node());
    fill(begin(edges), end(edges), Edge());

    InitGraph();
}

void menu(int choice) {
    switch (choice) {
        case 1: // Uniform Cost
            uc_is_running = true;
            break;
        case 2: // reset
            reset();
            break;
    }
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double means it uses double buffer
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(600, 100);
    glutCreateWindow("Uninformed Search");

    glutDisplayFunc(display); // refresh function
    glutIdleFunc(idle); // runs all the time in the background
// add menu
    glutCreateMenu(menu);
    glutAddMenuEntry("Run Uniform Cost", 1);
    glutAddMenuEntry("Reset", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();

    glutMainLoop();
}