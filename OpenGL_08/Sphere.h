#pragma once
#include "Collider.h"
#include "RigidBody.h"
#include "Render.h"
class Sphere : public Object
{
public:
	Sphere();
	~Sphere();

public:
	void Init();
	void Update();
	void ObjcetDraw();
	void Collision();

private:
	void MoveMent();

public:
	Collider collider;
	RigidBody rigidBody{transform};

private:
	GLUquadricObj* obj;
};

