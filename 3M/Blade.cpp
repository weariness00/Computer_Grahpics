#include "Blade.h"

ObjectBlock* Blade::blade_Object = nullptr;

Blade::Blade()
{
	name = "Cube";

	if (blade_Object == nullptr)
	{
		blade_Object = new ObjectBlock;
		ReadObj((char*)"BladeSword.obj", *blade_Object);
	}

	block.vertIndex = blade_Object->vertIndex;
	block.faceIndex = blade_Object->faceIndex;
	block.vertices = blade_Object->vertices;
	block.face = blade_Object->face;
}

Blade::~Blade()
{
}

void Blade::Init()
{
}
