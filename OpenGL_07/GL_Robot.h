#pragma once
#include "Cube.h"
#include "Collider.h"

enum {
	Robot_Head,
	Robot_Nose,
	Robot_Torso, // ¸öÅë
	Robot_LeftArm,
	Robot_RightArm,
	Robot_LeftLeg,
	Robot_RightLef,
	Robot_MaxIndex
};

class GL_Robot : public Object
{
public:
	GL_Robot();
	~GL_Robot();

public:
	void Init();
	void Draw();
	void ReSet();

public:
	void OnAnimation();
	void OnCollision(Collider& other);

private:
	void MoveMent();

public:
	Cube body_Object[7];
	Collider collider;

	bool isMoveMent;

	vec3 prevPos;

public:
	vec3 worldSpeed;

	float movingRotateSpeed;
private:
	float movingRotateValue;
};

