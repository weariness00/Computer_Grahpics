#pragma once
#include "Object.h"

class GL_Whirlwind : public Object
{
public:
	GL_Whirlwind();
	~GL_Whirlwind();

public:
	Vector2* GetDot();
	int GetPointCount() { return pointCount; };

private:
	void InitPoint();

private:
	Vector2* Real_Point;
	Vector2* Point;
	int pointCount;

	float Radius;
	int speed;
};

