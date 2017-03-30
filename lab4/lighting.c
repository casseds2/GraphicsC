#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/glut.h>

/*
This program illustrates a simple point light source.

*/

void display(void)
{
	glClearColor(1.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
//	glDisable(GL_BLEND);


	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

	GLfloat pos1[4] = {0.0,1.0,0.0,1.0};
	glLightfv(GL_LIGHT0,GL_POSITION,pos1);
	GLfloat pos2[4] = {0.0,1.0,0.0,1.0};
	glLightfv(GL_LIGHT1,GL_POSITION,pos2);

	//glTranslatef(0.0,0.5,0.0);
	glRotatef(45.0,0.0,0.0,1.0);
	glutSolidTeapot(0.5);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	
	//glutSolidTorus(0.5,0.75,24,24);
	
	glFlush();
	return;
}

typedef struct material{
	GL float ambient [ 4 ] ;
	GL float diffuse [ 4 ] ;
	GL float specular [ 4 ] ;
	GL float shininess
	} 
material ;
material brass = {
	{0. 33 , 0 . 2 2 , 0 . 0 3 , 1 . 0 } ,
	{0. 78 , 0 . 5 7 , 0 . 1 1 , 1 . 0 } ,
	{0. 99 , 0 . 9 1 , 0 . 8 1 , 1 . 0 } ,
	27. 8
};

void materials ( material *m)
{
glMaterialfv(GL FRONT AND BACK, GL AMBIENT, m−>ambient ) ;
glMaterialfv (GL FRONT AND BACK, GL DIFFUSE , m−>d i f f u s e ) ;
glMaterialfv(GL FRONT AND BACK, GL SPECULAR , m−>s p e c u l a r ) ;
glMaterialfv(GL FRONT AND BACK, GL SHININESS , m−>s h i n i n e s s ) ;
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