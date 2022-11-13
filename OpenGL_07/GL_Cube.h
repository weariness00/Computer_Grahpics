#pragma once
#include "Plan.h"
#include "Collider.h"
enum Cube_Dir{
	Cube_Down,
	Cube_Up,
	Cube_Left,
	Cube_Right,
	Cube_Forward,
	Cube_back,
	Cube_MaxIndex
};

class GL_Cube : public Object
{
public:
	GL_Cube();
	~GL_Cube();

public:
	void Draw();
	void Init();
	void ReSet();

public:
	void Animaition();

private:
	void MoveMent();

public:
	Plan planObjet[6];
	Collider collider[4];

	vec3 speed;
	vec3 rotateSpeed;

	vec3 coordinateRotate;
private:
	GLclampf prismColor[4 * 8] = {
	1, 0, 0, 1,
	0, 1, 0, 1,
	0, 0, 1, 1,
	1, 1, 0, 1,
	1, 1, 1, 1,
	0, 1, 1, 1,
	1, 0, 1, 1,
	1, 1, 1, 1
	};

	Cube_Dir dir_type;

	Transform t;
};