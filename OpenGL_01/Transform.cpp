#include "Transform.h"

Transform::Transform() : Mesh()
{
	Pivot = Init_Pivot = { 0,0 };
	Scale = { 1,1 };
}

Transform::Transform(Vector2 pos, Vector2 scale) : Mesh()
{
	Init_Pivot = pos;
	SetPosition(pos);
	SetScale(scale);
}

Transform::~Transform()
{
}

void Transform::Update()
{
	SetVertax();
}

void Transform::InitPivot(Vector2 pivot)
{
	Init_Pivot = pivot;
	SetPosition(Init_Pivot);
}

void Transform::SetPosition(Vector2 pos)
{
	Pivot = pos;
}

void Transform::SetScale(Vector2 scale)
{
	Scale = scale;
}

void Transform::SetScale()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> randomPos(-1, 1);

	Vector2 randomSacle = { (float)randomPos(gen), (float)randomPos(gen) };

	randomSacle = randomSacle + Scale;

	randomSacle.x = (randomSacle.x <= 0) ? 1 : randomSacle.x;
	randomSacle.y = (randomSacle.y <= 0) ? 1 : randomSacle.y;

	SetScale(randomSacle);
}

void Transform::ResetPosition()
{
	SetPosition(Init_Pivot);
}

void Transform::SetVertax()
{
	for (int y = 0; y < yDot; y++)
	{
		for (int x = 0; x < xDot; x++)
		{
			Real_MeshVertax[y][x] = RealPosition(meshVertax[y][x] * Scale + Pivot);
		}
	}
}
