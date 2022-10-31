#pragma once
#include "Object.h"
class Circle : public Object
{
public:
	Circle();
	~Circle();
	
public:
	void Init();
	void Draw();

private:
	void MoveMent();

public:
	float radius;

private:
	GLUquadricObj* obj;
};

