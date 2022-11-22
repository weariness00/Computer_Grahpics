#include "Cube.h"

ObjectBlock* Cube::cube_Block = nullptr;

Cube::Cube()
{
	name = "Cube";

	if (cube_Block == nullptr)
	{
		cube_Block = new ObjectBlock;
		ReadObj((char*)"Cube.obj", *cube_Block);
	}

	block.vertIndex = cube_Block->vertIndex;
	block.faceIndex = cube_Block->faceIndex;
	block.vertex = cube_Block->vertex;
	block.face = cube_Block->face;

	isRigidXY = false;
}

Cube::~Cube()
{
}

void Cube::Update()
{
	MoveMent();
	isRigidXY = !isRigidXY;
	transform.worldPosition += rigidBody.UpdateRigid() * FrameTime::oneFrame;
	SetMatrix();
}

void Cube::Init()
{
	Object::Init();

	collider.InitTransform(transform);
	collider.SetBox(block.vertex, block.vertIndex);
	collider.tag = "Object";

	Render::mainRender->AddObject(this);
}

void Cube::MoveMent()
{
	transform.worldPosition += worldSpeed;
	transform.worldRotation += worldRotateSpeed;
}

void Cube::Collision()
{
	if (!collider.isCollide)
		return;

	collider.CheckCollision();

	for (auto& other : collider.onCollideList)
	{
		if (other->tag == "Wall_X")
		{
			transform.worldPosition.x -= rigidBody.UpdateRigid().x * FrameTime::oneFrame;
		}
		else if (other->tag == "Wall_Y")
		{
			transform.worldPosition.y -= rigidBody.UpdateRigid().y * FrameTime::oneFrame;
		}
	}

}