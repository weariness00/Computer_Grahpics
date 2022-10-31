#pragma once

#include "Afx.h"

class Transform {
public:
	Transform();
	~Transform();

public:
	void Update();
	void SetScale(); // 랜덤 스케일
	void SetRandomRotate();
	void LookAt(float speed);	// 바라보는 방향에서 pos 만큼 이동
public:
	vec3 worldPosition;
	vec3 localPosition;

	vec3 worldScale;
	vec3 localScale;

	vec3 worldRotation;
	vec3 localRotation;

	vec3 worldPivot;
	vec3 localPivot;
};