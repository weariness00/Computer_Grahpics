#include "Sphere.h"

ObjectBlock* Sphere::sphere_Block = nullptr;

Sphere::Sphere()
{
	name = "Shpere";

	if (sphere_Block == nullptr)
	{
		sphere_Block = new ObjectBlock;
		ReadObj((char*)"Sphere.obj", *sphere_Block);
	}

	block.vertIndex = sphere_Block->vertIndex;
	block.faceIndex = sphere_Block->faceIndex;

	block.vertices = sphere_Block->vertices;
	block.vertices_uvs = sphere_Block->vertices_uvs;
	block.vertices_normals = sphere_Block->vertices_normals;

	block.vertexIndices = sphere_Block->vertexIndices;
	block.uvIndices = sphere_Block->uvIndices;
	block.normalIndices = sphere_Block->normalIndices;
}

Sphere::~Sphere()
{
}

void Sphere::Init()
{
	Object::Init();
	Render::objectRenedr->AddObject(this);
}

void Sphere::MoveMent()
{
}

