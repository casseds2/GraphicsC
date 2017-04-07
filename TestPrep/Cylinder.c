#include <GL/gl.h>
#include <GL/glext.h>
#include <C:/Users/casseds95/Desktop/GraphicsC/lab3/glut.h>

/* This program draws a cylinder and then rotates it by 90 degs.
Then it places a cuboid on top of the cylinder
*/


void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,2.0,2.0,0.0,0.0,0.0,0.0,1.0,0.0);


	GLUquadricObj *MyCylinder;
	MyCylinder = gluNewQuadric();
	gluQuadricDrawStyle(MyCylinder, GLU_LINE);

	glRotatef(-90.0,1.0,0.0,0.0);
	gluCylinder(MyCylinder,0.5,0.5,1.0,12,12);

	glRotatef(90.0,1.0,0.0,0.0);
	glTranslatef(0.0,1.0,0.0);
	glRotatef(-30.0,0.0,0.0,1.0);
	glTranslatef(0.0,0.5,0.0);
	glScalef(0.25,1.0,0.25);
	glutWireCube(1.0);

	glFlush();
	return;
}


void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	glFrustum(-1.0,1.0,-1.0,1.0,0.5,6.0);


	glViewport(0,0,w,h);
	return;
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cylinder");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);


	glutMainLoop();
}
