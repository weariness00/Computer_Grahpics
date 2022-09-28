#pragma once
#include "Object.h"
class GL_Triangle : public Object
{
public:
	GL_Triangle();
	~GL_Triangle();

public:
	void Update();
	Vector2* GetDot();
	Color* GetColor();

private:
	Vector2 Dot[3];
};