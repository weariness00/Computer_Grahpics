#pragma once
#include "Collider.h"
#include "RigidBody.h"
#include "Render.h"

class Cube :public Object
{
public:
	static ObjectBlock* cube_Block;

public:
	Cube();
	~Cube();

public:
	void Update();
	void Init();

public:
	void Collision();

private:
	void MoveMent();

public:
	Collider collider;
	RigidBody rigidBody{ transform };

	float yScaleSpeed = 0;

private:
	bool isRigidXY;	// x, y 동시에 움직이게 하지 않고 x 움직이고 y 움직이게 하기 위한 변수
};


