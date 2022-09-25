#include "Object.h"

Object::Object()
{
	name = "UnName";
	//pivot_Pos = { 0,0 };
	color = { 1,1,1,1 };
	collider.InitTransform(transform);
}

Object::~Object()
{
}

void Object::Update()
{
	transform.Update();
	//SetPosition(scale);
	//Draw();
}

//void Object::Draw()
//{
//	glColor3f(color.R, color.G, color.B);
//	glRectf(real_Position[0].x, -real_Position[0].y, real_Position[1].x, -real_Position[1].y);
//}

void Object::SetColor(Color c)
{
	color = c;
}

void Object::SetColor()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<GLclampf> randomcolor(0.0f, 1.0f);

	Color c = { randomcolor(gen),randomcolor(gen) ,randomcolor(gen),1 };
	SetColor(c);
}

//void Object::SetPosition(Vector2 scale_Pos[])
//{
//	for (int i = 0; i < size; i++)
//	{
//		real_Position[i] = RealPosition(vertax[i] * scale_Pos[i] + pivot_Pos);
//	}
//}
//
//void Object::InitVertax(Vector2 vector[], int size)
//{
//	this->size = size;
//	vertax = new Vector2[size];
//	real_Position = new Vector2[size];
//	for (int i = 0; i < size; i++)
//	{
//		vertax[i] = vector[i];
//	}
//}