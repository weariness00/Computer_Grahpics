#include "Line.h"


Line::Line()
{
	ReadObj((char*)"Line.obj", block);
}

Line::~Line()
{
}

void Line::Init()
{
	Object::Init();
}


void Line::Draw()
{
	if (!isActive)
		return;

	MoveMent();

	Object::lineDraw();
}

void Line::MoveMent()
{
	transform.worldPosition += speed;
	transform.worldRotation += rotateSpeed;
}

