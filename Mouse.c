#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/C/glut.h>

/*
This program illustrates the Mouse Function Callback.
It uses the right mouse button to select the corners
of a rectangle and then draws the rectangle.

This program assumes the window size is 500x500.
If you resize the window, it will not work.
*/

GLfloat x1,x2,z,y2;

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);
	glColor3f(1.0,0.0,0.0);

	glBegin(GL_POLYGON);
		glVertex2f(x1,z);
		glVertex2f(x1,y2);
		glVertex2f(x2,y2);
		glVertex2f(x2,z);
	glEnd();

	glFlush();
	return;
}

void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
	static int first=1;

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (first)
		{
			x1=(x-250.0)/250.0; 
			z=-(y-250)/250.0;;
		}
		else
		{
			x2=(x-250.0)/250.0;
			y2=-(y-250)/250.0;
			glutPostRedisplay();
		}
		first = !first;
	}

	return;
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("mouse");
	glutDisplayFunc(display);
	glutMouseFunc(MyMouse);


	glutMainLoop();
}