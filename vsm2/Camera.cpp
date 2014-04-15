#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include "Camera.h"
#include "f3.h"
#include <math.h>
#include <iostream>



	Camera::Camera(float x,float y, float z, float rotx, float roty, float rotz){
		pos = new f3(x,y,z);
		rot = new f3(rotx,roty,rotz);
	}

f3* Camera::getDirection(){
	f3* forward = new f3();
	forward->x=cos(rot->y)*sin(rot->x);
	forward->y=sin(rot->y);
	forward->z=cos(rot->y)*cos(rot->x);
	return forward;
}

f3* Camera::getRight(){
	f3* right= new f3();
	right->x=sin(rot->x - 3.14f/2.0f);
	right->y=0;
    right->z=cos(rot->x - 3.14f/2.0f);
	return right;
}

void Camera::setMatrices(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50.0, 1.0, .1f, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	f3* forward= getDirection();
	forward->add(pos);
    
	gluLookAt(pos->x, 0.0, pos->z, //pos
		forward->x, forward->y, forward->z, //lookatpos
         0.0, 1.0, 0.0); //up
}