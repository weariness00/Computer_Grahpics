#pragma once

#include "Transform.h"
#include "Color.h"
#include "Camera.h"

class Object {
public:
	static int ID_Count;
	static list<Object*> allObject;

	static unsigned char key;
	static int specialKey;

	static int modelLocation;
	static int vColorLocation;

public:
	Object();
	~Object();

public:
	virtual void Enable() {};
	virtual void Disable() {};
	virtual void Update();
	virtual void Init();
	virtual void ObjectDraw();
	virtual void Collision();

	//virtual void Handle_Evnet();

public:
	bool ActiveSelf() { return isActive; };
	void SetActive(bool value);
	void Info();
public:
	mat4& SetMatrix();

public:
	int id;
	string name;
	Transform transform;
	Color color;

	ObjectBlock block;

	bool isDraw;
public:
	vec3 worldSpeed;
	vec3 localSpeed;

	vec3 worldPivotSpeed;

	vec3 worldRotateSpeed;
	vec3 localRotateSpeed;


protected:
	GLuint VAO, VAO_Dot, VAO_Index;

private:
	bool isActive;
};