#pragma once

#include "Camera.h"

class Collider {
public:
	static list<Collider*> allCollider;
	static bool isPrint;

public:
	Collider();
	~Collider();
	
public:
	void InitTransform(Transform& t);
	void SetBox(const vector<vec3> box);
	void CheckCollision();
	void OnTrigger();

public:
	void GetBox();
	bool Collide_XZ(Collider& other);
	bool Collide_XY(Collider& other);

public:
	string tag;
	Transform* transform;

	vec3 rDistance;

public:
	bool isCollide;
	bool isTrigger;
	bool isMouseCollide;
	bool isWindowCollide;

	list<Collider*> onCollideList;

private:
	vec3 colliderBox[2];
	vec4 modelbox[2];
};