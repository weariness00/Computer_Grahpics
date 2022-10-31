#pragma once
#include "Object.h"
class Sphere : public Object
{
public:
	Sphere();
	~Sphere();

public:
	void Init();
	void Draw();

	void SetDrawStyle(bool value);
private:
	void MoveMent();

public:


private:
	GLUquadricObj* obj;
};

