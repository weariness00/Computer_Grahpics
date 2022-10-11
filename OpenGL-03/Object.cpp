#include "Object.h"

Object::Object()
{
	name = "UnName";
	collider.InitTransform(transform);

	isActive = false;
}

Object::~Object()
{
}

void Object::Update()
{
	transform.Update();
}