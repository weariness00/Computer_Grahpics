#pragma once
#include "Object.h"
#include "Render.h"

class GL_Tetrahedron : public Object 
{
public:
	static ObjectBlock* tetrahedron_Block;
public:
	GL_Tetrahedron();
	~GL_Tetrahedron();

public:
	void Init();

private:
	void MoveMent();

public:
};