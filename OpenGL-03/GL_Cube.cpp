#include "GL_Cube.h"

GL_Cube::GL_Cube()
{
	ReadObj(default_Cube, block);
	//Init();
}

GL_Cube::~GL_Cube()
{
}

void GL_Cube::Draw()
{
	if(!isActive)
		return;

	MoveMent();

	for (int i = 0; i < 6; i++)
		faceColor[i].A = 1;
	if (isPrismColor)
		for (int i = 0; i < 6; i++)
			faceColor[i].A = 0;

	glUseProgram(s_program);
	int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	int vColorLocation = glGetUniformLocation(s_program, "vColor");

	mat4 model = mat4(1.0);
	model = rotate(model, radians(coordinateRotate.x), vec3(1.0, 0, 0));
	model = rotate(model, radians(coordinateRotate.y), vec3(0, 1.0, 0));
	model = rotate(model, radians(coordinateRotate.z), vec3(0, 0, 1.0));

	model = scale(model, originScale); // 원점에 대한 신축

	model = translate(model, transform.Position);
	model = rotate(model, radians(transform.Rotation.x), vec3(1.0, 0, 0));
	model = rotate(model, radians(transform.Rotation.y), vec3(0, 1.0, 0));
	model = rotate(model, radians(transform.Rotation.z), vec3(0, 0, 1.0));
	model = scale(model, transform.Scale);

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

void GL_Cube::ReSet()
{
	for (int i = 0; i < 6; i++)
	{
		isActiveFace[i] = false;
		faceColor[i].SetRandomColor();
	}
	isPrismColor = false;

	transform.Scale = vec3(0.3,0.3,0.3);
	transform.Rotation = vec3(10,10,10);
	transform.Position = vec3(-0.5, -0.5, -0.5);

	originScale = vec3(0, 0, 0);
	now_S = transform.Scale.x;

	speed = rotateSpeed = { 0,0,0 };
}




void GL_Cube::MoveMent()
{
	transform.Position += speed;
	transform.Rotation = (transform.Rotation + rotateSpeed);
}


void GL_Cube::Init()
{
	for (int i = 0; i < 6; i++)
	{
		isActiveFace[i] = false;
		faceColor[i].SetRandomColor();
	}
	isPrismColor = false;

	transform.Scale *= 0.3;
	transform.Rotation += 10;
	transform.Position += -0.5f;

	now_S = transform.Scale.x;

	speed = rotateSpeed = { 0,0,0 };

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

	glBindBuffer(GL_ARRAY_BUFFER, VAO_Color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(prismColor), prismColor, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vec4), 0);
	glEnableVertexAttribArray(1);

	delete block.vertex;
	delete block.face;
}