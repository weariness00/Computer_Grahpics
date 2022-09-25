#include "GL_Rectangle.h"

GL_Rectangle::GL_Rectangle() : Object()
{
	Start_Dot[0] = { -10, -10 };
	Start_Dot[1] = { 10, 10 };
	transform.SetScale({ 1,1 });

	Dot[0] = Start_Dot[0] * transform.Scale;
	Dot[1] = Start_Dot[1] * transform.Scale;

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

			glRectf(dot[y][x].x, -dot[y][x].y, dot[y][x].x + maxWindow.x, -(dot[y][x].y + maxWindow.y));
		}
	}
}

//bool GL_Rectangle::Collide(Vector2 pos)
//{
//	Vector2 real_pos = Coordinate(pos);
//
//	isCollide = false;
//
//	if (real_pos.x >= Dot[0].x &&
//		real_pos.x <= Dot[1].x &&
//		real_pos.y >= Dot[0].y &&
//		real_pos.y <= Dot[1].y)
//	{
//		isCollide = true;
//	}
//
//	return isCollide;
//}


//void GL_Rectangle::SetPosition(Vector2 pos)
//{
//	pivot_Pos = pos;
//	for (int i = 0; i < 2; i++)
//	{
//		dot[i] = Start_Dot[i] * scale[i] + pivot_Pos;
//	}
//}
//
//void GL_Rectangle::SetScale(Vector2 s[2])
//{
//	for (int i = 0; i < 2; i++)
//	{
//		scale[i] = s[i];
//	}
//}
//
//void GL_Rectangle::SetScale()
//{
//	random_device rd;
//	mt19937 gen(rd());
//	uniform_real_distribution<float> randomX (-0.1f, 0.1f);
//	uniform_real_distribution<float> randomY(-0.1f, 0.1f);
//
//	Vector2 randomSacle[2] = {
//		{randomX(gen), randomY(gen)},
//		{randomX(gen), randomY(gen)}
//	};
//
//	for (int i = 0; i < 2; i++)
//	{
//		randomSacle[i] = randomSacle[i] + scale[i];
//	}
//
//	SetScale(randomSacle);
//}
//
//void GL_Rectangle::InitStartPivot(Vector2 pivot)
//{
//	StartPivot = pivot;
//	pivot_Pos = StartPivot;
//}
//
//void GL_Rectangle::ResetPosition()
//{
//	pivot_Pos = StartPivot;
//	//GL_Rectangle::SetPosition(pivot_Pos);
//}