#pragma once
#include "Object.h"
class Line : public Object
{
public:
	Line();
	~Line();

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

	GLclampf prismColor[4 * 2] = {
		1, 0, 0, 1,
		0, 0, 1, 1
	};
};

