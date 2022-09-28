#include "GL_Triangle.h"

GL_Triangle::GL_Triangle() : Object()
{
	Dot[0] = { 0, 50 };
	Dot[1] = { -50, 0 };
	Dot[2] = { 0, -50 };
	transform.Pivot = { 0,0 };
	transform.Scale = { 1,1 };
	transform.Rotation = { 0,0 };
}

GL_Triangle::~GL_Triangle()
{
}

void GL_Triangle::Update()
{
}

Vector2* GL_Triangle::GetDot()
{
	Vector2 real_Dot[3];
	for (int i = 0; i < 3; i++)
	{
		real_Dot[i] = RealPosition(Dot[i] * transform.Scale);
	}

	return real_Dot;
}

Color* GL_Triangle::GetColor()
{
	Color c[3];

	for (int i = 0; i < 3; i++)
	{
		c[i] = color;
	}
	return c;
}
