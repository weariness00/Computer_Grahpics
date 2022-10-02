#pragma once

#include "Afx.h"

class Transform {
public:
	Transform();
	Transform(Vector2 pos, Vector2 scale);
	~Transform();

public:
	void Update();
	void SetScale(); // 랜덤 스케일
	void SetRandomRotate();
	void LookAt(float speed);	// 바라보는 방향에서 pos 만큼 이동

public:
	Vector2 Position;
	Vector2 Pivot;
	Vector2 Scale;
	Vector2 Rotation;
};