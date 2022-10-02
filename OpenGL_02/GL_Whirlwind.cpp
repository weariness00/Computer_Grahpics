#include "GL_Whirlwind.h"

GL_Whirlwind::GL_Whirlwind() : Object()
{
	OnDrawAnimaiton = false;
	DrawAniCount = 0;

	Radius = 100;
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
	InitPoint();
	for (int i = 0; i < pointCount; i++)
	{
		Real_Point[i] = RealPosition(Point[i] + transform.Position);
	}
	return Real_Point;
}

void GL_Whirlwind::InitPoint()
{
	Vector2 pos ={0,0};
	Vector2 radius = {0,0};
	float lenth;
	float setha = 360/pointCount * 2;
	
	radius = { -Radius * cos((transform.Rotation.x) * (PI / 180)), -Radius * sin((transform.Rotation.x) * (PI / 180)) };
	for (int i = 0; i < pointCount / 2; i++)
	{
		lenth = (Radius / pointCount * 2) * i;

		float radian = (setha * i + 90 + UpDown * transform.Rotation.x/ 5) *  (PI / 180) * 5;
		pos = { float(lenth * cos(radian)), float(UpDown * lenth * sin(radian))};
		Point[i] = radius + pos;
	}

	radius = { Radius * cos((transform.Rotation.x) * (PI / 180)),Radius * sin((transform.Rotation.x) * (PI / 180)) };
	for (int i = pointCount / 2; i >= 0; i--)
	{
		lenth = (Radius / pointCount * 2) * i;

		float radian = (setha * i - 90 + UpDown * transform.Rotation.x/ 5) * (PI / 180) * 5;
		pos = { float(lenth * cos(radian)), float(UpDown * lenth * sin(radian))};
		Point[pointCount - i] = radius + pos;
	}
}

void GL_Whirlwind::RandomWhirwindDir()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> randDir(-2, 2);

	UpDown = 1;

	if (randDir(gen) >= 0)
	{
		UpDown = -1;
	}
}