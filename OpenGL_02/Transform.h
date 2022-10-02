#pragma once

#include "Afx.h"

class Transform {
public:
	Transform();
	Transform(Vector2 pos, Vector2 scale);
	~Transform();

public:
	void Update();
	void SetScale(); // ���� ������
	void SetRandomRotate();
	void LookAt(float speed);	// �ٶ󺸴� ���⿡�� pos ��ŭ �̵�

public:
	Vector2 Position;
	Vector2 Pivot;
	Vector2 Scale;
	Vector2 Rotation;
};