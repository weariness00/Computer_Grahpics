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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Face) * block.faceIndex, block.face, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
	glEnableVertexAttribArray(0);

	mat4 model = translate(mat4(1.0), transform.Position);
	model = rotate(model, radians(transform.Rotation.x), vec3(0, 0, 1.0));
	model = rotate(model, radians(transform.Rotation.y), vec3(0, 1.0, 0));
	model = rotate(model, radians(transform.Rotation.z), vec3(1.0, 0, 0));
	model = scale(model, transform.Scale);

	int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	//--- modelTransform 변수에 변환 값 적용하기
	int vColorLocation = glGetUniformLocation(s_program, "vColor");
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

	glBindVertexArray(VAO);

	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, 8);
	for (int i = 0; i < 6; i++)
	{
		if (!isActiveFace[i])
			continue;

		glUniform4f(vColorLocation, faceColor[i].R, faceColor[i].G, faceColor[i].B, faceColor[i].A);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (GLvoid*)(sizeof(GLuint) * (3 * i)));
	}

}


void GL_Cube::Init()
{
	for (int i = 0; i < 6; i++)
	{
		isActiveFace[i] = false;
		faceColor[i].SetRandomColor();
	}

	transform.Scale *= 0.3;
	transform.Rotation += 10;
	transform.Position += -0.5f;
}