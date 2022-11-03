#pragma once

#include "Transform.h"
#include "Color.h"
#include "Camera.h"

//extern vec3 cameraPos;
//extern vec3 cameraDirection;
//extern vec3 cameraUp;

//extern bool isProjection;

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
	Transform transform;
	Color color;

	bool isActive;

	vec3 worldSpeed;
	vec3 worldPivotSpeed;

	vec3 worldRotateSpeed;
	vec3 localRotateSpeed;

public:
	static Camera* camera;

protected:
	GLuint VAO, VAO_Dot, VAO_Index;

	ObjectBlock block;
};