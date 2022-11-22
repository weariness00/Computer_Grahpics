#pragma once

#include "Object.h"

class Collider {
public:
	static ObjectBlock* box_Block;
	static list<Collider*> allCollider;
	static bool isPrint;

public:
	Collider();
	~Collider();
	
public:
	void Init();
	void DrawBox();

public:
	void SetBox(const vec3* box, int size);
	void GetBox();
	bool Collide_XZ(Collider& other);

public:
	void SetBox_OBB(vec3 d);
	void GetBox_OBB();
	bool OBBCollision(const Collider& a,const Collider& b);

public:
	string tag;
	Object* object;

public:
	bool isCollide;
	bool isTrigger;
	bool isMouseCollide;
	bool isWindowCollide;

private:
	Color color;
	vec3 size;

	vec3 axis[3]; // �߽������� right, up, front ����
	float axisLen[3];
	vec3 defaultAxis[3];

	ObjectBlock cBlock;
	GLuint VAO, VAO_Dot, VAO_Index;

// �ӽ� ������
public:
	vec3 rDistance;
private:
	vec3 colliderBox[2];
	vec4 modelbox[2];
};