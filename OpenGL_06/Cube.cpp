#include "Cube.h"

Cube::Cube() : Mesh(this)
{
	zRotate = 0;
	worldSpeed = worldRotateSpeed = vec3(0, 0, 0);
}

Cube::~Cube()
{
}


void Cube::Init()
{
	obj = new OBJ;
	obj->ReadObj((char*)"Cube.obj");
	Render::meshtRender->AddObject(this);
}

void Cube::Update()
{
	MoveMent();
}

void Cube::MoveMent()
{
	transform.worldPosition += worldSpeed;
	transform.worldRotation += worldRotateSpeed;
}

