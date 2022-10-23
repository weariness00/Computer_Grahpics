#include "Transform.h"

Transform::Transform()
{
	worldPosition = localPosition = worldPivot = localPivot = vec3(0);
	worldScale = localScale = vec3(1);
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

	vec3 randomSacle = { (float)randomPos(gen), (float)randomPos(gen),  (float)randomPos(gen) };

	randomSacle = randomSacle + worldScale;

	randomSacle.x = (randomSacle.x <= 0) ? 1 : randomSacle.x;
	randomSacle.y = (randomSacle.y <= 0) ? 1 : randomSacle.y;

	worldScale = randomSacle;
}

void Transform::SetRandomRotate()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> randomPos(0, 360);

	worldRotation = { (float)randomPos(gen), 0 , 0};
}

void Transform::LookAt(float speed)
{
	worldPosition.x += speed * float(cos((worldRotation.x + 90) * (PI / 180)));
	worldPosition.y += speed * float(sin((worldRotation.x + 90) * (PI / 180)));
}
