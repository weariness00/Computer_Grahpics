#pragma once
#include "Object.h"
class GL_Whirlwind : public Object
{
public:
	GL_Whirlwind();
	~GL_Whirlwind();

public:
	void Draw();
	void Init();

private:

public:
	int count[4 * 2];
	vec3** vertex;

	int maxCount;

	vec3 coordinateRotate;

private:
	GLuint W_VAO[4 * 2], W_Dot[4 * 2];
};

