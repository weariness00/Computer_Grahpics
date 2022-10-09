#include "GL_Window.h"

GL_Window::GL_Window()
{
	float size = 200;

	notRotateDot[0].Position = { -size, size };
	notRotateDot[1].Position = { -size, -size };
	notRotateDot[2].Position = { size, -size };
	notRotateDot[3].Position = { size, size };

	Vector2 box[2] = { { -10,-10}, {10, 10} };
	box[0] = box[0] + transform.Position;
	box[1] = box[1] + transform.Position;
	for (int i = 0; i < 4; i++)
	{
		Dot_Collider[i].SetCollider(box);
		Dot_Collider[i].InitTransform(Dot[i]);
	}
	Dot_Collider[4].SetCollider(box);
	Dot_Collider[4].InitTransform(Rotate_Dot);

	Area = 0;
}

GL_Window::~GL_Window()
{
}

void GL_Window::Draw()
{
	if (!isActive)
		return;

	SetRealDot();

	int index[] = {
		0,1,
		1,2,
		2,3,
		3,0
	};

	glUseProgram(s_program);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VAO_Dot);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VAO_Dot);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * 5, real_Dot, GL_STATIC_DRAW);
	glGenBuffers(1, &VAO_Index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VAO_Index); //--- GL_ELEMENT_ARRAY_BUFFER 버퍼 유형으로 바인딩
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	int vColorLocation = glGetUniformLocation(s_program, "vColor");
	glUniform4f(vColorLocation, color.R, color.G, color.B, color.A);
	glBindVertexArray(VAO);

	glPointSize(5.0f);
	glDrawArrays(GL_POINTS, 0, 4);
	glPointSize(10.0f);
	glDrawArrays(GL_POINTS, 4, 1);
	glDrawElements(GL_LINES, 8, GL_UNSIGNED_INT, 0);
}

void GL_Window::OnPointClick(Vector2 Mouse_Pos)
{
	if (!isActive)
		return;
	
	MouseDot = nullptr;
	RotateDot = nullptr;
	

	Dot_Collider[4].OnMouseCollide(Mouse_Pos);

	if (Dot_Collider[4].isMouseCollide)
	{
		RotateDot = &Rotate_Dot;
		return;
	}

	for (int i = 0; i < 4; i++)
	{
		Dot_Collider[i].OnMouseCollide(Mouse_Pos);

		if (Dot_Collider[i].isMouseCollide)
		{
			MouseDot = &notRotateDot[i];
			return;
		}
	}
}

Vector2* GL_Window::SetRealDot()
{
	Vector2 box[2] = { { -10,-10}, {10, 10} };
	box[0] = box[0] + transform.Position;
	box[1] = box[1] + transform.Position;

	float dgree;
	int distance;

	//SetRotateDot();

	for (int i = 0; i < 4; i++)
	{
		Dot_Collider[i].SetCollider(box);

		Dot[i] = notRotateDot[i];

		real_Dot[i] = RealPosition(Dot[i].Position * transform.Scale + transform.Position);
	}

	dgree = (90 - transform.Rotation.x)* (PI / 180);
	distance = sqrt(pow((Dot[3].Position.x + Dot[0].Position.x)/2, 2) + pow((Dot[0].Position.y + Dot[3].Position.y) /2, 2));
	Rotate_Dot.Position = { distance * cos(dgree) * 1.5f, distance * sin(dgree) * 1.5f };

	real_Dot[4] = RealPosition(Rotate_Dot.Position * transform.Scale + transform.Position);
	Dot_Collider[4].SetCollider(box);
	return real_Dot;
}

void GL_Window::SetRotateDot()
{
	float dgree;
	double distance;

	for (int i = 0; i < 4; i++)
	{
		distance = sqrt(pow(notRotateDot[i].Position.x, 2) + pow(notRotateDot[i].Position.y, 2));
		dgree = (transform.Rotation.x - notRotateDot[i].Rotation.x) * (PI / 180) + atan2(notRotateDot[i].Position.x,notRotateDot[i].Position.y);
		notRotateDot[i].Rotation.x = transform.Rotation.x;
		notRotateDot[i].Position.x = sin(dgree) * distance;
		notRotateDot[i].Position.y = cos(dgree) * distance;
	}
}

void GL_Window::CheckInBox(Vector2 Mouse_Pos)
{
	int collideCount = 0;
	Collider line_Collde[4];
	isInside = false;

	for (int i = 0; i < 4; i++)
	{
		Vector2 box[2];
		box[0] = notRotateDot[i].Position;
		box[1] = notRotateDot[(i + 1) % 4].Position;
		line_Collde[i].SetCollider(box);
		line_Collde[i].InitTransform(transform);
	}

	do
	{
		for (int i = 0; i < 4; i++)
		{
			if (line_Collde[i].isMouseCollide)
				continue;

			line_Collde[i].OnMouseCollide(Mouse_Pos);

			if (line_Collde[i].isMouseCollide)
				collideCount++;
		}

		Mouse_Pos.y++;
	} while (Mouse_Pos.y <= windowSize_H / 2);

	if (collideCount % 2 == 1)
		isInside = true;
}