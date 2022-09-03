#include "GLUT.h"

#include <time.h>
#include <vector>
#include <iostream>
#include <queue>
#include "PuzzleNode.h"
#include "ComparePuzzleNodes.h"

using namespace std;

const int W = 600;
const int H = 600;



PuzzleNode* pn = new PuzzleNode();
vector<PuzzleNode*> solution;
bool solutionIsReady = false;


void init()
{
	srand(time(0)); // seed random numbers
	glClearColor(1, 1, 1, 0); // RGB - sets background color
	glOrtho(0, BSZ, BSZ, 0, -1, 1); // setup coordinate system
}

void UpdatePQ(PuzzleNode* pNeighbor, priority_queue <PuzzleNode*, vector<PuzzleNode*>, ComparePuzzleNodes> &pq)
{
	vector <PuzzleNode*> tmp;
	PuzzleNode* p;
	p = pq.top();
	while (!pq.empty() && !((*p) == *pNeighbor))
	{
		tmp.push_back(p);
		pq.pop();
		p = pq.top();
	}
	if (pq.empty())
	{
		cout << "Error! PQ is empty in UpdatePQ\n";
		exit(1);
	}
	// p points to an element in pq that is equals pNeighbor
	pq.pop();
	pq.push(pNeighbor);
	while (!tmp.empty())
	{
		pq.push(tmp.back());
		tmp.pop_back();
	}
}

void RestorePath(PuzzleNode* pnb)
{
	while (pnb->getParent() != nullptr)
	{
		solution.push_back(pnb);
		pnb = pnb->getParent();
	}
	solutionIsReady = true;
}

bool CheckNeighbor(PuzzleNode* pCurrent, int direction, priority_queue <PuzzleNode*, vector<PuzzleNode*>, ComparePuzzleNodes> &pq,
	vector<PuzzleNode> &gray, vector<PuzzleNode> &black)
{
	PuzzleNode* pNeighbor;
	vector<PuzzleNode>::iterator itGray, itBlack;

	pNeighbor = new PuzzleNode(pCurrent, direction);

	if (pNeighbor->getH() == 0) // then it is TARGET!
	{
		cout << "The solution has been found and it took " << pNeighbor->getG() << " steps\n";
		RestorePath(pNeighbor);
		return true;
	}

	itGray = find(gray.begin(), gray.end(), *pNeighbor);
	itBlack = find(black.begin(), black.end(), *pNeighbor);


	if (itGray == gray.end() && itBlack == black.end()) // then it is WHITE
	{
		pq.push(pNeighbor);
		gray.push_back(*pNeighbor);
	}
	else if(itGray != gray.end()) // it is gray
	{
		if (pNeighbor->getF() < itGray->getF())
		{
			*itGray = *pNeighbor;
			UpdatePQ(pNeighbor, pq);

		}
	}

	return false;
}

void RunAStar()
{
	// create Priority Queue
	priority_queue <PuzzleNode*, vector<PuzzleNode*>, ComparePuzzleNodes> pq;
	// create vector Gray and Black
	vector<PuzzleNode> gray, black; // must define operator == in PuzzleNode
	vector<PuzzleNode>::iterator itGray;
	// define first PuzzleNode, push it to pq and paint it gray
	pn->setG(0);
	pn->ComputeH();
	pn->ComputeF();
	pq.push(pn);
	gray.push_back(*pn);

	PuzzleNode* pCurrent;
	bool solutionFound = false;

	while (!solutionFound)
	{
		if (pq.empty())
		{
			cout << "There is no solution (not in our case!)\n";
			return;
		}
		pCurrent = pq.top();
		if (pCurrent->getH() == 0) //1. not in our case because we could stop search erlier
		{                             // 2. if h is double don't use ==0
			cout << "The solution has been found (not in our case!)\n";
			return;
		}
		// paint pCurrent black and extract it from pq
		pq.pop();
		itGray = find(gray.begin(), gray.end(), *pCurrent); //  must define operator == in PuzzleNode
		if (itGray == gray.end()) // pCurrent wasn't found
		{
			cout << "ERROR: pCurrent wasn't found\n";
			return;
		}
		gray.erase(itGray);
		black.push_back(*pCurrent);

		// if it is possible check the neighbor
		// up
		if (pCurrent->getEmptyRow() > 0)
			solutionFound = CheckNeighbor(pCurrent, UP, pq, gray, black);
		// down
		if (!solutionFound && pCurrent->getEmptyRow() < BSZ-1)
			solutionFound = CheckNeighbor(pCurrent, DOWN, pq, gray, black);

		// left
		if (!solutionFound && pCurrent->getEmptyCol() >0 )
			solutionFound = CheckNeighbor(pCurrent, LEFT, pq, gray, black);

		// right
		if (!solutionFound && pCurrent->getEmptyCol() <BSZ-1)
			solutionFound = CheckNeighbor(pCurrent, RIGHT, pq, gray, black);
	}// while

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // fills all the frame buffer with background color
	pn->Draw();
	glutSwapBuffers();// show what was drawn in "frame buffer"
}

void idle()
{

	glutPostRedisplay(); // calls indirectly to display
}

void menu(int choice)
{
	// start A* to find the solution
	RunAStar();
}

void mouse(int button, int state, int x, int y)
{
	int row, col;

	if (!solutionIsReady && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		row = BSZ * (double)y / H;
		col = BSZ * (double)x / W;

		pn->SwapCells(row, col);
	}
	else if (solutionIsReady && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (!solution.empty())
		{
			pn = solution.back();
			solution.pop_back();
		}
	}

}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double means it uses double buffer
	glutInitWindowSize(W, H);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("Puzzle");

	glutDisplayFunc(display); // refresh function
	glutIdleFunc(idle); // runs all the time in the background
	glutMouseFunc(mouse);
// add menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Start Puzzle", 1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	init();

	glutMainLoop();
}