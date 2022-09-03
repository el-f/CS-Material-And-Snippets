#pragma once
#include "Edge.h"
#include <vector>

using namespace std;

const int WALL = 0;
const int SPACE = 1;
const int START = 2;
const int TARGET = 3;
const int GRAY = 4;
const int BLACK = 5;
const int PATH = 6;
const int WHITE = 7;
const int GRAY_TARGET = 8;
const int WHITE_TARGET = 9;


class Node
{
private:
	double x, y;
	int color;
	vector<Edge> outgoing;
	int index;
	double g;
	Node* parent;

public:
	Node();
	~Node();
	void DrawMe();
	void setX(double value) { x = value; }
	void setY(double value) { y = value; }
	void setIndex(int i) { index = i; }
	void setColor(int c) { color = c; }
	void setG(double value) { g = value; }
	void setParent(Node* p) { parent = p; }

	double getX() { return x; }
	double getY() { return y; }
	int getColor() { return color; }
	double getG() { return g; }
	vector<Edge> GetOutgoing() { return outgoing; }
	int getIndex() { return index; }
	Node* getParent() { return parent; }
	void AddEdge(Edge &e) { outgoing.push_back(e); }
};

