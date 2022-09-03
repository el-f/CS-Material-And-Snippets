#include "PuzzleNode.h"
#include "GLUT.H"



PuzzleNode::PuzzleNode(PuzzleNode * p, int dir)
{
	int i, j;

	for (i = 0; i<BSZ; i++)
		for (j = 0; j < BSZ; j++)
		{
			board[i][j] = p->board[i][j];
		}
	parent = p;
	emptyRow = p->emptyRow;
	emptyCol = p->emptyCol;

	switch (dir)
	{
	case UP:
		SwapCells(emptyRow - 1, emptyCol);
		break;
	case DOWN:
		SwapCells(emptyRow + 1, emptyCol);
		break;
	case LEFT:
		SwapCells(emptyRow, emptyCol - 1);
		break;
	case RIGHT:
		SwapCells(emptyRow, emptyCol + 1);
		break;
	}
	g = p->g + 1;
	ComputeH();
	ComputeF();

}

PuzzleNode::PuzzleNode()
{
	int i, j;

	for(i=0;i<BSZ;i++)
		for (j = 0; j < BSZ; j++)
		{
			board[i][j] = 1 + i * BSZ + j;
		}
	board[BSZ - 1][BSZ - 1] = 0;
	parent = nullptr;
	emptyRow = BSZ - 1;
	emptyCol = BSZ - 1;
}


PuzzleNode::~PuzzleNode()
{
}

void PuzzleNode::Draw()
{
	int i, j;

	for (i = 0; i<BSZ; i++)
		for (j = 0; j < BSZ; j++)
		{
			if (1 + i * BSZ + j == board[i][j])
				glColor3d(0.8, 1, 0.8);
			else
				glColor3d(0.8, 0.8, 0.8);
			glBegin(GL_POLYGON);
			glVertex2d(j, i);
			glVertex2d(j+1, i);
			glVertex2d(j+1, i+1);
			glVertex2d(j, i+1);
			glEnd();

			glColor3d(0, 0, 0);
			glBegin(GL_LINE_LOOP);
			glVertex2d(j, i);
			glVertex2d(j + 1, i);
			glVertex2d(j + 1, i + 1);
			glVertex2d(j, i + 1);
			glEnd();

			if (board[i][j] > 0)
			{
				if (board[i][j] >= 10)
				{
					glRasterPos2d(j + 0.33, i + 0.55);
					glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
				}
				glRasterPos2d(j + 0.4, i + 0.55);
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0' + board[i][j] % 10);
			}
		}

}

void PuzzleNode::SwapCells(int row, int col)
{
	if (abs(row - emptyRow) == 1 && col == emptyCol ||
		abs(col - emptyCol) == 1 && row == emptyRow) // then we can swap them
	{
		board[emptyRow][emptyCol] = board[row][col];
		board[row][col] = 0;
		emptyRow = row;
		emptyCol = col;
	}
}

int PuzzleNode::ManhattanDistance(int row,int col)
{
	// 1. find its destination
	int i, j;

	if (board[row][col] > 0)
	{
		i = (board[row][col] - 1) / BSZ;
		j = (board[row][col] - 1) % BSZ;
	}
	else
	{
		i = BSZ - 1;
		j = BSZ - 1;
	}
	return abs(i - row) + abs(j - col);
}

// computes Heuristics: sum of distances of each cell from its destination
void PuzzleNode::ComputeH()
{
	int i,j, sum=0;

	for (i = 0; i<BSZ; i++)
		for (j = 0; j < BSZ; j++)
			sum += ManhattanDistance(i,j);

	h = sum;
}

bool PuzzleNode::operator==(const PuzzleNode & other)
{
	int i, j;

	for (i = 0; i < BSZ; i++)
		for (j = 0; j < BSZ; j++)
			if (board[i][j] != other.board[i][j])
				return false;

	return true;
}
