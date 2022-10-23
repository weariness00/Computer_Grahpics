#pragma once

#include "Afx.h"

class Transform {
public:
	Transform();
	Transform(vec3 pos, vec3 scale);
	~Transform();

public:
	void Update();
	void SetScale(); // ���� ������
	void SetRandomRotate();
	void LookAt(float speed);	// �ٶ󺸴� ���⿡�� pos ��ŭ �̵�

public:
	vec3 Position;
	vec3 Pivot;
	vec3 Scale;
	vec3 Rotation;
};