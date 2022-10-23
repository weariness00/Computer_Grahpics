#include "GL_Cube.h"

GL_Cube::GL_Cube()
{
}

GL_Cube::~GL_Cube()
{
}

void GL_Cube::Draw()
{
	if(!isActive)
		return;

	MoveMent();
	Animaition();

	for (int i = 0; i < 6; i++)
	{
		planObjet[i].transform.localPosition = transform.worldPosition;
		planObjet[i].transform.localRotation = transform.worldRotation;
		planObjet[i].transform.localScale = transform.worldScale;

		planObjet[i].Draw();
	}
}

void GL_Cube::Init()
{
	transform.worldRotation += 30;
	transform.worldScale *= 1;
	rotateSpeed.y = 1;

	for (int i = 0; i < 6; i++)
	{
		planObjet[i].Init();
		planObjet[i].isActive = true;
		planObjet[i].color.SetRandomColor();
	}

	float dif = 0.5f;

	// 아래
	planObjet[Cube_Down].transform.worldPosition.y = -dif;
	planObjet[Cube_Down].transform.worldRotation.z = 180;

	// 위
	planObjet[Cube_Up].transform.worldPosition.y = dif;

	// 왼쪽
	planObjet[Cube_Left].transform.worldPosition.x = -dif;
	planObjet[Cube_Left].transform.worldRotation.z = 90;

	// 오른쪽
	planObjet[Cube_Right].transform.worldPosition.x = dif;
	planObjet[Cube_Right].transform.worldRotation.z = -90;

	// 앞쪽
	planObjet[Cube_Forward].transform.worldPosition.z = dif;
	planObjet[Cube_Forward].transform.worldRotation.x = 90;

	// 뒷쪽
	planObjet[Cube_back].transform.worldPosition.z = -dif;
	planObjet[Cube_back].transform.worldRotation.x = -90;

	
}

void GL_Cube::ReSet()
{
	transform.worldScale = vec3(0.3,0.3,0.3);
	transform.worldRotation = vec3(10,10,10);
	transform.worldPosition = vec3(-0.5, -0.5, -0.5);

	speed = rotateSpeed = { 0,0,0 };
}

void GL_Cube::Animaition()
{
	if (planObjet[Cube_Forward].transform.worldRotation.x > 180)
	{
		planObjet[Cube_Forward].rotateSpeed.x = 0;
		planObjet[Cube_Forward].transform.worldRotation.x = 180;
	}
	else if (planObjet[Cube_Forward].transform.worldRotation.x < 90)
	{
		planObjet[Cube_Forward].rotateSpeed.x = 0;
		planObjet[Cube_Forward].transform.worldRotation.x = 90;
	}

	if (planObjet[Cube_Left].transform.worldPosition.y > 1)
	{
		planObjet[Cube_Left].transform.worldPosition.y = 1;
		planObjet[Cube_Left].speed.y = 0;
		planObjet[Cube_Right].transform.worldPosition.y = 1;
		planObjet[Cube_Right].speed.y = 0;
	}
	else if (planObjet[Cube_Left].transform.worldPosition.y < 0)
	{
		planObjet[Cube_Left].transform.worldPosition.y = 0;
		planObjet[Cube_Left].speed.y = 0;
		planObjet[Cube_Right].transform.worldPosition.y = 0;
		planObjet[Cube_Right].speed.y = 0;
	}

}


void GL_Cube::MoveMent()
{
	transform.worldPosition += speed;
	transform.worldRotation = (transform.worldRotation + rotateSpeed);
}