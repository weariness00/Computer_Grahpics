#pragma once

#include "Collider.h"
#include "Color.h"

class Object {
public:
	Object();
	~Object();

public:
	void virtual Update();

public:
	string name;
	Transform transform;
	Collider collider;
	Color color;

	bool isActive;

protected:
	GLuint VAO, VAO_Dot, VAO_Index;
};