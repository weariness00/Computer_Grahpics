#pragma once
#include "Object.h"
class Triangle : public Object
{
public:
	Triangle();
	~Triangle();

public:
	void Init();
	void Draw();

private:
	void MoveMent();
public:
	vec3 speed;
	vec3 rotateSpeed;
	
private:
	GLuint VAO_Color;

	GLclampf prismColor[4 * 3] = {
		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 0, 1, 1,
	};
};

