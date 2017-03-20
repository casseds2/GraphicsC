#include <GL/gl.h>
#include <h:/C/glut.h>
#include <GL/glext.h>

/*
This program illustrates the use of the Reshape Callback,
which is called whenever the window is resized.
It contains the functions gluOrtho2D and glViewport.
At the moment, the viewport is set to half the window size.
*/

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);

	glBegin(GL_LINE_LOOP);
		glColor3f(1.0,1.0,0.0);
		glVertex2f(-0.5,-0.5);
		glColor3f(1.0,0.0,0.0);
		glVertex2f(-0.5,0.5);
		glColor3f(0.0,1.0,0.0);
		glVertex2f(0.5,0.5);
		glColor3f(0.0,0.0,1.0);
		glVertex2f(0.5,-0.5);
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

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("simple");
//	glColor3f(1.0,0.0,0.0);
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);


	glutMainLoop();
}