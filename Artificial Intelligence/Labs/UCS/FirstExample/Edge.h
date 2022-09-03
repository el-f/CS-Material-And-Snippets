#pragma once
class Edge
{
private:
	int firstIndex, secondIndex;
	double cost;

public:
	Edge();
	~Edge();
	void setFirstIndex(int i) { firstIndex = i; }
	void setSecondIndex(int i) { secondIndex = i; }
	void setCost(double c) { cost = c; }
	void DrawMe(double x1, double y1, double x2, double y2);

	int getFirstIndex() { return firstIndex; }
	int getSecondIndex() { return secondIndex; }
	double getCost() { return cost; }
};

