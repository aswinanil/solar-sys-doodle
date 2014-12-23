// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>
#include "GL\glut.h"
#include <time.h>

void drawSmiley();
void drawTriCircle(double , double , float ,
			 int , int, int);

using namespace std;

GLfloat PI = 3.14;
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;

void drawArc(double cx, double cy, float r,
			 int startDeg, int endDeg)
{
	int i, div = 8;
	r /= div; cx /= div; cy /= div;
	
	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
	
	for(i=startDeg;i<=endDeg;i++)
		glVertex2f(cx+r*sin(2.0*PI*i/360.0),
		cy+r*cos(2.0*PI*i/360.0));

	glEnd();
}

void drawPlanArc(double cx, double cy, float r,
			 int startDeg, int endDeg)
{
	int i, div = 8;
	r /= div; cx /= div; cy /= div;
	
	glColor3f(1,1,1);
	
	glBegin(GL_LINE_STRIP);

	for(i=startDeg;i<=endDeg;i++) {

			glVertex2f(cx+r*sin(2.0*PI*i/360.0),
			cy+r*cos(2.0*PI*i/360.0));		
	}
	glEnd();
}

void lineExp(double cx, double cy, float r,
			 int startDeg, int endDeg)
{
	glColor3f(0,1,0);
	glBegin(GL_LINE_STRIP);

	for(int i=startDeg;i<=endDeg;i++)
		glVertex2f(cx+r*sin(2.0*PI*i/360.0),
		cy+r*cos(2.0*PI*i/360.0));

	glEnd();

}

void drawLine()
{
	glColor3f(0,1,0);
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,8);
	glEnd();
}

void drawQuads()
{
	glColor3f(1 ,0 ,0);
	glBegin(GL_QUAD_STRIP);

	glVertex2f(0,0);

	glColor3f(1 ,1 ,0);
	glVertex2f(2,0);
	glColor3f(0.75 ,0 ,0.75);
	glVertex2f(4,2);
	glColor3f(0.25 ,0.25 ,0.25);
	glVertex2f(2,4);
	glColor3f(0.4 ,0.4 ,0);
	glVertex2f(6,6);
	glEnd();
}

/**********************************

Drawing Circle with GL_TRIANGLE_FAN
			 
**********************************/

void drawTriCircle(double cx, double cy, float r,
			 int startDeg, int endDeg, int design)
{
	int i, div = 8;

	glBegin(GL_TRIANGLE_FAN);

	r /= div; cx /= div; cy /= div;

	switch(design) {
		case 0: glColor3f(1,1,0); break;
		case 1: glColor3f(0.7216,0.7216,0.7216); break;
		case 2: glColor3f(1,0.894,0.4784); break;
		case 3: glColor3f(0.5216,0.761,1); break;
		default: glColor3f(1,1,0); break;
	}

	for(int i=startDeg;i<=endDeg;i++) {
		
		switch(design) {

			case 1:
				if(i==45)
					glColor3f(0.7216,0.7216,0.7216);
				if(i==250)
					glColor3f(0.478,0.478,0.478);
				break;

			case 2: 
				if(i==110)
					glColor3f(1,0.847,0.2392);
				if(i==280)
					glColor3f(1,0.894,0.4784);
				break;
			

			case 3:
				if(i==205)
					glColor3f(0.2,0.8,0);
				if(i==340)
					glColor3f(0.5216,0.761,1);
				break;
		}

		glVertex2f(cx+r*sin(2.0*PI*i/360.0),
		cy+r*cos(2.0*PI*i/360.0));
	}

	glEnd();
}

//void drawPlanet()

void drawSmiley()
{	
	drawTriCircle(0,0,8,0,360, 0);
	drawArc(3,2,2,-90,90);
	drawArc(-3,2,2,-90,90);
	drawArc(0,-2,4,90,270);
}

void smileyCircle()
{
	drawSmiley();
	
	for(int i=0; i<8; i++) {

		for(int i=0; i<8; i++) {
			glTranslatef(0,1.5625,0);
			glScalef(0.55,0.55,1);
			glRotatef(10,0,0,1);
			drawSmiley();
		}

		glLoadIdentity();

		for(int j=i+1; j>0; j--) {
			glRotatef(45,0,0,1);
		}
	}
}

void drawPlanet(double size, int planet)
{
	drawTriCircle(0,0,8*size,0,360, planet);
	drawArc(3*size,2*size,2*size,-90,90);
	drawArc(-3*size,2*size,2*size,-90,90);
	drawArc(0,-2*size,4*size,90,270);
}


/*****************************

Drawing the stars using Random

*****************************/

void drawDots()
{
	glColor3f(1,1,1);
	double randX, randY;
	srand( time(NULL) );
	
	glBegin(GL_POINTS);

	for(int i=0; i<1500; i++) {
		
		if(i%100==0)
			srand(time(NULL) + i);
		randX = (rand() % 250) / 10.0 - 12.5;
		randY = (rand() % 250) / 10.0 - 12.5;
		
		glVertex2f(randX, randY);
	}

	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

	
	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);

	//draw your stuff here
	
	drawDots();
	smileyCircle();

	// Mercury
	drawPlanArc(0,0,36,0,360);
	glPushMatrix();
	glTranslatef( -1.164, -4.347, 0);
	glRotatef(165, 0, 0, 1);
	drawPlanet(0.383, 1);
	glPopMatrix();

	// Venus 
	drawPlanArc(0,0,68.28,0,360);	
	glPushMatrix();
	glTranslatef(8.2442, -2.209, 0);
	glRotatef(255, 0, 0, 1);
	drawPlanet(0.949, 2);
	glPopMatrix(); 
	
	// Earth
	drawPlanArc(0,0,93.103,0,360);
	glPushMatrix();
	glTranslatef(-7.481 , 8.915, 0);
	glRotatef(40, 0, 0, 1);
	drawPlanet(1, 3);
	glPopMatrix();

	glPopMatrix();
	glFlush();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (0, 0, 0, 0);
	glShadeModel (GL_SMOOTH);
}

void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

		case 'a':
			alpha+=10;
			glutPostRedisplay();
			break;

		case 'd':
			alpha-=10;
			glutPostRedisplay();
			break;

		case 'q':
			k+=0.1;
			glutPostRedisplay();
			break;

		case 'e':
			if(k>0.1)
				k-=0.1;
			glutPostRedisplay();
			break;

		case 'z':
			tx-=0.1;
			glutPostRedisplay();
			break;

		case 'c':
			tx+=0.1;
			glutPostRedisplay();
			break;

		case 's':
			ty-=0.1;
			glutPostRedisplay();
			break;

		case 'w':
			ty+=0.1;
			glutPostRedisplay();
			break;

		default:
			break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 1\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}