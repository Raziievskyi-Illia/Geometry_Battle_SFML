#include "Vec2.h"

bool Vec2::operator==(const Vec2& other)
{
	return (x == other.x && y == other.y);
}

bool Vec2::operator!=(const Vec2& other)
{
	return (x != other.x && y != other.y);
}

Vec2 Vec2::operator+(const Vec2& other)
{
	return Vec2(x + other.x, y + other.y); 
}

Vec2 Vec2::operator-(const Vec2& other)
{
	return Vec2(x-other.x , y - other.y);
}

Vec2 Vec2::operator/(const float n)
{
	return Vec2(x/n , y/n);
}

Vec2 Vec2::operator*(const float n)
{
	return Vec2(x*n , y*n);
}

void Vec2::operator+=(const Vec2& other)
{
	x += other.x; 
	y += other.y; 
}

void Vec2::operator-=(const Vec2& other)
{
	x -= other.x;
	y -= other.y;	
}

void Vec2::operator*=(const float value)
{
    x += value; 
    y *= value; 
}


void Vec2::normalize()
{
    float length = sqrtf(this->x * this->x + this->y * this->y);
    if (length != 0)
    {
        this->x /= length;
        this->y /= length;
    }
    else
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }
}
