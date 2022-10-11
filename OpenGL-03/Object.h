#pragma once

#include "Collider.h"

class Object {
public:
	Object();
	~Object();

public:
	void virtual Update();

public:
	void virtual SetColor(Color c);
	void virtual SetColor();

public:
	string name;
	Transform transform;
	Collider collider;
	Color color;

	bool isActive;

protected:
	GLuint VAO, VAO_Dot, VAO_Index;
};