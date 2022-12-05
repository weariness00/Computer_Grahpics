#pragma once
#include "Render.h"
class Cube :public Object, public Mesh
{
public:
	Cube();
	~Cube();

public:
	void Init();
	void Update();

private:
	void MoveMent();

public:
	float zRotate;
	vec3 worldSpeed;
	vec3 worldRotateSpeed;
};

