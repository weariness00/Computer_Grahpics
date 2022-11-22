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
	void Handle_Evnet(unsigned char key);
	void Handle_Evnet(int specialKey);

public:
	void ReSet();
	void MakeMaze();

	void RandomMovingScaleAnimaiton();
	void SetWall_YScale(float yScale);

public:
	Cube** wall_Object;

	Position2 wall_number;

	float scaleMovingSpeed = 1;
	bool isRandomScaleMoveing = false;
};

