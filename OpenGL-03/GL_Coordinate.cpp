#include "GL_Coordinate.h"

GL_Coordinate::GL_Coordinate()
{
	ReadObj((char*)"Coordinate.obj", block);
}

GL_Coordinate::~GL_Coordinate()
{

}

void GL_Coordinate::Draw()
{
	if (!isActive)
		return;

	MoveMent();

	glUseProgram(s_program);
	int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	int vColorLocation = glGetUniformLocation(s_program, "vColor");

	mat4 model = mat4(1.0);
	model = translate(model, transform.Position);
	model = rotate(model, radians(transform.Rotation.x), vec3(0, 0, 1.0));
	model = rotate(model, radians(transform.Rotation.y), vec3(0, 1.0, 0));
	model = rotate(model, radians(transform.Rotation.z), vec3(1.0, 0, 0));

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

	glBindVertexArray(VAO);

	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);
	glDrawArrays(GL_LINES, 0, 6);
}

void GL_Coordinate::Init()
{
	speed = rotateSpeed = { 0,0,0 };
	//transform.Rotation += 10;

	glUseProgram(s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_Dot);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VAO_Dot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block.vertIndex, block.vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
	glEnableVertexAttribArray(0);
}

void GL_Coordinate::MoveMent()
{
	transform.Rotation += rotateSpeed;
}