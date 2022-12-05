#include "Sphere.h"

OBJ* Sphere::_Obj = nullptr;

Sphere::Sphere() : Mesh(this)
{
	name = "Shpere";
}

Sphere::~Sphere()
{
}

void Sphere::Init()
{
	if (_Obj == nullptr)
	{
		_Obj = new OBJ;
		_Obj->ReadObj((char*)"Sphere.obj");
	}
	obj = _Obj;
	Render::meshtRender->AddObject(this);
}

void Sphere::MoveMent()
{
}

