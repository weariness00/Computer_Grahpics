#pragma once
#include "Collider.h"
#include "Render.h"

class Cube :public Object
{
public:
	static ObjectBlock* cube_Block;

public:
	Cube();
	~Cube();

public:
	void Enable();
	void Disable();
	void Init();
	void Update();

private:
	void MoveMent();

public:
	Collider collider;

	float yScaleSpeed = 0;
};


