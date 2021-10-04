#include "GL\glew.h"
#include <glut.h>
#include<windows.h>
#include<windows.h>
#include <iostream>
#include <fstream>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "GL\Wglew.h"
#include <glut.h>
#include<stdio.h>
#include <GLAUX.H>
#include <glut.h>
#include <GLU.H>
#include <math.h>
#include <iostream>
#include <glu.h>
#include <cmath>
#include <vector> 
#include <string> 
#include "image_DXT.h"
#include "image_helper.h"
#include "image_DXT.h"
#include "GLFW\glfw3.h"
#include<stdio.h>
#include<GL/glu.h>
#include<vector>
#include "Trees.h"
#include "circles2.h"

float dx = -0.7;
float dy = -1.7;
float c = 1;

GLubyte fish[] = {
	0x00, 0x60, 0x01, 0x00,
	0x00, 0x90, 0x01, 0x00,
	0x03, 0xf8, 0x02, 0x80,
	0x1c, 0x37, 0xe4, 0x40,
	0x20, 0x40, 0x90, 0x40,
	0xc0, 0x40, 0x78, 0x80,
	0x41, 0x37, 0x84, 0x80,
	0x1c, 0x1a, 0x04, 0x80,
	0x03, 0xe2, 0x02, 0x40,
	0x00, 0x11, 0x01, 0x40,
	0x00, 0x0f, 0x00, 0xe0,
};

#define checkImageWidth 80
#define checkImageHeight 80
typedef GLubyte Pixel[3];
static GLuint texName;
#define checkImageWidth 64
#define checkImageHeight 64
static GLubyte checkImage[checkImageHeight][checkImageWidth][4];

GLfloat randomFloat() {
	return (GLfloat)rand() / RAND_MAX;
}

void makeCheckImage(void)
{
	int i, j, c;

	for (i = 0; i < checkImageHeight; i++) {
		for (j = 0; j < checkImageWidth; j++) {
			c = ((((i & 0x8) == 0) ^ ((j & 0x8)) == 0)) * 255;
			checkImage[i][j][0] = (GLubyte)0;
			checkImage[i][j][1] = (GLubyte)c;
			checkImage[i][j][2] = (GLubyte)60;
			checkImage[i][j][3] = (GLubyte)255;
		}
	}
}


void init(void)
{
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	makeCheckImage();
	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, checkImageWidth,checkImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,checkImage);

	//
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 150.0 };
	GLfloat light_position[] = { 4.0, 1.0, 1.0, 0.0 };
	GLfloat lmodel_ambient[] = { 0.1, 0.8, 0.1, 1.0 };
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	

	glTranslatef(0, 0, 0);
	glRotatef(0, 0.0, 1.0, 0.0);
	glScalef(1, 1, 1);
	
	
	//sky
	glColor3f(0,0.5,1);
	glBegin(GL_QUADS);
	glTexCoord3f(0.0, 0.0, -10); glVertex3f(-50.0, -50.0, -10.0);
	glTexCoord3f(0.0, 30.0, -10); glVertex3f(-50.0, 50.0, -10.0);
	glTexCoord3f(50.0, 30.0, -10); glVertex3f(50.0, 50.0, -10.0);
	glTexCoord3f(50.0, 0.0, -10); glVertex3f(50.0, -50.0, -10.0);
	glEnd();

	glFlush();
	

	//earth
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glBegin(GL_POLYGON);
	glVertex3f(-10,-1, 0.0);
	glVertex3f(-10,-7, 0.0);
	glVertex3f(10,-7, 0.0);
	glVertex3f(10,-1, 0.0);
	glEnd();
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);
	glFlush();

	//writing		
	glColor3f(0, 0, 0);
	glRasterPos3f(0, 2.7, 0);
	char * s = "Nature";
	int l = (int)strlen(s);
	for (int i = 0; i < l; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
	}
	glFlush();

	// Load textures
	GLuint textures[2];
	glGenTextures(2, textures);


	int width, height;
	unsigned char* image;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texName);

	// trees
	glColor3f(0.4, 0.7, 0.2);
	
	glScalef(4, 3, 1);
	// set input data to arrays
	glVertexPointer(3, GL_FLOAT, 0, TreesVerts);
	glNormalPointer(GL_FLOAT, 0, TreesNormals);
	glTexCoordPointer(2, GL_FLOAT, 0, TreesTexCoords);
	// draw data
	glDrawArrays(GL_TRIANGLES, 0, TreesNumVerts);
	glFlush();

	glTranslatef(1.0, 0, 0);
	glVertexPointer(3, GL_FLOAT, 0, TreesVerts);
	glNormalPointer(GL_FLOAT, 0, TreesNormals);
	glTexCoordPointer(2, GL_FLOAT, 0, TreesTexCoords);
	// draw data
	glDrawArrays(GL_TRIANGLES, 0, TreesNumVerts);
	glFlush();

	glTranslatef(-2.0, 0, 0);
	glVertexPointer(3, GL_FLOAT, 0, TreesVerts);
	glNormalPointer(GL_FLOAT, 0, TreesNormals);
	glTexCoordPointer(2, GL_FLOAT, 0, TreesTexCoords);
	// draw data
	glDrawArrays(GL_TRIANGLES, 0, TreesNumVerts);
	glDisable(GL_TEXTURE_2D);
	glFlush();

	

	//sun
	glColor3f(1, c, 0);
	glScalef(0.3, 0.3, 1);
	glTranslatef(2, 2.7, 0.0);
	glutSolidSphere(0.4, 12, 20);
	glFlush();
		

	//lake
	glColor3f(0, 1, 1);
	glRotatef(20, 90, 3, 0.0);
	glTranslatef(2,-6, -0.1);
	glScalef(dx, dy, 2);
		
	// set input data to arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, circles2Verts);
	glNormalPointer(GL_FLOAT, 0, circles2Normals);
	glTexCoordPointer(2, GL_FLOAT, 0, circles2TexCoords);
	// draw data
	glDrawArrays(GL_TRIANGLES, 0, circles2NumVerts);
	glFlush();


	//FLSHES
	glScalef(0.2,0.2,0);
	for (int i = 0; i < 8; i++) {
		glColor3f(randomFloat(), randomFloat(), randomFloat());
		glRasterPos3f(randomFloat(), randomFloat(), i-0.1);
		glBitmap(27, 11, 0, 0, 0, 0, fish);
	}
	glFlush();



	
	glColor3f(1, 1, 1);
	glutSwapBuffers();
	glPopMatrix();
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	case 'h':
		dx = dx + 0.3;
		dy = dy + 0.3;
		glutPostRedisplay();
		break;

	case 'k':
		c = 0.6;
		glutPostRedisplay();
		break;

	case 'g':
		dx = dx - 0.3;
		dy = dy - 0.3;
		glutPostRedisplay();
		break;
	case 'j':
		exit(0);
		break;

	default:
		break;
	}
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0);
}
void mouse(int button, int state, int x, int y)
{
	switch (button) {

	case GLUT_RIGHT_BUTTON:
		PlaySound("Summer.wav", NULL, SND_ASYNC);

		break;

	default:
		break;
	}
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

