#include "Plan.h"

ObjectBlock* Plan::plan_Block = nullptr;

Plan::Plan()
{
	name = "Plan";

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

void Plan::Update()
{
	if (!isActive)
		return;
	 
	MoveMent();

	SetMatrix();
}

void Plan::MoveMent()
{
	transform.worldPosition += worldSpeed;
	transform.worldRotation = (transform.worldRotation + worldRotateSpeed);
}


void Plan::Init()
{
	Object::Init();
	Render::mainRender->AddObject(this);
}