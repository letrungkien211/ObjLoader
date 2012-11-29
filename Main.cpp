/*
 *  SierpinskyMain.cpp
 *
 *  Created on: Aug 11, 2012
 *      Author: letrungkien7
 */
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <GL/glut.h>
#include <eigen3/Eigen/Core>
#include <vector>
#include <exception>
#include <cstring>
#include "Loader.h"

using namespace std;
using namespace Eigen;

typedef Vector3d Point;
typedef Vector3d Color;

GLsizei wh = 1000;
GLsizei ww = 1000;

double pitch =0, yaw =0;
double mouse_x, mouse_y;

int mouse_button;
double fovy=45, near=0, far=1000;
double dist = -200;

Loader loader[2];

void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,1.0);
	glLoadIdentity();

	glTranslated(0,0,dist);

	glRotated(pitch, 1,0,0);
	glRotated(yaw,0,1,0);

	loader[0].Draw();
	loader[1].Draw();

	glFlush();
}

void reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)h/(double)w, 0, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(0,0,-200);
	glRotated(45, 1,1,1);

}

void mouse(int button, int state, int x, int y){
	mouse_button = button;
	mouse_x = x;
	mouse_y = y;
}

void motion(int x, int y)
{
	switch(mouse_button){
	case GLUT_LEFT_BUTTON:
		if( x==mouse_x && y==mouse_y ) return;
		yaw -= (GLfloat)( x - mouse_x ) /10.0;
		pitch -= (GLfloat)( y - mouse_y ) /10.0;
		break;
	case GLUT_RIGHT_BUTTON:
		if( y==mouse_y ) return;
		if( y < mouse_y ) dist += (GLfloat)(mouse_y - y);
		else dist -= (GLfloat)(y - mouse_y);
		if( -dist < near ) dist = -near;
		if( -dist > far ) dist = -far;
		break;
	}
	mouse_x = x;
	mouse_y = y;
	glutPostRedisplay();
}

void keyboard(unsigned char c, int x, int y){
	switch(c){
	case 27:
		exit(1)	;
		break;
	default:
		break;
	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww, wh) ;
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	char a[20] = "trumpet.obj", b[20] = "teapot.obj";

	if(argc>1){
		strcpy(a, argv[1]);
		if(argc>2)
			strcpy(a, argv[2]);
	}

	loader[0].Load(a);
	loader[1].Load(b);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape) ;
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop() ;
	return 0;
}

