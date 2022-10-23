#pragma once
#include "Line.h"
class GL_Coordinate : public Object {
public:
	GL_Coordinate();
	~GL_Coordinate();

public:
	void Draw();
	void Init();

public:
	Line lineObject[3];

	vec3 speed;
	vec3 rotateSpeed;

private:
};