#pragma once
#include "Object.h"
class GL_Cube : public Object
{
public:
	GL_Cube();
	~GL_Cube();

public:
	void Draw();

private:
	void Init();


public:
	

private:
	ObjectBlock block;
};