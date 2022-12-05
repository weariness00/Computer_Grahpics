#pragma once

#include"Cube.h"

enum {
	Cube_Body,
	Cube_Handle,
	Cube_Left,
	Cube_Right,
	Cube_MaxIndex
};

class GL_Crane : public Object
{
public:
	GL_Crane();
	~GL_Crane();

public:
	void Init();
	void Draw();

	void ReSet();

private:
	void MoveMent();

public:
	Cube cube_Object[4];

private:

};