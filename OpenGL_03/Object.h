#pragma once

#include "Collider.h"
#include "Color.h"

class Object {
public:
	Object();
	~Object();

public:
	void virtual Update();
	void virtual ExpensionScale();

public:
	string name;
	Transform transform;
	Collider collider;
	Color color;

	bool isActive;
	float now_S;

protected:
	GLuint VAO, VAO_Dot, VAO_Index;
	int imagnaryNumber;
};