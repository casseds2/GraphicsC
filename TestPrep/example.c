#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <math.h>

double spin;
int tears;
unsigned char* image;
int crying;
//
//void initiateTexture(void){
//    initiateTexture();
//    GLuint tex;
//    glGenTextures(1, &tex);
//    glBindTexture(GL_TEXTURE_2D, tex);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    int width, height;
//    image = SOIL_load_image("wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//    SOIL_free_image_data(image);
//}

void display(void){
    crying=1;
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,2.5, 0.0,0.0,0.0, 0.0,1.0,0.0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);

////--- GL Ambient Lighting: Same amount of lighting everywhere. ----
//    GLfloat ambientColor[] = {1.2f,1.2f,1.2f,0.1f}; //first three is the intensity for each different colour.
//    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientColor);
//
////-----------------------------------------------------------------
////---- Add lighting source -----
//    GLfloat lightColor[] = {0.5f,0.5f,0.5f,1.0f}; //Colour (0.5,0.5,0.5)
//    GLfloat lightPos[] = {1.0f, 3.0f, -6.0f, 1.0f}; //Positioned at (4,0,8)
//
//    //Setting the intensity of the light. GL_DIFFUSE: Setting Colour. lightColor: Intensity of the light
//    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
//    //Setting the position of our light. GL_POSITION: Position of light. lightPos: coordinates; *NOTE* Relative to current transformation
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);


//---- Add directed light -----
    GLfloat lightColor1[] = {1.0f, 1.0f, 1.0f, 1.0f}; //Color (0.5, 0.2, 0.2)
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {0.0f,-2.0f,-6.5f,0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);


    GLUquadricObj *MyCylinder;
    MyCylinder = gluNewQuadric();
    gluQuadricDrawStyle(MyCylinder, GLU_LINE);


    glRotatef(spin/10,0.0,1.0,0.0);
    glPushMatrix();
        glTranslatef(0.0,-1.0,0.0);
//        glRotatef(-spin,0.0,1.0,0.0);
        glutSolidCube(0.8);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,0.35,0.0);
//        glRotatef(spin,0.0,1.0,0.0);
        glutSolidSphere(.9,148,28);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(1.0,1.2,0.0);
        glRotatef(spin,0.0,0.0,1.0);
        glutSolidSphere(.4,26,26);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.0,1.2,0.0);
        glRotatef(spin*3,0.0,0.0,1.0);
        glutSolidSphere(.4,26,26);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0,0.0,-0.9);
//        glRotatef(180,0.0,1.0,0.0);
//        glRotatef(70,0.0,0.0,1.0);
        gluCylinder(MyCylinder,.2,.2,0.02,12,12);
//        glTranslatef(.5,0.0,0.0);
    glPopMatrix();

    if(crying==1){
        glPushMatrix();
            glTranslatef(.45,0.65,-0.9);
            glRotatef(spin*50,0.0,0.0,1.0);
            glutSolidSphere(.22,10,10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(-.45,0.65,-0.9);
            glRotatef(spin*50,0.0,0.0,1.0);
            glutSolidSphere(.22,10,10);
        glPopMatrix();
            if(tears<201){
            glPushMatrix();
                glTranslatef(.45,0.40,-0.9);
                int count=0;
                for(int i=0; i<tears; i++){
                    if(i%10==0){
                       count++;
                       glTranslatef(0.0,-(count*.05),0.0);
                       glutSolidSphere(.05,10,10);
                    }
                }
                count=0;
            glPopMatrix();
            glPushMatrix();
                glTranslatef(-.45,0.40,-0.9);
                for(int i=0; i<tears; i++){
                    if(i%10==0){
                       count++;
                       glTranslatef(0.0,-(count*.05),0.0);
                       glutSolidSphere(.05,10,10);
                       glTranslatef(.1,0.0,0.0);
                       glutSolidSphere(.05,10,10);
                       glTranslatef(-.2,0.0,0.0);
                       glutSolidSphere(.05,10,10);
                       glTranslatef(.1,0.0,0.0);
                    }
                }
            glPopMatrix();

        }
    }

//    glBegin(GL_LINE_LOOP);
//
//    glEnd();

	glFlush();
	return;
}

void rotate(void){
    spin+=0.4;
    tears++;
    if(tears==600){
        tears=0;
    }
    display();
}

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	glFrustum(-1.0,1.0,-1.0,1.0,1.0,3.0);
	glViewport(0,0,w,h);
	return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(100,700);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutIdleFunc(rotate);
	glutMainLoop();
}