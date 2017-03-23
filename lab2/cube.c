#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/C/lab2/glut.h>


void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,1.0,1.0,0.0,0.0,0.0,1.0,0.0,0.0); //changing 4th value will bring it towards the view plain(or outsde of it)
													//changing 5th value will tilt the image to the right amd shift right?
													//6th value does opposite to th value
													//Not sure about 7th value, doesn't change much until set to 0

	glutWireCube(0.5);
	
	glFlush();
	return;
}


void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	glFrustum(-1.0,1.0,-1.0,1.0,1.0,3.0); //when last number is 3, we get the 3D view, if changed to 1.5, we get the hidden sides of the 3D view			  
										  //4th number controls the height of the image displayed in glFrustrum
	                                      //5t number also seems to control what is shown (3D or hidden edges of 3D)


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