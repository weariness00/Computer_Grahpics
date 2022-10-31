#include "Camera.h"

//Camera::Camera()
//{
//}
//
//Camera::~Camera()
//{
//}
//
//void Camera::Init()
//{
//	glUseProgram(s_program);
//
//	mat4 view = mat4(1.0f);
//	view = lookAt(cameraPos, cameraDirection, cameraUp);
//	unsigned int viewLocation = glGetUniformLocation(s_program, "viewTransform"); //--- ºäÀ× º¯È¯ ¼³Á¤
//	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//
//	mat4 projection = mat4(1.0f);
//	projection = perspective(radians(45.0f), 1.0f, 0.1f, 100.0f);
//	projection = translate(projection, vec3(0.0, 0.0, -2.0)); //--- °ø°£À» ¾à°£ µÚ·Î ¹Ì·ïÁÜ
//	unsigned int projectionLocation = glGetUniformLocation(s_program, "projectionTransform");
//}
