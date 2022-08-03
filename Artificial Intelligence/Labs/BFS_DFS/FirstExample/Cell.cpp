#include "Cell.h"



Cell::Cell()
{
}

Cell::Cell(int r, int c)
{
	row = r;
	col = c;
	parent = nullptr; // has no parent
}

Cell::Cell(int r, int c,Cell* p)
{
	row = r;
	col = c;
	parent = p; 
}


Cell::~Cell()
{
}
