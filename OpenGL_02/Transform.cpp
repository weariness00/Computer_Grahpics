#include "Transform.h"

Transform::Transform()
{
	Position = { 0,0 };
	Pivot = { 0,0 };
	Scale = { 1,1 };
}

Transform::Transform(Vector2 pos, Vector2 scale)
{
	Position = pos;
	Scale = scale;
}

Transform::~Transform()
{
}

void Transform::Update()
{
	//SetVertax();
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

	Scale = randomSacle;
}

//void Transform::SetVertax()
//{
//	for (int y = 0; y < yDot; y++)
//	{
//		for (int x = 0; x < xDot; x++)
//		{
//			Real_MeshVertax[y][x] = RealPosition(meshVertax[y][x] * Scale + Pivot);
//		}
//	}
//}
