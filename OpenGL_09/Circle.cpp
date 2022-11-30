#include "Circle.h"

Circle::Circle()
{
	radius = 1.0f;
}

Circle::~Circle()
{
}

void Circle::Init()
{
	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_LINE);
	Render::objectRenedr->AddObject(this);

	transform.worldRotation.x = 90;
}

void Circle::ObjectDraw()
{
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(transform.model));
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);

	glBindVertexArray(VAO);
	gluDisk(obj, radius, radius, 100, 1);
}
