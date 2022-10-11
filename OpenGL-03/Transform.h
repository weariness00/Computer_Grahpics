#pragma once

#include "Afx.h"

class Transform {
public:
	Transform();
	Transform(vec3 pos, vec3 scale);
	~Transform();

public:
	void Update();
	void SetScale(); // 랜덤 스케일
	void SetRandomRotate();
	void LookAt(float speed);	// 바라보는 방향에서 pos 만큼 이동

public:
	vec3 Position;
	vec3 Pivot;
	vec3 Scale;
	vec3 Rotation;
};