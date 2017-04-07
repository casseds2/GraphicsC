#include <GL/gl.h>
#include <GL/glext.h>
#include <C:\Users\casseds95\Desktop\GraphicsC\lab3\glut.h>


void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

	glTranslatef(0.0, 0.0, -2.0);
	glRotatef(5, 1, 1, 0); //Rotatef(angle, set 1 for x-axis, set 1 for y-axis, set 1 for z-axis)
	//5 degree Rotation, at the start, the cube will be pointed directly at you(as much as a cube can be).
	//Degrees rotation apply on it from the x, y, z axis....all flags(1s) can be set at the same time.
	glutWireSphere(2, 30, 30); //generate the wire sphere
	
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