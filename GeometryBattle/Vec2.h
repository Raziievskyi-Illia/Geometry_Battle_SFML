#pragma once
#include <math.h>
class Vec2
{
public:
	float x = 0; 
	float y = 0; 
	Vec2() = default; 
	Vec2(float vx, float vy) : x(vx), y(vy){}


	bool operator ==(const Vec2& other); 
	bool operator !=(const Vec2& other); 
	Vec2 operator +(const Vec2& other); 
	Vec2 operator - (const Vec2& other);
	/*Vec2 operator / (const Vec2& other); 
	Vec2 operator * (const Vec2& other);*/
	Vec2 operator / (const float n);
	Vec2 operator * (const float n);

	void operator +=(const Vec2& other); 
	void operator -=(const Vec2& other);
	void operator *=(const float value); 

	void normalize(); 


	

};

 