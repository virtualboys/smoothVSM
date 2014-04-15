
#ifndef f3_h
#define f3_h

struct f3 { 
	float x; float y; float z; 

	f3(){}

	f3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}	

	f3 operator*(float f) const;
	f3 operator+(const f3 &other) const;
	f3 operator-(const f3 &other) const;
	float dot(const f3 &other) const;
	float magnitude() const;
	void normalize();
	void add(f3* vec);
	void sub(f3* vec);
	void multscalar(float s);
	f3 cross(const f3 &other) const;
};

#endif