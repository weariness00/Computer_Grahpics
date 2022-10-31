#include "Circle.h"

Circle::Circle()
{
	radius = 1.0f;
	isActive = true;
}

Circle::~Circle()
{
}

void Circle::Init()
{
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_LINE);
}

void Circle::Draw()
{
	if (!isActive)
		return;

	MoveMent();
	Object::SetMatrix();


	gluDisk(obj, radius, radius, 100, 1);
}

void Circle::MoveMent()
{
	transform.worldPivot += worldPivotSpeed;
	transform.worldRotation += rotateSpeed;
	transform.worldPosition += worldSpeed;
	transform.localRotation += localRotateSpeed;
}

