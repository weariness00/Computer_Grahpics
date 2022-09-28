#include "GL_Rectangle.h"

GL_Rectangle::GL_Rectangle() : Object()
{
	Start_Dot[0] = { -5, -5 };
	Start_Dot[1] = { 5, 5 };
	transform.SetScale({ 10,10 });

	Dot[0] = Start_Dot[0];
	Dot[1] = Start_Dot[1];

	transform.InitVertax(Dot);
	transform.SetPosition({ 0,0 });
	collider.InitCollider(Dot);
}

GL_Rectangle::~GL_Rectangle()
{
}

void GL_Rectangle::Update()
{
	Object::Update();

	Draw();
}

void GL_Rectangle::Draw()
{
	Vector2** dot = transform.GetRealMeshVertax();
	Vector2 maxWindow = window_RealPos * transform.Scale;
	glColor3f(color.R, color.G, color.B);

	for (int y = 0; y < transform.yDot - 1; y++)
	{
		for (int x = 0; x < transform.xDot - 1; x++)
		{
			if (!transform.isAcitve[y][x])
				continue;

			glRectf(dot[y][x].x, -dot[y][x].y, dot[y + 1][x + 1].x, -(dot[y + 1][x + 1].y));
		}
	}
}