#pragma once
#include "Object.h"
class GL_Cube : public Object
{
public:
	GL_Cube();
	~GL_Cube();

public:
	void Draw();
	void Init();

private:
	void MoveMent();
	

public:
	bool isActiveFace[6];
	Color faceColor[6];

	bool isPrismColor;

	vec3 speed;
	vec3 rotateSpeed;

	vec3 coordinateRotate;

private:
	ObjectBlock block;

	GLuint VAO_Color;
	GLclampf prismColor[4 * 8] = {
	1, 0, 0, 1,
	0, 1, 0, 1,
	0, 0, 1, 1,
	1, 1, 0, 1,
	0, 1, 1, 1,
	1, 0, 1, 1,
	1, 1, 1, 1,
	0, 0, 0.5f, 1
	};
};