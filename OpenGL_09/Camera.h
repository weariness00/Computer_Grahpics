#pragma once
#include "Transform.h"

class Camera {
public:
 	static Camera* mainCamera;

	static unsigned int viewPosLocation;

public:
	Camera();
	~Camera();

public:
	void Draw();
	void ProcessInput(int specialKey);

	void Info();
public:
	string name;
	Transform transform;
	Transform* target_Pos;

	bool isProjection;
	bool isProjection_XY;
	bool isProjection_XZ;
	bool isPitch;
	vec3 cameraPos; //--- ī�޶� ��ġ
	vec3 cameraFront = vec3(0, 0, -1);
	vec3 cameraDirection; //--- ī�޶� �ٶ󺸴� ����
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);
	// ������ Ǯ�� ���� �ӽ� ������
	float yRotate;
	float speed;
};