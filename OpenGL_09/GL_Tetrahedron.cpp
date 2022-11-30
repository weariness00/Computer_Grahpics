#include "GL_Tetrahedron.h"

ObjectBlock* GL_Tetrahedron::tetrahedron_Block = nullptr;

GL_Tetrahedron::GL_Tetrahedron()
{
	if (tetrahedron_Block == nullptr)
	{
		tetrahedron_Block = new ObjectBlock;
		ReadObj((char*)"Tetrahedron.obj", *tetrahedron_Block);
	}
	block.vertIndex = tetrahedron_Block->vertIndex;
	block.faceIndex = tetrahedron_Block->faceIndex;

	block.vertices = tetrahedron_Block->vertices;
	block.vertices_uvs = tetrahedron_Block->vertices_uvs;
	block.vertices_normals = tetrahedron_Block->vertices_normals;

	block.vertexIndices = tetrahedron_Block->vertexIndices;
	block.uvIndices = tetrahedron_Block->uvIndices;
	block.normalIndices = tetrahedron_Block->normalIndices;
}
GL_Tetrahedron::~GL_Tetrahedron()
{

}

void GL_Tetrahedron::MoveMent()
{
}

void GL_Tetrahedron::Init()
{
	Object::Init();

	color.SetRandomColor();

	Render::objectRenedr->AddObject(this);
}