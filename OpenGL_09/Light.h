#pragma once
#include "Sphere.h"

class Light : public Object
{
public:
	static unsigned int lightPosLocation;
	static unsigned int lightColorLocation;
	static unsigned int material;
public:
	Light();
	~Light();

public:
	void Enable();
	void Disable();
	void Init();
	void Update();
	void ObjectDraw();

public:
	Transform transform;
	Sphere shape;

public:
	float yRotate = 0;
	float dis = 0;
};

