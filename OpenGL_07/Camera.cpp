#include "Camera.h"

Camera::Camera()
{
	yRotate = 0;
}

Camera::~Camera()
{
}

void Camera::Draw()
{
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);
	float size = 2.0f;
	if (isProjection_XY)	// Á÷°¢ Åõ¿µ
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
		view = lookAt(cameraPos, cameraDirection, cameraUp);

		projection = perspective(radians(45.0f), 1.0f, 0.1f, 50.0f);

		projection = translate(projection, transform.localPivot);
		projection = translate(projection, transform.localPosition);
		projection = rotate(projection, radians(transform.localRotation.x), vec3(1.0, 0.0, 0.0));
		projection = rotate(projection, radians(transform.localRotation.y), vec3(0.0, 1.0, 0.0));

		projection = translate(projection, transform.worldPivot);
		projection = translate(projection, transform.worldPosition);
		projection = rotate(projection, radians(transform.worldRotation.x), vec3(1.0, 0.0, 0.0));
		projection = rotate(projection, radians(transform.worldRotation.y), vec3(0.0, 1.0, 0.0));
	}
	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ºäÀ× º¯È¯ ¼³Á¤
	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");

	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &projection[0][0]);
}
