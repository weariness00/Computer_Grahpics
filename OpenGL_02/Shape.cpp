#include "Shape.h"

Shape::Shape()
{
	shapeSize = 2;
	radius = 100;
}

Shape::~Shape()
{

}

void Shape::Draw()
{
	if (!isActive)
		return;

	SetShape();

	if(isChagneShapeAni)
		Animaiton();
	else
		GetDot();

	glUseProgram(s_program);

	int* index;

	if (shapeSize == 1)
	{
		index = new int[shapeSize * 2];

		index[0] = 0;
		index[1] = 1;
	}
	else
	{
		index = new int[(shapeSize + 1) * 3];

		for (int i = 0; i < shapeSize + 1; i++)
		{
			index[i * 3] = 0;
			index[i * 3 + 1] = i + 1;
			index[i * 3 + 2] = i + 2;
		}
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_Dot);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VAO_Dot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * (shapeSize + 1), real_Dot, GL_STATIC_DRAW);
	glGenBuffers(1, &VAO_Index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_Index); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩

	if (shapeSize == 1)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 2 * shapeSize, index, GL_STATIC_DRAW);
	else
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * (shapeSize + 1), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);


	int vColorLocation = glGetUniformLocation(s_program, "vColor");
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);
	glBindVertexArray(VAO);

	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, shapeSize + 1);
	if (shapeSize == 1)	// 점
	{
		glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawElements(GL_LINES, 2 * (shapeSize - 2 + 1), GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 3 * (shapeSize - 2 + 1), GL_UNSIGNED_INT, 0);
	}

	delete Dot;
	delete real_Dot;
	delete change_Dot;
	delete StartAni_Dot;
}

Vector2* Shape::GetDot()
{
	for (int i = 0; i < shapeSize + 1; i++)
	{
		real_Dot[i] = RealPosition(Dot[i] * transform.Scale + transform.Position);
	}

	return real_Dot;
}

void Shape::SetShape()
{
	Dot = new Vector2[shapeSize + 1];
	real_Dot = new Vector2[shapeSize + 1];
	change_Dot = new Vector2[shapeSize + 1];
	StartAni_Dot = new Vector2[shapeSize + 1];
	int setha = 360;

	for (int i = 0; i < shapeSize + 1; i++)
	{
		double start_dgree = double((setha * (i + 1) / shapeSize + transform.Rotation.x) * (PI / 180));
		double change_dgree = double((setha * (i + 1) / (shapeSize + 1) + transform.Rotation.x) * (PI / 180));
		StartAni_Dot[i] = { float(radius * cos(start_dgree)), float(radius * sin(start_dgree)) };
		
		change_Dot[i] = { float(radius * cos(change_dgree)), float(radius * sin(change_dgree)) };

		Dot[i] = change_Dot[i];
	}
}

void Shape::RandomRadius()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> radnomRadius(50, 200);

	radius = radnomRadius(gen);
}

void Shape::Animaiton()
{
	int count = 100;

	for (int i = 0; i < shapeSize + 1; i++)
	{
		Dot[i] = StartAni_Dot[i] + ((change_Dot[i] - StartAni_Dot[i]) / count * ChangeAniCount);
	}

	GetDot();

	if (ChangeAniCount >= count)
	{
		ChangeAniCount = 0;
		shapeSize++;
		if (shapeSize > 8)
			shapeSize = 1;
	}

	ChangeAniCount++;
}