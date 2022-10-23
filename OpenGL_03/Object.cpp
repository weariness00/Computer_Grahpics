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

void Object::ExpensionScale()
{
	if (transform.Scale.x >= now_S)
		imagnaryNumber = -1;
	else if (transform.Scale.x <= 0)
		imagnaryNumber = 1;

	transform.Scale += imagnaryNumber * 0.01f;
}