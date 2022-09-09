#include "RectangleCollider.h"

RC::RectangleCollider::RectangleCollider()
{
	SetDotRandom();
}

RC::RectangleCollider::~RectangleCollider()
{
}

void RC::RectangleCollider::SetDotRandom()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> posX(0, 800);
	uniform_int_distribution<int> posY(0, 600);
	
	Position random_Pos;
	for (int i = 0; i < 2; i++)
	{
		random_Pos = { posX(gen), posY(gen)};
		dot[i] = random_Pos;
	}
}

void RC::RectangleCollider::PrintDot()
{
	for (int i = 0; i < 2; i++)
	{
		cout << "( " << dot[i].x << ", " << dot[i].y << " )";
	}
}

void RC::RectangleCollider::Move(Position moveIndex)
{
	for (int i = 0; i < 2; i++)
	{
		if ((dot[i].x + moveIndex.x < 0 || dot[i].x + moveIndex.x > 800) ||
			(dot[i].y + moveIndex.y < 0 || dot[i].y + moveIndex.x > 600))
		{
			cout << "도형이 범위를 벗어납니다. 다시 이동해주세요" << endl;
			return;
		}
	}

	for (int i = 0; i < 2; i++)
	{
		dot[i].x += moveIndex.x;
		dot[i].y += moveIndex.y;
 	}
}

void RC::RectangleCollider::CheckCollider(RectangleCollider other)
{
	bool isCollider = false;
	for (int i = 0; i < 2; i++)
	{
		if (dot[0].x >= other.dot[i].x &&
			dot[1].x <= other.dot[i].x)
		{
			isCollider = true;
		}
		else if (dot[0].x <= other.dot[i].x &&
				 dot[1].x >= other.dot[i].x)
		{
			isCollider = true;
		}
		else if (dot[0].y >= other.dot[i].y &&
				 dot[1].y <= other.dot[i].y)
		{
			isCollider = true;
		}
		else if (dot[0].y <= other.dot[i].y &&
				 dot[1].y >= other.dot[i].y)
		{
			isCollider = true;
		}
	}

	if (isCollider)
		cout << "도형이 충돌했습니다." << endl;
}