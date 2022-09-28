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
	Vector2 Dot[2];

private:
	Vector2 Start_Dot[2];
};