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
	block.vertices_uvs = cube_Block->vertices_uvs;
	block.vertices_normals = cube_Block->vertices_normals;

	block.vertexIndices = cube_Block->vertexIndices;
	block.uvIndices = cube_Block->uvIndices;
	block.normalIndices = cube_Block->normalIndices;
}

Cube::~Cube()
{
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