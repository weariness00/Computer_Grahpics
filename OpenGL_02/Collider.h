#pragma once

#include "Transform.h"

class Collider {
public:
	Collider();
	~Collider();
	
public:
	void InitTransform(Transform& t);

public:
	bool OnMouseCollide(Vector2 mousePos);
	bool WindowColider();
	bool OnCollide(Vector2 other[]);
	bool OnCollide(Collider other);
	void SetCollider(Vector2 dot[2]);

public:
	bool isCollide;
	bool isMouseCollide;
	bool isWindowCollide;

private:
	Vector2 Collider_Box[2];

	Transform* transform;
};