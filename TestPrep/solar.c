#include <GL/gl.h>
#include <GL/glext.h>
#include <C:/Users/casseds95/Desktop/GraphicsC/lab3/glut.h>
#include <stdbool.h>
#include <stdio.h>

GLfloat yRotated;
GLubyte image[64][64][3];
bool click = true; //For controlling when it should spin left or right
bool right_arrow_pressed = false;
bool left_arrow_pressed = true;

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
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-1.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);

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

	/*Draw The Sun*/
    glPushMatrix();
	    materials(&red);
	    glutSolidSphere(0.5, 20, 20);
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
	if(!click && right_arrow_pressed == true){
		yRotated -= 2.0;
		display();
		glutTimerFunc(25, manageRotationEvent, 0);
	}
	if(click && left_arrow_pressed == true){
		yRotated += 2.0;
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

/*Events handled bby clicks*/
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

void manageKeyboardEvent(int key, int x, int y){ //right = 262; left = 263
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

int main(int argc, char **argv)
{
	loadLenna();
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("Solar System");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutMouseFunc(MyMouse);
	glutSpecialFunc(manageKeyboardEvent);
	glutTimerFunc(25, manageRotationEvent, 0);
	glutMainLoop();
}