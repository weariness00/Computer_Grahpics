#include "GL_Whirlwind.h"

GL_Whirlwind::GL_Whirlwind() : Object()
{
	Radius = 30;
	speed = 5;

	pointCount = 200;
	Point = new Vector2[pointCount];
	Real_Point = new Vector2[pointCount];

	InitPoint();
}

GL_Whirlwind::~GL_Whirlwind()
{
}

Vector2* GL_Whirlwind::GetDot()
{
	for (int i = 0; i < pointCount; i++)
	{
		Real_Point[i] = RealPosition(Point[i] + transform.Position);
	}
	return Real_Point;
}

void GL_Whirlwind::InitPoint()
{
	Vector2 pos ={0,0};
	Vector2 radius;
	float lenth;

	radius = { -Radius, 0};
	for (int i = 0; i < pointCount / 2; i++)
	{
		lenth = (Radius / pointCount * 2) * (i + 1);

		pos = { float(lenth * cos((360 / (i + 1)) * (PI / 180))), float(lenth * sin((360 / (i + 1)) * (PI / 180))) };
		Point[i] = Radius + pos;
	}

	radius = { Radius, 0 };
	for (int i = pointCount / 2; i < pointCount; i++)
	{
		lenth = (Radius / pointCount * 2) * (i + 1);
		pos = { float(lenth * cos((360 / (i + 1)) * (PI / 180))), float(lenth * sin((360 / (i + 1)) * (PI / 180))) };
		Point[i] = Radius + pos;
	}
}