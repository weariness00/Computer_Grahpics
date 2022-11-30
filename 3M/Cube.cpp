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
	block.vertices = cube_Block->vertices;
	block.face = cube_Block->face;

	collider.tag = "Wall";
	collider.object = this;
	collider.SetBox_OBB(vec3(1));
	vec3 box[2] = { vec3(-0.5), vec3(0.5) };
	collider.SetBox(box, 2);

	//SetActive(false);
}

Cube::~Cube()
{
}

void Cube::Enable()
{
	this->collider.isCollide = true;
}

void Cube::Disable()
{
	this->collider.isCollide = false;
}

void Cube::Init()
{
	Object::Init();

	color.SetRandomColor();

	Render::objectRenedr->AddObject(this);
}

void Cube::Update()
{
	MoveMent();
}

void Cube::MoveMent()
{
	transform.worldPosition += worldSpeed * FrameTime::oneFrame;
	transform.worldRotation += worldRotateSpeed * FrameTime::oneFrame;
}