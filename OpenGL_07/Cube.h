#pragma once
#include "Object.h"

class Cube :public Object
{
public:
	Cube();
	~Cube();

public:
	void Init();
	void Draw();

private:
	void MoveMent();

public:
	//Collider collider;

	float yScaleSpeed = 0;
public:
	static ObjectBlock* cube_Block;
};


