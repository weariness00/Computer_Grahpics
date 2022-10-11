#include "GL_Cube.h"

GL_Cube::GL_Cube()
{
	ReadObj(default_Cube, block);
	Init();
}

GL_Cube::~GL_Cube()
{
}

void GL_Cube::Draw()
{
	if(!isActive)
		return;

	glUseProgram(s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_Dot);
	glGenBuffers(1, &VAO_Index);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VAO_Dot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block.vertIndex, block.vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_Index); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vec3) * block.faceIndex, block.face, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
	glEnableVertexAttribArray(0);

	mat4 model = scale(mat4(1.0), transform.Scale);
	model = translate(model, transform.Position); //--- model 행렬에 이동 변환 적용
	model = rotate(model, radians(transform.Rotation.x), vec3(0, 0, 1.0));
	model = rotate(model, radians(transform.Rotation.y), vec3(0, 1.0, 0));
	model = rotate(model, radians(transform.Rotation.z), vec3(1.0, 0, 0));

	unsigned int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	//--- modelTransform 변수에 변환 값 적용하기
	int vColorLocation = glGetUniformLocation(s_program, "vColor");
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

	glBindVertexArray(VAO);

	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, 8);
	glDrawElements(GL_TRIANGLES, block.faceIndex * sizeof(vec3) / 2, GL_UNSIGNED_INT_VEC3, 0);
}


void GL_Cube::Init()
{
	transform.Scale *= 0.3;
	transform.Rotation += 20;
	transform.Position += -0.5f;
}