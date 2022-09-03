#include "GLUT.h"
#include <math.h>
#include "Player.h"
#include <time.h>

const double PI = 3.14;

Player* p;
Player* p1;


void init()
{
	glClearColor(0, 0.6, 0.2, 0); // RGB - sets background color
	glOrtho(0, MSZ, 0, MSZ, -1, 1); // setup coordinate system
	srand(time(0));
	p = new Player();
	p1 = new Player();


}

void DrawTree(int x, int y)
{
	glLineWidth(2);
	glColor3d(0.8, 0.4, 0);
	glBegin(GL_LINES);
	glVertex2d(x, y + 2);
	glVertex2d(x, y);
	glEnd();
	glLineWidth(1);

	glColor3d(0, 0.4, 0);
	glBegin(GL_POLYGON);
	glVertex2d(x, y + 5);
	glVertex2d(x+2, y + 3);
	glVertex2d(x - 2, y + 3);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2d(x, y + 3);
	glVertex2d(x + 2, y+1);
	glVertex2d(x - 2, y+1);
	glEnd();



}

void DrawForest()
{
	DrawTree(81, 79);
	DrawTree(78, 86);
	DrawTree(84, 89);
}

void DrawStock()
{
	glColor3d(0.8, 0.8, 0.8);
	glBegin(GL_POLYGON);
	glVertex2d(15, 15);
	glVertex2d(15, 20);
	glVertex2d(25, 20);
	glVertex2d(25, 15);
	glEnd();
	glColor3d(0.6, 0.4, 0);
	glBegin(GL_POLYGON);
	glVertex2d(18, 15);
	glVertex2d(18, 18);
	glVertex2d(22, 18);
	glVertex2d(22, 15);
	glEnd();

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // fills all the frame buffer with background color

	DrawForest();
	DrawStock();

	p->DrawMe();
	p1->DrawMe();


	glutSwapBuffers();// show what was drawn in "frame buffer"
}

void idle()
{
	p->Execute();
	p1->Execute();
	glutPostRedisplay(); // calls indirectly to display
}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE); // double means it uses double buffer
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("FSM Example");

	glutDisplayFunc(display); // refresh function
	glutIdleFunc(idle); // runs all the time in the background

	init();

	glutMainLoop();
}