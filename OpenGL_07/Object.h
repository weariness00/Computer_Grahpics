#pragma once

#include "Transform.h"
#include "Color.h"
#include "Camera.h"

class Object {
public:
	Object();
	~Object();

public:
	void virtual Update();
	void virtual Init();

	void virtual Draw();
	void lineDraw();

public:
	void SetMatrix();

public:
	string name;
	static Camera* camera;
	Transform transform;
	Color color;

	bool isActive;
public:
	vec3 worldSpeed;
	vec3 worldPivotSpeed;

	vec3 worldRotateSpeed;
	vec3 localRotateSpeed;
protected:
	GLuint VAO, VAO_Dot, VAO_Index;

	ObjectBlock block;
};