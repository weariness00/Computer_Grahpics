#pragma once
#include "Object.h"
#include "Render.h"
class Circle : public Object
{
public:
	Circle();
	~Circle();
	
public:
	void Init();
	void ObjectDraw();

public:
	float radius;

private:
	GLUquadricObj* obj;
};

