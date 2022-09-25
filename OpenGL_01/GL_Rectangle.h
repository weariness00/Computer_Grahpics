#pragma once

#include "Object.h"

class GL_Rectangle : public Object
{
public:
	GL_Rectangle();
	~GL_Rectangle();
	void virtual Update();
	void Draw();

public:
	//bool Collide(Vector2 pos);
	//void SetPosition(Vector2 pos);
	//void SetScale(Vector2 scale[2]);
	//void SetScale();

public:
	//void InitStartPivot(Vector2 pivot);
	//void ResetPosition();
public:
	Vector2 Dot[2];
	//bool isCollide;

private:
	Vector2 Start_Dot[2];
	//Vector2 StartPivot;
	//Vector2 real_Dot[2];
};