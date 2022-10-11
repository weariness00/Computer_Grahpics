#pragma once
#include "Object.h"

class GL_Tetrahedron : public Object 
{
public:
	GL_Tetrahedron();
	~GL_Tetrahedron();

public:
	void Draw();

private:
	void Init();

public:
	bool isActiveFace[4];

private:
	ObjectBlock block;

	Color faceColor[4];
};