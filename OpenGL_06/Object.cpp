#include "Object.h"

//vec3 cameraPos = vec3(0.0f, 0.0f, 5.0f); //--- 카메라 위치
//vec3 cameraDirection = vec3(0.0f, 0.0f, 0.0f); //--- 카메라 바라보
//vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향

//bool isProjection = true;

Camera* Object::camera = nullptr;

Object::Object()
{
	name = "UnName";
	isActive = false;
	camera = &mainCamera;

	zRotate = 0;
}

Object::~Object()
{
}

void Object::Update()
{
}

void Object::Init()
{
	glUseProgram(s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_Dot);
	glGenBuffers(1, &VAO_Index);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VAO_Dot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block.vertIndex, block.vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_Index); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Face) * block.faceIndex, block.face, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
	glEnableVertexAttribArray(0);

	delete block.vertex;
	delete block.face;
}

void Object::Draw()
{
	if (!isActive)
		return;

	SetMatrix();

	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, block.vertIndex);
	glDrawElements(GL_TRIANGLES, block.faceIndex * 3, GL_UNSIGNED_SHORT, 0);
}

void Object::lineDraw()
{
	if (!isActive)
		return;

	SetMatrix();
	glDrawArrays(GL_LINES, 0, block.vertIndex);
}

void Object::SetMatrix()
{
	glUseProgram(s_program);

	camera->Draw();

	int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	int vColorLocation = glGetUniformLocation(s_program, "vColor");

	mat4 worldModel = mat4(1.0);
	mat4 localModel = mat4(1.0);

	
	localModel = translate(localModel, transform.localPosition);
	localModel = rotate(localModel, radians(transform.localRotation.x), vec3(1.0, 0, 0));
	localModel = rotate(localModel, radians(transform.localRotation.y), vec3(0, 1.0, 0));	// y축으로 자전 해주고 싶어 처음에 추가
	localModel = rotate(localModel, radians(transform.localRotation.z), vec3(0, 0, 1.0));
	localModel = translate(localModel, transform.localPivot);
	localModel = scale(localModel, transform.localScale);


	worldModel = translate(worldModel, transform.worldPosition);
	worldModel = rotate(worldModel, radians(transform.worldRotation.x), vec3(1.0, 0, 0));
	worldModel = rotate(worldModel, radians(transform.worldRotation.y), vec3(0, 1.0, 0));
	worldModel = rotate(worldModel, radians(transform.worldRotation.z), vec3(0, 0, 1.0));
	worldModel = translate(worldModel, transform.worldPivot);

	{
		// 임시
		worldModel = rotate(worldModel, radians(zRotate), vec3(0, 0, 1.0));
	}
	worldModel = scale(worldModel, transform.worldScale);


	mat4 model = localModel * worldModel;

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);

	glBindVertexArray(VAO);
}
