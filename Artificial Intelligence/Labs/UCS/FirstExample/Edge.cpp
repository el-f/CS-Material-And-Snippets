#include "Edge.h"
#include "GLUT.H"



Edge::Edge()
{
}


Edge::~Edge()
{
}

void Edge::DrawMe(double x1, double y1, double x2,double y2)
{
	glColor3d(0, 0, 0);

	glBegin(GL_LINES);
	glVertex2d(x1, y1);	
	glVertex2d(x2, y2);
	glEnd();
}
