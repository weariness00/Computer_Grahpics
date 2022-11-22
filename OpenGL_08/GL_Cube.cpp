#include "GL_Cube.h"

GL_Cube::GL_Cube()
{
	name = "GL_Cube";

	worldSpeed = rotateSpeed = vec3(0);
}

GL_Cube::~GL_Cube()
{
}

void GL_Cube::Update()
{
	MoveMent();
	Animaition();

	for (int i = 0; i < 6; i++)
	{
		planObjet[i].transform.localPosition = transform.worldPosition;
		planObjet[i].transform.localRotation = transform.worldRotation;
		planObjet[i].transform.localScale = transform.worldScale;
	}
}

void GL_Cube::Init()
{
	transform.worldScale *= 1;

	for (int i = 0; i < 6; i++)
	{
		planObjet[i].color.SetRandomColor();
	}

	float dif = 0.5f;

	vec3 box[2] = { vec3(-0.5,0,0), vec3(0.5, 0, 0)};
	for (int i = 0; i < 4; i++)
	{
		collider[i].tag = "Wall_Y";
		if (i >= 2)
		{
			box[0] = vec3(0, -0.5, 0);
			box[1] = vec3(0, 0.5, 0);
			collider[i].tag = "Wall_X";
		}
		collider[i].InitTransform(planObjet[i].transform);
		collider[i].SetBox(box, 2);
		
	}

	// 아래
	planObjet[Cube_Down].transform.worldPosition.y = -dif;

	// 위
	planObjet[Cube_Up].transform.worldPosition.y = dif;
	planObjet[Cube_Up].transform.worldRotation.z = 180;

	// 왼쪽
	planObjet[Cube_Left].transform.worldPosition.x = -dif;
	planObjet[Cube_Left].transform.worldRotation.z = -90;

	// 오른쪽
	planObjet[Cube_Right].transform.worldPosition.x = dif;
	planObjet[Cube_Right].transform.worldRotation.z = 90;

	// 앞쪽
	planObjet[Cube_Forward].transform.worldPosition.z = dif;
	planObjet[Cube_Forward].transform.worldRotation.x = 90;
	planObjet[Cube_Forward].transform.worldRotation.z = 180;

	// 뒷쪽
	planObjet[Cube_back].transform.worldPosition.z = -dif;
	planObjet[Cube_back].transform.worldRotation.x = 90;

	
}

void GL_Cube::ReSet()
{
	for (int i = 0; i < 6; i++)
	{
		planObjet[i].transform.ReSet();
	}

	float dif = 0.5f;

	// 아래
	planObjet[Cube_Down].transform.worldPosition.y = -dif;

	// 위
	planObjet[Cube_Up].transform.worldPosition.y = dif;
	planObjet[Cube_Up].transform.worldRotation.z = 180;

	// 왼쪽
	planObjet[Cube_Left].transform.worldPosition.x = -dif;
	planObjet[Cube_Left].transform.worldRotation.z = -90;

	// 오른쪽
	planObjet[Cube_Right].transform.worldPosition.x = dif;
	planObjet[Cube_Right].transform.worldRotation.z = 90;

	// 뒷쪽
	planObjet[Cube_back].transform.worldPosition.z = -dif;
	planObjet[Cube_back].transform.worldRotation.x = 90;
}

void GL_Cube::Animaition()
{
	if (planObjet[Cube_Down].transform.worldPosition.x >= 1)
	{
		planObjet[Cube_Down].transform.worldPosition.x = 1;
		planObjet[Cube_Down].worldSpeed.x = 0;
	}

	if (planObjet[Cube_Forward].transform.worldRotation.x > 180)
	{
		planObjet[Cube_Forward].worldRotateSpeed.x = 0;
		planObjet[Cube_Forward].transform.worldRotation.x = 180;
	}
	else if (planObjet[Cube_Forward].transform.worldRotation.x < 90)
	{
		planObjet[Cube_Forward].worldRotateSpeed.x = 0;
		planObjet[Cube_Forward].transform.worldRotation.x = 90;
	}

	if (planObjet[Cube_Left].transform.worldPosition.y > 1)
	{
		planObjet[Cube_Left].transform.worldPosition.y = 1;
		planObjet[Cube_Left].worldSpeed.y = 0;
		planObjet[Cube_Right].transform.worldPosition.y = 1;
		planObjet[Cube_Right].worldSpeed.y = 0;
	}
	else if (planObjet[Cube_Left].transform.worldPosition.y < 0)
	{
		planObjet[Cube_Left].transform.worldPosition.y = 0;
		planObjet[Cube_Left].worldSpeed.y = 0;
		planObjet[Cube_Right].transform.worldPosition.y = 0;
		planObjet[Cube_Right].worldSpeed.y = 0;
	}

}


void GL_Cube::MoveMent()
{
	transform.worldPosition += worldSpeed * FrameTime::oneFrame;
	transform.worldRotation = (transform.worldRotation + rotateSpeed) * FrameTime::oneFrame;
}