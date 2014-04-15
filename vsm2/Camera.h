#ifndef CAMERA_H
#define CAMERA_H
#include "f3.h"
class Camera{
public:
	f3* pos;
	f3* rot;
	Camera(){}
	Camera(float x,float y, float z, float rotx, float roty, float rotz);
	f3* getDirection();
	f3* getRight();
	void setMatrices();
};
#endif	