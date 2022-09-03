#pragma once
#include "PuzzleNode.h"
class ComparePuzzleNodes
{
public:
	ComparePuzzleNodes();
	~ComparePuzzleNodes();
	bool operator() (PuzzleNode* pn1, PuzzleNode* pn2) {
		return pn1->getF() > pn2->getF();
	}
};

