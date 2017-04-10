#include <GL/gl.h>
#include <GL/glext.h>
#include <C:/Users/casseds95/Desktop/GraphicsC/lab3/glut.h>
#include <stdbool.h>
#include <stdio.h>

GLfloat yRotated;
int x_axis = 0;
int y_axis = 1; //Must have one axis set to functions prperly
bool click = false;


void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,2.0,0.0,0.0,0.0,0.0,1.0,0.0);

    glRotatef(yRotated, x_axis, y_axis, 0);
    glutWireCube(0.5);
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

/*Rotate Based off Keyboard Functions*/
void keyboardRotate(unsigned char key, int x, int y){
	if(key == 32){
		click = !click;
	}
	switch(key){
		case 32 :
			click = !click;
			break;
		case GLUT_KEY_RIGHT : //Right
			if(x_axis == 0)
				x_axis = 1;
			else
				x_axis = 0;
			printf("%d X-axis:" + x_axis);
			break;
		/*	
		case : 263 //Left
			if(x_axis == 1)
				x_axis = 0;
			else
				x_axis = 1;
			break;
		*/		
		case GLUT_KEY_DOWN : //Down
			if(y_axis == 0)
				y_axis = 1;
			else
				y_axis = 0;
		    printf("%d Y-axis:" + y_axis);
			break;
		//case : 265 //Up		
	}
}

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-2.0,2.0,-2.0,2.0,0.3,5.0);
	glFrustum(-1.0,1.0,-1.0,1.0,1.0,3.0);
//	gluPerspective(60,1.0,0.3,10.0);
	glViewport(0,0,w,h);
	return;
}

/*Used if idle function desired*/
void myRotate(){
    yRotated += 0.01;
    display();
}

/*Events handled bby clicks*/
void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
		click = true;
	if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
		click = false;	
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(MyMouse);
	glutTimerFunc(25, manageEvent, 0);
	glutKeyboardFunc(keyboardRotate);
	//glutIdleFunc(myRotate);
	glutMainLoop();
}
