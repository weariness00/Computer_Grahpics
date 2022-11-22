#include "Camera.h"

Camera* Camera::mainCamera = nullptr;

Camera::Camera()
{
	name = "Null";

	yRotate = 0;

	isProjection = false;
	isProjection_XY = false;
	isProjection_XZ = false;
	isPitch = false;

	cameraPos = vec3(0);
	cameraDirection = vec3(0);
}

Camera::~Camera()
{
}

void Camera::Draw()
{
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);
	float size = 2.0f;
	if (isProjection_XY)	// ���� ����
	{
		projection = ortho(-size, size, -size, size, -size, size);
	}
	else if (isProjection_XZ)
	{
		projection = ortho(-size, size, -size, size, -size, size);
		projection = rotate(projection, radians(90.0f), vec3(1, 0, 0));
	}
	else if(isProjection)
	{
		view = lookAt(cameraPos, vec3(0), cameraUp);

		projection = perspective(radians(45.0f), 1.0f, 0.1f, 50.0f);

		projection = translate(projection, transform.localPosition);
		projection = rotate(projection, radians(transform.localRotation.x), vec3(1.0, 0.0, 0.0));
		projection = rotate(projection, radians(transform.localRotation.y), vec3(0.0, 1.0, 0.0));
		projection = rotate(projection, radians(transform.localRotation.z), vec3(0.0, 0.0, 1.0));

		projection = translate(projection, transform.worldPosition);
		projection = rotate(projection, radians(transform.worldRotation.x), vec3(1.0, 0.0, 0.0));
		projection = rotate(projection, radians(transform.worldRotation.y), vec3(0.0, 1.0, 0.0));
		projection = rotate(projection, radians(transform.worldRotation.z), vec3(0.0, 0.0, 1.0));
	}
	else if (isPitch)
	{
		mat4 dirModel = translate(target_Pos->model, cameraDirection);
		mat4 posModel = translate(target_Pos->model, cameraPos);
		vec3 dir = dirModel * vec4(0, 0, 0, 1);
		vec3 pos = posModel * vec4(0, 0, 0, 1);
		view = lookAt(pos, dir, cameraUp);

		projection = perspective(radians(45.0f), 1.0f, 0.1f, 50.0f);
	}

	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ���� ��ȯ ����
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}
void Camera::ProcessInput(int specialKey)
{
	//float cameraSpeed = speed * FrameTime::oneFrame;
	//switch (specialKey)
	//{
	//case GLUT_KEY_LEFT:
	//	cameraPos -= glm::normalize(glm::cross(cameraDirection, cameraUp)) * cameraSpeed;
	//	break;
	//case GLUT_KEY_RIGHT:
	//	cameraPos += glm::normalize(glm::cross(cameraDirection, cameraUp)) * cameraSpeed;
	//	break;
	//case GLUT_KEY_UP:
	//	cameraPos += cameraSpeed * cameraDirection;
	//	break;
	//case GLUT_KEY_DOWN:
	//	cameraPos -= cameraSpeed * cameraDirection;
	//	break;
	//}
}


void Camera::Info()
{
	cout << "Camera : " << name << endl;
}