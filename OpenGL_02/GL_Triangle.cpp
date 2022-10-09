#include "GL_Triangle.h"

GL_Triangle::GL_Triangle() : Object()
{
	radius = 10;
	speed = 1;
	transform.Pivot = { 0,0 };
	transform.Scale = { 1,1 };
	transform.Rotation = { 0,0 };

	Dot[0] = { float(2 * radius* cos((0 + 90) * (PI / 180))), float(2 * radius * sin((0 + 90) * (PI / 180))) };
	Dot[1] = { float(radius * cos((120 + 90) * (PI / 180))), float(radius * sin((120 + 90) * (PI / 180))) };
	Dot[2] = { float(radius * cos((-120 + 90) * (PI / 180))), float(radius * sin((-120 + 90) * (PI / 180))) };

	Vector2 d[2];
	d[0] = { -Dot[1].x,Dot[0].y };
	d[1] = Dot[2];
	collider.SetCollider(d);

	zigzag_Radius = 0;
}

GL_Triangle::~GL_Triangle()
{
}

void GL_Triangle::Update()
{
}

Vector2* GL_Triangle::GetDot()
{
	Dot[0] = { float(3*radius * cos((0 + 90 + transform.Rotation.x) * (PI / 180))), float(3 *radius * sin((0 + 90 + transform.Rotation.x) * (PI / 180))) };
	Dot[1] = { float(radius * cos((120 + 90 + transform.Rotation.x) * (PI / 180))), float(radius * sin((120 + 90+ transform.Rotation.x) * (PI / 180))) };
	Dot[2] = { float(radius * cos((-120 + 90 + transform.Rotation.x) * (PI / 180))), float(radius * sin((-120 + 90 + transform.Rotation.x) * (PI / 180))) };
	collider.SetCollider(Dot);

	for (int i = 0; i < 3; i++)
	{
		real_Dot[i] = RealPosition(Dot[i] * transform.Scale + transform.Position);
	}
	return real_Dot;
}

Color* GL_Triangle::GetColor()
{
	for (int i = 0; i < 3; i++)
	{
		c[i] = color;
	}

	return c;
}

void GL_Triangle::MoveWindow()
{
	transform.LookAt((float)speed);
	GetDot();

	collider.WindowColider();

	if (collider.isWindowCollide)
	{
		transform.LookAt(-(float)speed);
		SetRandomSpeed();
		transform.SetRandomRotate();
		GetDot();
	}
}

void GL_Triangle::SetRandomSpeed()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> radnomSpeed(2, 4);

	speed = radnomSpeed(gen);
}

void GL_Triangle::SetRandomZigZagRadius()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> radnomRadius(0, 360);
	uniform_int_distribution<int> radnomSpeed(2, 4);

	zigzag_Radius = (float)radnomRadius(gen);
	zigzag_Count = 0;
	zigzag_Speed = radnomSpeed(gen);
	isZigZagCountMax = false;
}

void GL_Triangle::MoveZigZag()
{
	transform.Rotation = { zigzag_Radius,0 };

	if (zigzag_Count == 30)
	{
		int increase_decrease;
		if (isZigZagCountMax)
			increase_decrease = 90;
		else
			increase_decrease = -90;

		isZigZagCountMax = !isZigZagCountMax;
		zigzag_Radius = increase_decrease + zigzag_Radius;
		zigzag_Count = 0;
	}

	zigzag_Count++;
	transform.LookAt((float)zigzag_Speed);
	GetDot();
}