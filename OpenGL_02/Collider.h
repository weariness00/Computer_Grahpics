#pragma once

#include "Transform.h"

class Collider {
public:
	Collider();
	~Collider();
	
public:
	void InitCollider(Vector2 collider[]);
	void InitTransform(Transform& t);

public:
	bool OnMouseCollide(Vector2 mousePos);
	bool WindowColider();
	void SetAllColider(bool value);	// 수정(보완) 필요
	void CheckAllColider();

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