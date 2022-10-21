#pragma once
#include "Object.h"

class GL_Coordinate : public Object {
public:
	GL_Coordinate();
	~GL_Coordinate();

public:
	void Draw();
	void Init();

private:
	void MoveMent();

public:
	vec3 speed;
	vec3 rotateSpeed;

private:
	ObjectBlock block;

	GLuint VAO_xLine, VAO_xLine_Dot, VAO_Color;

	GLclampf prismColor[4 * 6] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	1, 1, 0, 0,
	0, 1, 1, 0,
	1, 0, 1, 0
	};

	int maxVertexNumber = 0;
};