#pragma once
#include "Cube.h"
class GL_Maze : public Object
{
public:
	GL_Maze();
	~GL_Maze();

public:
	void Init();
	void Update();

public:
	void MakeMaze();

	void RandomMovingScaleAnimaiton();
	void SetWall_YScale(float yScale);

public:
	Cube** wall_Object;

	Position2 wall_number;

	bool isRandomScaleMoveing = false;
};

