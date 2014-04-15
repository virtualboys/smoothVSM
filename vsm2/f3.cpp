#include "f3.h"
#include <cmath>

	f3 f3::operator*(float f) const {
		f3 result = *this;    
		result.x *= f;
		result.y *= f;
		result.z *= f;
		return result;              
	}

	f3 f3::operator+(const f3 &other) const {
		f3 result = *this;    
		result.x += other.x;
		result.y += other.y;
		result.z += other.z;
		return result;              
	}

	f3 f3::operator-(const f3 &other) const {
		f3 result = *this;    
		result.x -= other.x;
		result.y -= other.y;
		result.z -= other.z;
		return result;              
	}

	float f3::dot(const f3 &other) const {
		return x * other.x + y * other.y + z * other.z;
	}
	void f3::add(f3* vec){
		x+=vec->x;
		y+=vec->y;
		z+=vec->z;
	}
	void f3::sub(f3* vec){
		x-=vec->x;
		y-=vec->y;
		z-=vec->z;
	}
	void f3::multscalar(float s){
		x*=s;
		y*=s;
		z*=s;
	}
	float f3::magnitude() const {
		return sqrt(x * x + y * y + z * z);
	}

	void f3::normalize() {
		float mag = magnitude();
		x /= mag;
		y /= mag;
		z /= mag;
	}

	f3 f3::cross(const f3 &other) const{
		float xc = y * other.z - z * other.y;
		float yc = z * other.x - x * other.z;
		float zc = x * other.y - y * other.x;
		return f3(xc,yc,zc);
	}