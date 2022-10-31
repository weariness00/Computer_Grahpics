#pragma once
#include "Circle.h"
#include "Sphere.h"
class GL_Atom : public Object
{
public:
	GL_Atom();
	~GL_Atom();

public:
	void Init();
	void Draw();

private:
	void MoveMent();

public:
	Sphere shpere_Object;
	Circle circle_Objcet[3];

	float radian;
	float radianSpeed;
private:

};

