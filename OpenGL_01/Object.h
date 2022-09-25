#pragma once

#include "Collider.h"

class Object {
public:
	Object();
	~Object();

public:
	void virtual Update();
	//void virtual Draw();

public:
	void virtual SetColor(Color c);
	void virtual SetColor();
	//void virtual SetPosition(Vector2 scale_Pos[]);
	//void InitVertax(Vector2 vector[], int size);

public:
	string name;
	Transform transform;
	Collider collider;
	Color color;
	//Vector2* vertax;
	//Vector2 scale[2];
	//int size;

public:
	//Vector2 pivot_Pos;

private:
	//Vector2* real_Position;
};