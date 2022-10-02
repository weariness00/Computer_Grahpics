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
	void RandomWhirwindDir();

private:
	void InitPoint();

public:
	bool OnDrawAnimaiton;

	int DrawAniCount;

private:
	Vector2* Real_Point;
	Vector2* Point;
	int pointCount;

	float Radius;
	int speed;

	int UpDown = 1;
};

