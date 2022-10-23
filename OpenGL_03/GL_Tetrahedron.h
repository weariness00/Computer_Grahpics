#pragma once
#include "Object.h"

class GL_Tetrahedron : public Object 
{
public:
	GL_Tetrahedron();
	~GL_Tetrahedron();

public:
	void Draw();
	void Init();

private:
	void MoveMent();
	

public:
	bool isActiveFace[4];

	bool isPrismColor;

	vec3 speed;
	vec3 rotateSpeed;

private:
	ObjectBlock block;

	Color faceColor[4];

	GLuint VAO_Color;
	GLclampf prismColor[4 * 5] = {
		1, 0, 0, 1,
		0, 1, 0, 1,
		0, 0, 1, 1,
		1, 1, 0, 1,
		0, 1, 1, 1,
	};
};