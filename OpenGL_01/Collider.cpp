#include "Collider.h"

Collider::Collider()
{
	isAllCollide = false;
	isMouseCollide = false;
	isWindowCollide = false;
}

Collider::~Collider()
{
}

void Collider::InitCollider(Vector2 collider[])
{
	xCollider = int(collider[1].x - collider[0].x) + 1;
	yCollider = int(collider[1].y - collider[0].y) + 1;

	Collider_Box = new Vector2*[yCollider];
	isCollide = new bool * [yCollider];
	for (int y = 0; y < yCollider; y++)
	{
		Collider_Box[y] = new Vector2[xCollider];
		isCollide[y] = new bool[xCollider];
	}

	for (int y = 0; y < yCollider; y++)
	{
		for (int x = 0; x < xCollider; x++)
		{
			Collider_Box[y][x] = { collider[0].x + x,collider[0].y + y };
			isCollide[y][x] = true;
		}
	}
}

void Collider::InitTransform(Transform& t)
{
	transform = &t;
}

bool Collider::OnMouseCollide(Vector2 mousePos)
{
	Vector2 real_pos = Coordinate(mousePos);

	isMouseCollide = false;

	for (int y = 0; y < yCollider - 1; y++)
	{
		for (int x = 0; x < xCollider - 1; x++)
		{
			if (!isCollide[y][x])
				continue;

			if (real_pos.x >= Collider_Box[y][x].x * transform->Scale.x + transform->Pivot.x &&
				real_pos.x <= Collider_Box[y + 1][x + 1].x * transform->Scale.x + transform->Pivot.x &&
				real_pos.y >= Collider_Box[y][x].y * transform->Scale.y + transform->Pivot.y &&
				real_pos.y <= Collider_Box[y + 1][x + 1].y * transform->Scale.y + transform->Pivot.y)
			{
				isMouseCollide = true;
				return isMouseCollide;
			}
		}
	}

	/*if (real_pos.x >= Collider_Box[0][0].x * transform->Scale.x + transform->Pivot.x &&
		real_pos.x <= Collider_Box[yCollider - 1][xCollider - 1].x * transform->Scale.x + transform->Pivot.x &&
		real_pos.y >= Collider_Box[0][0].y * transform->Scale.y + transform->Pivot.y &&
		real_pos.y <= Collider_Box[yCollider - 1][xCollider - 1].y * transform->Scale.y + transform->Pivot.y )
	{
		isMouseCollide = true;
		return isMouseCollide;
	}*/

	return isMouseCollide;
}

bool Collider::WindowColider()
{
	Vector2 window_Pos[2];
	window_Pos[0] = Coordinate({0,0});
	window_Pos[1] = Coordinate({(float)windowSize_W, (float)windowSize_H});

	isWindowCollide = false;

	if (Collider_Box[0][0].x * transform->Scale.x + transform->Pivot.x <= window_Pos[0].x)
		isWindowCollide = true;
	else if (Collider_Box[yCollider - 1][xCollider - 1].x * transform->Scale.x + transform->Pivot.x >= window_Pos[1].x)
		isWindowCollide = true;
	else if (Collider_Box[0][0].y * transform->Scale.y + transform->Pivot.y <= window_Pos[0].y)
		isWindowCollide = true;
	else if (Collider_Box[yCollider - 1][xCollider - 1].y * transform->Scale.y + transform->Pivot.y >= window_Pos[1].y)
		isWindowCollide = true;

	return isWindowCollide;
}

//지우개 전용
bool Collider::OnCollider(const Collider& other)
{
	bool check = false;
	Vector2 checkPos[2];

	for (int y = 0; y < yCollider - 1; y++)
	{
		for (int x = 0; x < xCollider - 1; x++)
		{
			if (!other.isCollide[y][x])
				continue;

			checkPos[0] = other.Collider_Box[y][x] * other.transform->Scale + other.transform->Pivot;
			checkPos[1] = other.Collider_Box[y + 1][x + 1] * other.transform->Scale + other.transform->Pivot;
			check = CheckCollide(checkPos);
			other.isCollide[y][x] = !check;
			other.transform->isAcitve[y][x] = !check;
		}
	}

	return check;
}

bool Collider::CheckCollide(const Vector2 one[])
{
	for (int y = 0; y < yCollider - 1; y++)
	{
		for (int x = 0; x < xCollider - 1; x++)
		{
			if (one[0].x >= Collider_Box[y][x].x * transform->Scale.x + transform->Pivot.x &&
				one[0].x <= Collider_Box[y + 1][x + 1].x * transform->Scale.x + transform->Pivot.x)
			{
				if (one[0].y >= Collider_Box[y][x].y * transform->Scale.y + transform->Pivot.y &&
					one[0].y <= Collider_Box[y + 1][x + 1].y * transform->Scale.y + transform->Pivot.y)
					return true;
				else if(one[1].y >= Collider_Box[y][x].y * transform->Scale.y + transform->Pivot.y &&
					one[1].y <= Collider_Box[y + 1][x + 1].y * transform->Scale.y + transform->Pivot.y)
					return true;
			}
			else if (one[1].x >= Collider_Box[y][x].x * transform->Scale.x + transform->Pivot.x &&
					one[1].x <= Collider_Box[y + 1][x + 1].x * transform->Scale.x + transform->Pivot.x)
			{
				if (one[0].y >= Collider_Box[y][x].y * transform->Scale.y + transform->Pivot.y &&
					one[0].y <= Collider_Box[y + 1][x + 1].y * transform->Scale.y + transform->Pivot.y)
					return true;
				else if (one[1].y >= Collider_Box[y][x].y * transform->Scale.y + transform->Pivot.y &&
					one[1].y <= Collider_Box[y + 1][x + 1].y * transform->Scale.y + transform->Pivot.y)
					return true;
			}
		}
	}

	return false;
}
