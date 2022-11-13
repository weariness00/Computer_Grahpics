#pragma once
#include "Object.h"
class Plan : public Object
{
public:
	Plan();
	~Plan();
	
public:
	void Draw();
	void Init();

private:
	void MoveMent();

public:
	vec3 speed;
	vec3 rotateSpeed;

	static ObjectBlock* plan_Block;

private:
	GLclampf prismColor[4 * 4] = {
		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 0, 1, 1,
		1, 1, 1, 1
	};
};

