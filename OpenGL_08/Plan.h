#pragma once
#include "Object.h"
#include "Render.h"
class Plan : public Object
{
public:
	Plan();
	~Plan();
	
public:
	void Update();
	void Init();

private:
	void MoveMent();

public:
	static ObjectBlock* plan_Block;

private:
	GLclampf prismColor[4 * 4] = {
		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 0, 1, 1,
		1, 1, 1, 1
	};
};

