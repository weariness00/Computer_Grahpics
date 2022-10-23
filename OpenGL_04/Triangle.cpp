#include "Triangle.h"

Triangle::Triangle()
{
	ReadObj((char*)"Triangle.obj", block);
}

Triangle::~Triangle()
{
}

void Triangle::Init()
{
	Object::Init();
}


void Triangle::Draw()
{
	if (!isActive)
		return;

	MoveMent();

	Object::Draw();
}

void Triangle::MoveMent()
{
	transform.worldPosition += speed;
	transform.worldRotation += rotateSpeed;
}

