#include <GL/gl.h>
#include <GL/glext.h>
#include <C:/Users/casseds95/Desktop/GraphicsC/lab3/glut.h>

/*
This program illustrates a simple point light source.

*/

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
//	glDisable(GL_BLEND);


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

	GLfloat pos[4] = {0.0,1.0,0.0,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos);

//	glutSolidTeapot(0.5);
	glutSolidTorus(0.5,0.75,24,24);

	glFlush();
	return;
}


void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	glFrustum(-1.0,1.0,-1.0,1.0,0.5,3.0);
	glViewport(0,0,w,h);
	return;
}




int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);


	glutMainLoop();
}
