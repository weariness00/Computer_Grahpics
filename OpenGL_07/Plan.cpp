#include "Plan.h"

ObjectBlock* Plan::plan_Block = nullptr;

Plan::Plan()
{
	if (plan_Block == nullptr)
	{
		plan_Block = new ObjectBlock;
		ReadObj((char*)"Plan.obj", *plan_Block);
	}

	block.vertIndex = plan_Block->vertIndex;
	block.faceIndex = plan_Block->faceIndex;
	block.vertex = plan_Block->vertex;
	block.face = plan_Block->face;
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