#include "GL_Tetrahedron.h"

GL_Tetrahedron::GL_Tetrahedron()
{
	ReadObj((char*)"Tetrahedron.obj", block);
	//Init();
}
GL_Tetrahedron::~GL_Tetrahedron()
{

}

void GL_Tetrahedron::Draw()
{
	if (!isActive)
		return;

	MoveMent();
	glUseProgram(s_program);

	for (int i = 0; i < 8; i++)
		prismColor[4 * (i + 1) - 1] = 0;
	if (isPrismColor)
		for (int i = 0; i < 8; i++)
			prismColor[4 * (i + 1) - 1] = 1;

	glBindBuffer(GL_ARRAY_BUFFER, VAO_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(prismColor), prismColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), 0);
	glEnableVertexAttribArray(1);

	mat4 model = translate(mat4(1.0), transform.Position);
	model = rotate(model, radians(transform.Rotation.x), vec3(0, 0, 1.0));
	model = rotate(model, radians(transform.Rotation.y), vec3(0, 1.0, 0));
	model = rotate(model, radians(transform.Rotation.z), vec3(1.0, 0, 0));
	model = scale(model, transform.Scale);

	int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	int vColorLocation = glGetUniformLocation(s_program, "vColor");
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

	glBindVertexArray(VAO);

	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, 4);

	for (int i = 0; i < 4; i++)
	{
		if (!isActiveFace[i])
			continue;

		glUniform4f(vColorLocation, faceColor[i].R, faceColor[i].G, faceColor[i].B, faceColor[i].A);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, (GLvoid*)(6 * i));
	}
}

void GL_Tetrahedron::MoveMent()
{
	transform.Position += speed;
	transform.Rotation = (transform.Rotation + rotateSpeed);
}

void GL_Tetrahedron::Init()
{
	transform.Scale *= 0.3;
	transform.Rotation += 20;

	for (int i = 0; i < 4; i++)
	{
		isActiveFace[i] = false;
		faceColor[i].SetRandomColor();
	}

	glUseProgram(s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_Dot);
	glGenBuffers(1, &VAO_Index);
	glGenBuffers(1, &VAO_Color);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VAO_Dot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * block.vertIndex, block.vertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_Index); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Face) * block.faceIndex, block.face, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
	glEnableVertexAttribArray(0);
}