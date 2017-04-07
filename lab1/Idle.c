#include <GL/gl.h>
#include <GL/glext.h>
#include <C:\Users\casseds95\Desktop\GraphicsC\lab3\glut.h>
#include <math.h>

/*
This program illustrates the use of the Idle Callback,
in this case to carry out some animation.
It draws a rotating square.
*/

float theta = M_PI/4; //Constant Pi

void display(void)
{
	glClearColor(0.0,256,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,256);

	GLfloat x=cos(theta), y=sin(theta);

	glBegin(GL_POLYGON);
		glVertex2f(-x,-y);
		glVertex2f(-y,x);
		glVertex2f(x,y);
		glVertex2f(y,-x);
	glEnd();

	glFlush();
	return;
}

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0,1.0,-1.0,1.0);
	glViewport(0,0,w/2,h/2);
	return;
}

void MyIdle()
{

	theta -= 0.001; //REVERSE THE DIRECTION OF THE SPIN
	if (theta > 2*M_PI) theta -= 2*M_PI;
	glutPostRedisplay();

	return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("Spinning Square");
	glutDisplayFunc(display);
	glutIdleFunc(MyIdle);


	glutMainLoop();
}
