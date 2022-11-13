#pragma once

#include "Camera.h"

class Collider {
public:
	static Camera* camera;

public:
	Collider();
	~Collider();
	
public:
	void InitTransform(Transform& t);
	void SetBox(const vec3* box, int size);

public:
	void GetBox();
	bool Collide_XZ(Collider& other);

public:
	string tag;

	bool isCollide;
	bool isMouseCollide;
	bool isWindowCollide;

	static bool isPrint;

	Transform* transform;
private:

	vec3 colliderBox[2];
	vec4 modelbox[2];
};