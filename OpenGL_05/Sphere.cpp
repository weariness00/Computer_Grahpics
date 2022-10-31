#include "Sphere.h"

Sphere::Sphere()
{
	isActive = true;
}

Sphere::~Sphere()
{
}

void Sphere::Init()
{
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
}

void Sphere::Draw()
{
	if (!isActive)
		return;

	MoveMent();

	Object::SetMatrix();


	gluSphere(obj, 1.0, 30, 30);
}

void Sphere::SetDrawStyle(bool value)
{
	if (value)
		gluQuadricDrawStyle(obj, GLU_LINE);
	else
		gluQuadricDrawStyle(obj, GLU_FILL);
}

void Sphere::MoveMent()
{
	transform.worldRotation += rotateSpeed;
	transform.localRotation += localRotateSpeed;
}

