#pragma once

#include "Transform.h"
#include "Color.h"
#include "Camera.h"

class Object {
public:
	Object();
	~Object();

public:
	virtual void Update();
	virtual void Init();
	virtual void ObjcetDraw();
	virtual void Collision();

	void Info();
public:
	mat4& SetMatrix();

public:
	int id;
	string name;
	Transform transform;
	Color color;

	ObjectBlock block;
	GLuint VAO;

	bool isActive;
public:
	vec3 worldSpeed;
	vec3 localSpeed;

	vec3 worldPivotSpeed;

	vec3 worldRotateSpeed;
	vec3 localRotateSpeed;

public:
	static int ID_Count;
	static list<Object*> allObject;

	static int modelLocation;
	static int vColorLocation;

protected:
	GLuint VAO_Dot, VAO_Index;
};