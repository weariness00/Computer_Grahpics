#include "Object.h"

Object::Object()
{
	name = "UnName";
	color = { 1,1,1,1 };
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

void Object::SetColor(Color c)
{
	color = c;
}

void Object::SetColor()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<GLclampf> randomcolor(0.0f, 1.0f);

	Color c = { randomcolor(gen),randomcolor(gen) ,randomcolor(gen), 1.0f};
	SetColor(c);
}