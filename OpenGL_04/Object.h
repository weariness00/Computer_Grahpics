#pragma once

#include "Transform.h"
#include "Color.h"

extern vec3 cameraPos;
extern vec3 cameraDirection;
extern vec3 cameraUp;

extern bool isProjection;

class Object {
public:
	Object();
	~Object();

public:
	void virtual Update();
	void virtual Init();

	void virtual Draw();
	void lineDraw();

private:
	void SetMatrix();
public:
	string name;
	Transform transform;
	Color color;

	bool isActive;

protected:
	GLuint VAO, VAO_Dot, VAO_Index;

	ObjectBlock block;
};