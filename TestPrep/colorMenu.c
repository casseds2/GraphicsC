#include <GL/gl.h>
#include <GL/glext.h>
#include <C:/Users/casseds95/Desktop/GraphicsC/lab3/glut.h>
#include <math.h>

//roatating, menu, colour change

static int menu_id;
static int value = 0;
static int window;
float theta = M_PI/4;

void display(void)
{
	switch(value) // change colour of square
	{
		case 1:
			glColor3f(1.0,0.0,0.0);
			break;
		case 2:
			glColor3f(1.0,1.0,0.0);
			break;
		case 3:
			glColor3f(0.0,0.0,1.0);
			break;
	}
	glClearColor(0.0,0.0,0.0,0.0); //background colour
	glClear(GL_COLOR_BUFFER_BIT); //clear colour
	
	GLfloat x=cos(theta), y=sin(theta);//idle
	
	glBegin(GL_POLYGON);
		glVertex2f(-x,-y);
		glVertex2f(-y,x);
		glVertex2f(x,y);
		glVertex2f(y,-x);
	glEnd();
	
	glFlush();
	return;
}

void menu(int num) // get the menu id
{
	if(num ==0)
	{
		glutDestroyWindow(window);
		exit(0);
	}
	else
	{
		value = num;	
	}

	glutPostRedisplay();
}
void createMenu(void)
{
	menu_id = glutCreateMenu(menu);
	glutAddMenuEntry("red",1);
	glutAddMenuEntry("yellow",2);
	glutAddMenuEntry("blue",3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MyIdle() //rotate around center
{
	theta += 0.001;
	if (theta > 2*M_PI) theta -= 2*M_PI;
	glutPostRedisplay();

	return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("simple");
	createMenu();
	glutDisplayFunc(display);
	glutIdleFunc(MyIdle);
	
	glutMainLoop();
}