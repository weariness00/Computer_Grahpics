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
};