#pragma once
#include "Transform.h"

class Camera {
public:
	Camera();
	~Camera();

public:
	void Draw();

public:
	Transform transform;

	bool isProjection = false;
	bool isProjection_XY = false;
	bool isProjection_XZ = false;
	vec3 cameraPos = vec3(0.0f, 0.0f, 2.0f); //--- ī�޶� ��ġ
	vec3 cameraDirection = vec3(0.0f, 0.0f, 0.0f); //--- ī�޶� �ٶ󺸴� ����
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	// ������ Ǯ�� ���� �ӽ� ������
	float yRotate;
};