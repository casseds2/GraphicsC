#include <GL/gl.h>
#include <GL/glext.h>
#include <C:/Users/casseds95/Desktop/GraphicsC/lab3/glut.h>
#include <stdbool.h>
#include <stdio.h>

GLfloat yRotated;
int x_axis = 0;
int y_axis = 1; //Must have one axis set to functions prperly
bool click = false; //For controlling when it should spin left or right

typedef struct material{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} material;

material black ={
	{0, 0, 0, 1.0},
	{0, 0, 0, 1.0},
	{0, 0, 0, 1.0},
	20
};

material brown = {
	{102, 51, 0, 1.0},
	{102, 51, 0, 1.0},
	{102, 51, 0, 1.0},
	20
};

material white = {
	{256, 256, 256, 1.0},
	{256, 256, 256, 1.0},
	{256, 256, 256, 1.0},
	20
};

void materials(material *m){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m->shininess);
}

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,2.0,0.0,0.0,0.0,0.0,1.0,0.0);

	glPushMatrix(); //Cigar
		GLUquadricObj *MyCylinder;
		MyCylinder = gluNewQuadric();
		gluQuadricDrawStyle(MyCylinder, GLU_FILL);
		glRotatef(yRotated, x_axis, y_axis, 0);
		glRotatef(90.0,1.0,0.0,1.0);
		glRotatef(yRotated, x_axis, y_axis, 0);
		gluCylinder(MyCylinder,0.1,0.1,0.5,12,12);
	glPopMatrix();

    glPushMatrix(); //Left Ear
    	glRotatef(yRotated, x_axis, y_axis, 0);
    	glTranslatef(-0.45, 0.8, 0.0);
    	glRotatef(yRotated, x_axis, y_axis, 0);
    	materials(&white);
    	glutSolidSphere(0.2, 20, 20);
    glPopMatrix();	

	glPushMatrix(); //Right Ear
		glRotatef(yRotated, x_axis, y_axis, 0);
		glTranslatef(0.45, 0.8, 0.0);
		glRotatef(yRotated, x_axis, y_axis, 0);
		materials(&black);
		glutSolidSphere(0.2, 20, 20);
	glPopMatrix();

    glPushMatrix(); //Main Head
    	glTranslatef(0.0, 0.3, 0);
    	glRotatef(yRotated, x_axis, y_axis, 0);
    	materials(&black);
		glutSolidSphere(0.5, 20, 20);
	glPopMatrix();

	glPushMatrix(); //Right Eye
		glRotatef(yRotated, x_axis, y_axis, 0);
		glTranslatef(0.15, 0.3, 0.4);
		glScalef(0.6,1.0,1.0);
		glRotatef(yRotated, x_axis, y_axis, 0);
		materials(&white);
		glutSolidSphere(0.08, 20, 20);
	glPopMatrix();

	glPushMatrix(); //Left Eye
		glRotatef(yRotated, x_axis, y_axis, 0);
		glTranslatef(-0.15, 0.3, 0.4);
		glScalef(0.6,1.0,1.0);
		glRotatef(yRotated, x_axis, y_axis, 0);
		materials(&white);
		glutSolidSphere(0.08, 20, 20);
	glPopMatrix();

	glPushMatrix();	//Box it Stands On
    	glTranslatef(0.0, -0.5, 0.0);
    	materials(&black);
    	glutSolidCube(0.5);
    glPopMatrix();

	glFlush();
	return;
}

/**Manage The Click Event**/
void manageEvent(int value){
	if(!click){
		yRotated += 2.0;
		display();
		glutTimerFunc(25, manageEvent, 0);
	}
	else{
		yRotated -= 2.0;
		display();
		glutTimerFunc(25, manageEvent, 0);
	}
}

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0,1.0,-1.0,1.0,1.0,3.0);
	glViewport(0,0,w,h);
	return;
}

/*Used if idle function desired*/
void myRotate(){
    yRotated += 0.01;
    display();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(25, manageEvent, 0);
	//glutIdleFunc(myRotate);
	glutMainLoop();
}
