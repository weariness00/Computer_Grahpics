#include "GL_Whirlwind.h"

GL_Whirlwind::GL_Whirlwind()
{
	maxCount = 0;
}

GL_Whirlwind::~GL_Whirlwind()
{
}

void GL_Whirlwind::Draw()
{
	if (!isActive)
		return;

	glUseProgram(s_program);
	int modelLocation = glGetUniformLocation(s_program, "modelTransform");
	int vColorLocation = glGetUniformLocation(s_program, "vColor");

	mat4 model = mat4(1.0);
	model = rotate(model, radians(coordinateRotate.x), vec3(1.0, 0, 0));
	model = rotate(model, radians(coordinateRotate.y), vec3(0, 1.0, 0));
	model = rotate(model, radians(coordinateRotate.z), vec3(0, 0, 1.0));

	model = translate(model, transform.Position);
	model = rotate(model, radians(transform.Rotation.x), vec3(1.0, 0, 0));
	model = rotate(model, radians(transform.Rotation.y), vec3(0, 1.0, 0));
	model = rotate(model, radians(transform.Rotation.z), vec3(0, 0, 1.0));
	model = scale(model, transform.Scale);

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, value_ptr(model));

	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);
	glPointSize(5.0f);
	for (int i = 0; i < 4 * 2; i++)
	{
		glBindVertexArray(W_VAO[i]);
		glDrawArrays(GL_LINE_STRIP, 0, count[i] + 1);
		//glDrawArrays(GL_POINTS, 0, count[i] + 1);
	}
}

void GL_Whirlwind::Init()
{
	// 초기화
	int divide_Max = 4;
	vertex = new vec3 * [divide_Max * 2 + 1];

	// 회오리 모양을 낼 기준점 잡기
	float* wVertex = new float[divide_Max * 2 + 1];
	wVertex[0] = 0;
	for (int i = 0; i < divide_Max; i++)
	{
		wVertex[i * 2 + 1] = float(i + 1) / float(divide_Max);
		wVertex[i * 2 + 2] = -float(i + 1) / float(divide_Max);
	}

	// vertex 초기화
	for (int i = 0; i < divide_Max * 2; i++)
	{
		count[i] = int(40 * abs(wVertex[i] - wVertex[i + 1]));
		vertex[i] = new vec3[count[i] + 1];
		maxCount += count[i] + 1;
	}

	// 거리에 따른 반원 점 찍어주기
	for (int i = 0; i < divide_Max * 2; i++)
	{
		float pivot = (wVertex[i] + wVertex[i + 1]) / 2;
		float radius = abs(wVertex[i] - wVertex[i + 1]) / 2;

		float setha = 180;
		int num = 0;
		int imaginaryNum = pow(-1, i);

		if (imaginaryNum == -1)
			num = count[i];
		else
			num = 0;

		while (setha > 0)
		{
			vertex[i][num] = vec3(radius * cos(radians(imaginaryNum * setha)) + pivot,
									0,
								radius * sin(radians(imaginaryNum * setha)));
			setha -= float(180) / float(count[i]);

			if (imaginaryNum == -1)
				num--;
			else
				num++;
		}
		vertex[i][num] = vec3(radius + pivot, 0, 0);
		cout << vertex[i][num] << endl;
	}

	glUseProgram(s_program);

	glGenVertexArrays(divide_Max * 2, W_VAO);
	glGenBuffers(divide_Max * 2, W_Dot);
	
	for (int i = 0; i < divide_Max * 2; i++)
	{
		glBindVertexArray(W_VAO[i]);

		glBindBuffer(GL_ARRAY_BUFFER, W_Dot[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * (count[i] + 1), vertex[i], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
		glEnableVertexAttribArray(0);
	}
}
