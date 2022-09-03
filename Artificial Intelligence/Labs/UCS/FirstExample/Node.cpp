#include "Node.h"
#include "GLUT.H"


Node::Node()
{
	color = WHITE;
	parent = nullptr;
}


Node::~Node()
{
}

void Node::DrawMe()
{
	double sz=0.6;
	switch (color)
	{
	case WHITE:
		glColor3d(1, 1, 1);
		break;
	case GRAY:
		glColor3d(0, 1, 1);
		break;
	case BLACK:
		glColor3d(0, 0, 0);
		break;
	case PATH:
		glColor3d(1, 0, 1);
		break;
	case START:
		glColor3d(0, 0, 1);
		break;
	case TARGET:
	case WHITE_TARGET:
		glColor3d(1,0, 0);
		break;
	case GRAY_TARGET:
		glColor3d(1, 0.6, 0);
		break;
	}
	// fill with color
	glBegin(GL_POLYGON);
	glVertex2d(x-sz, y);
	glVertex2d(x, y+sz);
	glVertex2d(x+sz, y);
	glVertex2d(x, y-sz);
	glEnd();
	// border
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2d(x - sz, y);
	glVertex2d(x, y + sz);
	glVertex2d(x + sz, y);
	glVertex2d(x, y - sz);
	glEnd();

}
