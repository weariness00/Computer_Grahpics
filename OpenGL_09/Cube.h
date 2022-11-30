#pragma once
#include "Render.h"

class Cube :public Object
{
public:
	static ObjectBlock* cube_Block;

public:
	Cube();
	~Cube();

public:
	void Init();
	void Update();

private:
	void MoveMent();

public:
	float yScaleSpeed = 0;
};


