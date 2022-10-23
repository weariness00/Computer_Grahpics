#pragma once
#include "Triangle.h"
#include "Plan.h"

enum {
	T_Foward,
	T_Back,
	T_Left,
	T_Right
};

class GL_Tetrahedron : public Object 
{
public:
	GL_Tetrahedron();
	~GL_Tetrahedron();

public:
	void Draw();
	void Init();

public:
	void Animaition();

private:
	void MoveMent();

public:
	Triangle triangleObject[4];
	Plan floor;

	bool isPrismColor;

	vec3 speed;
	vec3 rotateSpeed;

private:
};