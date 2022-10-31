#pragma once
#include "Transform.h"

extern vec3 cameraPos;
extern vec3 cameraDirection;
extern vec3 cameraUp;
extern bool isProjection;

class Camera {
public:
	Camera();
	~Camera();

public:
	void Draw();

public:
	Transform transform;

	// 문제를 풀기 위한 임시 변수들
	bool isRotate;
};