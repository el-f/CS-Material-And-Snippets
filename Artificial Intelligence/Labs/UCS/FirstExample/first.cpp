#include "GLUT.h"

#include <time.h>
#include <vector>
#include "Cell.h"
#include <iostream>
#include "Node.h"
#include <queue>
#include "CompareNodes.h"

using namespace std;


const int MSZ = 100; // maze size

const int NUM_NODES = 600;
const int NUM_EDGES = 1100;

Node nodes[NUM_NODES];
Edge edges[NUM_EDGES];


int maze[MSZ][MSZ] = {0};
bool bfs_is_running = false;
bool dfs_is_running = false;
bool uc_is_running = false;
// defines queue of Cells
vector<Cell*> grays;

priority_queue < Node*, vector<Node*>, CompareNodes> pq;

void InitMaze();
void InitGraph();

void init()
{
	srand(time(0)); // seed random numbers
	glClearColor(1, 1, 1, 0); // RGB - sets background color
	glOrtho(0, MSZ, 0, MSZ, -1, 1); // setup coordinate system
//	InitMaze();
	InitGraph();
}

double Distance(int index1, int index2)
{
	double x1, y1, x2, y2;

	x1 = nodes[index1].getX();
	y1 = nodes[index1].getY();
	x2 = nodes[index2].getX();
	y2 = nodes[index2].getY();

	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

void InitGraph()
{
	int i,n1,n2;
	double x, y,distance;

	// set random Nodes
	for (i = 0; i < NUM_NODES; i++)
	{
		x = rand() % MSZ;
		y = rand() % MSZ;
		nodes[i].setX(x);
		nodes[i].setY(y);
		nodes[i].setIndex(i);
	}

	// set random Edges
	for (i = 0; i < NUM_EDGES;i++)
	{
		do
		{
			n1 = rand() % NUM_NODES;
			n2 = rand() % NUM_NODES;
			distance = Distance(n1, n2);
		} while (distance>11);

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

void InitMaze()
{
	int i, j;

	// the border is WALL by default 

	for(i=1;i<MSZ-1;i++)
		for (j = 1; j < MSZ - 1; j++)
		{
			if (i % 2 == 1) // more SPACES
			{
				if (rand() % 100 < 85)
					maze[i][j] = SPACE;
				else
					maze[i][j] = WALL;
			}
			else // i is even: more walls
			{
				if (rand() % 100 < 70)
					maze[i][j] = WALL;
				else
					maze[i][j] = SPACE;
			}
		}
	maze[MSZ / 2][MSZ / 2] = START;
	// add Start Point to grays
	Cell* pc = new Cell(MSZ / 2, MSZ / 2);
	grays.push_back(pc);

	maze[rand() % MSZ][rand() % MSZ] = TARGET;

}




void DrawMaze()
{
	int i, j;

	for(i=0;i<MSZ;i++)
		for (j = 0; j < MSZ; j++)
		{
			// set color
			switch (maze[i][j])
			{
			case WALL:
				glColor3d(0.3, 0, 0);// dark red
				break;
			case SPACE:
				glColor3d(1, 1, 1); // white
				break;
			case START:
				glColor3d(0.5, 0.7, 1);// light blue
				break;
			case TARGET:
				glColor3d(1, 0, 0); // red
				break;
			case GRAY:
				glColor3d(0, 0.5, 0); // dark green
				break;
			case BLACK:
				glColor3d(0.7, 1, 0.7); // light green
				break;
			case PATH:
				glColor3d(0.7, 0, 0.7); // magenta
				break;
			}
			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j, i+1);
			glVertex2d(j+1, i+1);
			glVertex2d(j+1, i);
			glEnd();
		}
}

void RestorePath(Cell* pc)
{
	while (pc != nullptr)
	{
		maze[pc->getRow()][pc->getCol()] = PATH;
		pc = pc->getParent();
	}
}

void CheckNeighbor(int row, int col, Cell* pcurrent)
{
	Cell* pneighbor;
	// is maze[row][col] a TARGET
	if (maze[row][col] == TARGET)
	{
		cout << "the solution has been found\n";
		bfs_is_running = false;
		dfs_is_running = false;
		RestorePath(pcurrent);
	}
	else // this is white neighbor
	{
		pneighbor = new Cell(row, col,pcurrent); // and pcurrent as parent
		grays.push_back(pneighbor);
		maze[row][col] = GRAY;
	}
}

void BfsIteration()
{
	Cell* pcurrent;
	int r, c;

	if (grays.empty())
	{
		cout << "There is no solution\n";
		bfs_is_running = false;
		return;
	}
	else // grays is not empty
	{
		pcurrent = *grays.begin();
		// remove pcurrent from grays and paint it black
		grays.erase(grays.begin());
		r = pcurrent->getRow();
		c = pcurrent->getCol();
		maze[r][c] = BLACK;
		// add non-visited neighbors
		// up
		if (maze[r + 1][c] == SPACE || maze[r + 1][c] == TARGET)
			CheckNeighbor(r + 1, c, pcurrent);
		// down
		if (bfs_is_running && (maze[r - 1][c] == SPACE || maze[r - 1][c] == TARGET))
			CheckNeighbor(r - 1, c, pcurrent);
			// left
		if (bfs_is_running && (maze[r ][c- 1] == SPACE || maze[r ][c- 1] == TARGET))
			CheckNeighbor(r, c - 1, pcurrent);
		// right
		if (bfs_is_running && (maze[r][c + 1] == SPACE || maze[r][c + 1] == TARGET))
			CheckNeighbor(r, c + 1, pcurrent);
	}

}

void DfsIteration()
{
	Cell* pcurrent;
	int row, col,i;

	if (grays.empty())
	{
		cout << "There is no solution\n";
		dfs_is_running = false;
		return;
	}
	else // grays is not empty
	{// pick the last element from grays
		pcurrent = grays.back();
		grays.pop_back();
		row = pcurrent->getRow();
		col = pcurrent->getCol();
		maze[row][col] = BLACK;

		// choose random direction (In DFS random direction is important)
		int direction[4] = { -1,-1,-1,-1 };
		int place;
		for (i = 0; i < 4; i++) // i stands for direction
		{
			do
			{
				place = rand() % 4;
			} while (direction[place]!=-1);
			direction[place] = i;
		}

		// pick neighbors in random order
		for (i = 0; i < 4 && dfs_is_running; i++)
		{
			switch (direction[i])
			{
			case 0:  // up
				if (maze[row + 1][col] == SPACE || maze[row + 1][col] == TARGET)
					CheckNeighbor(row + 1, col, pcurrent);
				break;
			case 1: //down
				if (maze[row - 1][col] == SPACE || maze[row - 1][col] == TARGET)
					CheckNeighbor(row - 1, col, pcurrent);
				break;
			case 2: // left 
				if (maze[row ][col - 1] == SPACE || maze[row][col - 1] == TARGET)
					CheckNeighbor(row, col - 1, pcurrent);
				break;
			case 3: // right
				if (maze[row][col + 1] == SPACE || maze[row][col + 1] == TARGET)
					CheckNeighbor(row, col + 1, pcurrent);
				break;
			}
		}
	}
}

void RestorePathInGraph(Node* pn)
{
	pn = pn->getParent();
	while (pn->getParent() != nullptr)
	{
		pn->setColor(PATH);
		pn = pn->getParent();
	}
}


void UpdatePQ(Node* pCurrent, int neighbor_index, double cost)
{
	Node* pn;
	vector<Node*> tempQ;
	while (!pq.empty() && pq.top()->getIndex() != neighbor_index)
	{
		tempQ.push_back(pq.top());
		pq.pop();
	}
	// Now either pq is empty or pq.top is what we are looking for
	if (pq.empty())
	{
		cout << "A gray Node wasn't found in PQ\n";
		exit(1);
	}
	// the neighbor was found
	pn = pq.top();
	pq.pop();
	pn->setG(pCurrent->getG() + cost); // update G
	pn->setParent(pCurrent); // update parent
	pq.push(pn);
	while (!tempQ.empty())
	{
		pq.push(tempQ.back());
		tempQ.pop_back();
	}
}

void CheckNeighborInGraph(Node* pCurrent, int neighbor_index, double cost)
{
	switch (nodes[neighbor_index].getColor())
	{
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
void UCIteration()
{
	Node* pCurrent;
	int neighbor_index;

	if (pq.empty())
	{
		cout << "There is no solution\n";
		uc_is_running = false;
	}
	else // pq is not empty
	{
		pCurrent = pq.top(); // pq.top is the "best" (defined in CompareNodes: G) Node 

		if (pCurrent->getColor() == GRAY_TARGET)
		{
			cout << "The solution has been found\n";
			uc_is_running = false;
			RestorePathInGraph(pCurrent);
			return;
		}

		pq.pop();
		if(pCurrent->getColor()==GRAY)
			pCurrent->setColor(BLACK);
		// scan all the neighbors and pick non-Black and non-start
		for (auto it : pCurrent->GetOutgoing()) // it is iterator on (outgoing) edges
		{
			if (it.getFirstIndex() == pCurrent->getIndex())
				neighbor_index = it.getSecondIndex();
			else
				neighbor_index = it.getFirstIndex();

			if (nodes[neighbor_index].getColor() != BLACK && nodes[neighbor_index].getColor() != START)
				CheckNeighborInGraph(pCurrent, neighbor_index,it.getCost());
		}

	}
}

void DrawGraph()
{
	int i;
	double x1, y1, x2, y2;

	// first draw edges
	for (i = 0; i < NUM_EDGES; i++)
	{
		x1 = nodes[edges[i].getFirstIndex()].getX();
		y1 = nodes[edges[i].getFirstIndex()].getY();
		x2 = nodes[edges[i].getSecondIndex()].getX();
		y2 = nodes[edges[i].getSecondIndex()].getY();
		edges[i].DrawMe(x1,y1,x2,y2);
	}

	// second draw nodes
	for (i = 0; i < NUM_NODES; i++)
		nodes[i].DrawMe();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // fills all the frame buffer with background color

//	DrawMaze();
	DrawGraph();
	glutSwapBuffers();// show what was drawn in "frame buffer"
}

void idle()
{
	if (bfs_is_running)
		BfsIteration();
	if (dfs_is_running)
		DfsIteration();
	if (uc_is_running)
		UCIteration();

	glutPostRedisplay(); // calls indirectly to display
}

void menu(int choice)
{
	switch (choice)
	{
	case 1: // bfs
		bfs_is_running = true;
		break;
	case 2: // dfs
		dfs_is_running = true;
		break;
	case 3: // Uniform Cost
		uc_is_running = true;
		break;
	}
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double means it uses double buffer
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("Uninformed Search");

	glutDisplayFunc(display); // refresh function
	glutIdleFunc(idle); // runs all the time in the background
// add menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Run BFS", 1);
	glutAddMenuEntry("Run DFS", 2);
	glutAddMenuEntry("Run Uniform Cost", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
}