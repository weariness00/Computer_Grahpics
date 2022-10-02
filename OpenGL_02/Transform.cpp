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

void Transform::SetRandomRotate()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> randomPos(0, 360);

	Rotation = { (float)randomPos(gen), 0 };
}

void Transform::LookAt(float speed)
{
	Position.x += speed * float(cos((Rotation.x + 90) * (PI / 180)));
	Position.y += speed * float(sin((Rotation.x + 90) * (PI / 180)));
}
