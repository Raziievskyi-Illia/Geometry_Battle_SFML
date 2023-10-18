#pragma once
#include "Vec2.h"
#include "SFML/Graphics.hpp"

class CTransform
{
public:
	Vec2 pos{ 0.0f, 0.0f };
	Vec2 velocity{0.0f , 0.0f};
	float angle = 0.f; 
	CTransform(const Vec2& p , const Vec2& v , const float a ):pos(p) , velocity(v), angle(a){}

};


class CShape
{
public:
	sf::CircleShape circle; 
	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float outlinethickness) :circle(radius, points)
	{
		circle.setFillColor(fill); 
		circle.setOutlineThickness(outlinethickness);
		circle.setOutlineColor(outline);
		circle.setOrigin(radius, radius); 
	}
};


class CCollision
{
public:
	float radius = 0.f; 
	CCollision(float r):radius(r){}

};


class CScore
{
public:
	int score = 0; 
	CScore(int s):score(s) {}

};


class CLifespan
{
public:
	int total; 
	int remain; 
	CLifespan(int t):total(t) , remain(t){}
};


class CInput
{
public:
	bool up = false; 
	bool down = false;
	bool left = false;
	bool right = false;
	CInput() = default; 
};