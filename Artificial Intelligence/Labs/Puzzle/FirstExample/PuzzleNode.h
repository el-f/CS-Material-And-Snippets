#pragma once

const int BSZ = 4;
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

/*
 * true: use A* - optimal solution but slower to find.
 * false: use Best First - not guaranteed optimal solution but faster to find.
 */
constexpr bool GET_OPTIMAL_SOLUTION = true;

class PuzzleNode
{
private:
	int board[BSZ][BSZ];
	int g, h, f;
	PuzzleNode* parent;
	int emptyRow, emptyCol;
public:
	PuzzleNode(PuzzleNode* p, int dir);
	PuzzleNode();
	~PuzzleNode();
	void Draw();
	void SwapCells(int row, int col);
	int ManhattanDistance(int row, int col);
	void setG(int value) { g = value; }
	void ComputeH();
	void ComputeF() { f = GET_OPTIMAL_SOLUTION ? g + h : h; }
	int getG() { return g; }
	int getH() { return h; }
	int getF() { return f; }
	int getEmptyRow() { return emptyRow; }
	int getEmptyCol() { return emptyCol; }
	bool operator == (const PuzzleNode &other);
	PuzzleNode* getParent() { return parent; }


};

