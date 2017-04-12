#include <GL/gl.h>
#include <GL/glext.h>
#include <C:/Users/casseds95/Desktop/GraphicsC/lab3/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

GLfloat yRotated;
GLubyte image[64][64][3];
bool click = true; //For controlling when it should spin left or right
bool right_arrow_pressed = false;
bool left_arrow_pressed = true;
int menu_id;
int window;
int value = 0;
bool allowedSpin = true;
char words[6][80];
int currentColour = 0;
double moveX, moveY, moveZ=5;

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

material yellow = {
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

material red = {
	{256, 1, 0, 1.0},
	{256, 1, 0, 1.0},
	{256, 1, 0, 1.0},
	50
};

material blue = {
	{0, 0, 256, 1.0},
	{0, 0, 256, 1.0},
	{0, 0, 256, 1.0},
	20
};

void materials(material *m){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m->shininess);
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
	glutAddMenuEntry("Spin",4);
	glutAddMenuEntry("Stop Spin",5);
	glutAddMenuEntry("Mirror World",6);
	glutAddMenuEntry("Return To Normal World",7);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

/*Resets the Colour to the Previous Colour*/
void setCurrentColour(int x){
	if(x == 1)
		materials(&red);
	if(x == 2)
		materials(&yellow);
	if(x == 3)
		materials(&blue);
}

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0,0,moveZ,0.0,0.0,0.0,0.0,1.0,0.0);

	/*Define Light*/
	GLfloat sunlightDiffuse[] = {256.0f, 0.0f, 0.0f};
	GLfloat sunlightSource[] = {-5.0f, 3.0f, 6.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sunlightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, sunlightSource);
    
	/*Texture Parameters*/
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	/*Remembers the Colour (Fixes Issue of Colour Being Reset By Stop Spin / Spin)*/
	setCurrentColour(currentColour);

	/*Change Colours Based Off of Menu Calls*/
	switch(value)
	{
		case 1:
			materials(&red);
			currentColour = 1;
			break;
		case 2:
			materials(&yellow);
			currentColour = 2;
			break;
		case 3:
			materials(&blue);
			currentColour = 3;
			break;
		case 4:
			allowedSpin = true;
			break;
		case 5:
			allowedSpin = false;
			break;
		case 6:
			moveZ = -5;
			break;
		case 7:
			moveZ = 5;	
			break;	
	}

	//glTranslatef(moveX, moveY, moveZ);

	/*Insert Writing*/
	glPushMatrix();
		int i;
		int length;
		glColor3f(256.0, 0.0, 0.0);
		glTranslatef(0.0, 1.5, 0.0);
		glScalef(0.003, 0.003, 0.003);
		length = (int)strlen(words[0]);
		glTranslatef(-(length*37), -(200), 0.0);
		//glRotatef(yRotated, 0, 1, 0);
		for(i = 0; i < length; i++){
			glutStrokeCharacter(GLUT_STROKE_ROMAN, words[0][i]);
		}
	glPopMatrix();

	/*Draw The Sun*/
    glPushMatrix();
	    glutSolidSphere(0.5, 20, 20);
	glPopMatrix();

	glPushMatrix();
		materials(&black);
		glRotatef(yRotated, 0, 0, 1);
		glutWireCube(0.4);
	glPopMatrix();	

	/*Draw a Lenna Planet*/
	glPushMatrix();
		glRotatef(yRotated, 0, 0, 1);
		glTranslatef(-1.0, 0, 0);
		GLUquadricObj *MySphere;
		MySphere = gluNewQuadric();
		gluQuadricTexture(MySphere,1);
		glRotatef(yRotated, 1, 0, 0);
		materials(&white);
		gluSphere(MySphere,0.4,20,20);
	glPopMatrix();

	glFlush();
	return;
}

/**Manage The Click Event**/
void manageRotationEvent(){
	if(!click && right_arrow_pressed == true && allowedSpin == true){
		yRotated -= 2.0;
		display();
		glutTimerFunc(25, manageRotationEvent, 0);
	}
	if(click && left_arrow_pressed == true && allowedSpin == true){
		yRotated += 2.0;
		display();
		glutTimerFunc(25, manageRotationEvent, 0);
	}
	if(allowedSpin == false){
		yRotated += 0;
		display();
		glutTimerFunc(25, manageRotationEvent, 0);
	}
}

/*Handle Window Reshape Events*/
void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0,1.0,-1.0,1.0,3,20.0);
	glViewport(0,0,w,h);
	return;
}

/*Events handled by clicks*/
void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
	if(state == GLUT_DOWN && button == GLUT_LEFT_BUTTON){
		click = true;
		left_arrow_pressed = true;
	}
	if(state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON){
		click = false;	
		right_arrow_pressed = true;
	}
}

/*Minor Function to Load the Lenna Image*/
void loadLenna(){
	int i,j;
	FILE *fp;
	char buffer[4096],*pb;

	fp = fopen("texture.bin","r");
	fread(buffer, 4096,1,fp);

	pb = buffer;

	for(i=0; i<64; i++){
		for(j=0; j<64; j++)
		{		
			image[i][j][0]=(GLubyte)*pb;
			image[i][j][1]=(GLubyte)*pb;
			image[i][j][2]=(GLubyte)*pb;
			pb++;
		}
	}
}

/*Manage a Left or Right Arrow Click*/
void manageKeyboardEvent(int key, int x, int y){
	if(key == GLUT_KEY_RIGHT){
		right_arrow_pressed = true;
		left_arrow_pressed = false;
		click = false;
	}
	if(key == GLUT_KEY_LEFT){
		left_arrow_pressed = true;
		right_arrow_pressed = false;
		click = true;
	}
}

void manageKeyCharEvent(unsigned char key, int x, int y){
	switch(key){
		case 'w':
			moveY += 0.2;
			break;
		case 's':
			moveY -= 0.2;
			break;
		case 'a':
			moveX -= 0.2;
			break;
		case 'd':
			moveX += 0.2;
			break;
		case 'q':
			moveZ += 0.2;
			break;
		case 'z':
			moveZ -= 0.2;
			break;		
		default:return;				
	}
}

int main(int argc, char **argv)
{
	loadLenna();
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("Solar System");
	strcpy(words[0], "Marks plz?");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(MyMouse);
	glutSpecialFunc(manageKeyboardEvent);
	glutKeyboardFunc(manageKeyCharEvent);
	glutTimerFunc(25, manageRotationEvent, 0);
	createMenu();
	glutMainLoop();
}