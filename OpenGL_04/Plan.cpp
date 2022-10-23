#include "Plan.h"

Plan::Plan()
{
	ReadObj((char*)"Plan.obj", block);
}

Plan::~Plan()
{
}

void Plan::Draw()
{
	if (!isActive)
		return;

	MoveMent();

	Object::Draw();
}

void Plan::MoveMent()
{
	transform.worldPosition += speed;
	transform.worldRotation = (transform.worldRotation + rotateSpeed);
}


void Plan::Init()
{
	Object::Init();
}