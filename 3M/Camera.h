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

	vec3 cameraPos = vec3(0.0f, 5.0f, 5.0f); //--- 카메라 위치
	vec3 cameraDirection = vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
	vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향

	bool isProjection = false;
	bool isProjection_XY = false;
	bool isProjection_XZ = false;

	float yRotate = 0;
};
