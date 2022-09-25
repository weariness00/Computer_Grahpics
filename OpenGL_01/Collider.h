#pragma once

#include "Transform.h"

class Collider {
public:
	Collider();
	~Collider();
	
public:
	void InitCollider(Vector2 collider[]);
	void InitTransform(Transform& t);
	bool OnMouseCollide(Vector2 mousePos);
	bool WindowColider();
	bool OnCollider(const Collider& other); //지우개 전용

private:
	bool CheckCollide(const Vector2 one[]);

public:
	int xCollider;
	int yCollider;

	bool isAllCollide;
	bool isMouseCollide;
	bool isWindowCollide;
private:
	Vector2** Collider_Box;
	bool** isCollide;

	Transform* transform;
};