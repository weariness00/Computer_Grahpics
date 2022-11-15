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
	bool isRigidXY;	// x, y ���ÿ� �����̰� ���� �ʰ� x �����̰� y �����̰� �ϱ� ���� ����
};


