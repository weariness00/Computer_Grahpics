#include "Cube.h"

Cube::Cube()
{
	ReadObj((char*)"Cube.obj", block);
	isActive = true;

	worldSpeed = worldRotateSpeed = vec3(0, 0, 0);
}

Cube::~Cube()
{
}


void Cube::Init()
{
	Object::Init();
}

void Cube::Draw()
{
	if (!isActive)
		return;

	MoveMent();

	Object::SetMatrix();

	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, block.vertIndex);
	glDrawElements(GL_TRIANGLES, block.faceIndex * 3, GL_UNSIGNED_SHORT, 0);
}

void Cube::MoveMent()
{
	transform.worldPosition += worldSpeed;
	transform.worldRotation += worldRotateSpeed;
}

