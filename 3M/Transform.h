#pragma once

#include "Afx.h"

class Transform {
public:
	Transform();
	~Transform();

public:
	void Update();
	void SetScale(); // ���� ������
	void SetRandomRotate();

	void Info();
	void ReSet();

public:
	vec3 worldPosition;
	vec3 localPosition;

	vec3 worldScale;
	vec3 localScale;

	vec3 worldRotation;
	vec3 localRotation;

	vec3 worldPivot;
	vec3 localPivot;

	mat4 model;
};