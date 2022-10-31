#include "Camera.h"

bool isProjection = true;
vec3 cameraPos = vec3(0.0f, 0.0f, 0.0f); //--- 카메라 위치
vec3 cameraDirection; //--- 카메라 바라보는 방향
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향

Camera mainCamera;

Camera::Camera()
{
	isRotate = true;
}

Camera::~Camera()
{
}

void Camera::Draw()
{
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);
	if (isProjection)	// 직각 투영
	{
		float size = 2.0f;
		projection = ortho(-size, size, -size, size, -size, size);
	}
	else
	{
		view = lookAt(cameraPos, cameraDirection, cameraUp);

		projection = perspective(radians(45.0f), 1.0f, 0.1f, 50.0f);

		float yR = 0;
		vec3 pi = vec3(0.0);
		if (isRotate)
		{
			cameraPos = vec3(0.0f, 0.0f, 0.0f); //--- 카메라 위치
			cameraDirection = vec3(1.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
		}
		else
		{
			cameraPos = vec3(0.0f, 0.0f, 0.0001f); //--- 카메라 위치
			cameraDirection = vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보는 방향
			
			yR = 90;
			pi.x = 5;
			pi.z = 4.5;
		}

		projection = translate(projection, transform.localPivot);
		projection = translate(projection, transform.localPosition);
		projection = rotate(projection, radians(transform.localRotation.x), vec3(1.0, 0.0, 0.0));
		projection = rotate(projection, radians(transform.localRotation.y + yR), vec3(0.0, 1.0, 0.0));

		projection = translate(projection, transform.worldPivot + pi);
		projection = translate(projection, transform.worldPosition);
		projection = rotate(projection, radians(transform.worldRotation.x), vec3(1.0, 0.0, 0.0));
		projection = rotate(projection, radians(transform.worldRotation.y), vec3(0.0, 1.0, 0.0));
	}
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- 뷰잉 변환 설정
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}
