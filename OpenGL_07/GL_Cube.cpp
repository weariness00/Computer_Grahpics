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


	t.localPivot = transform.worldPivot;
	t.localPosition = transform.worldPosition;
	t.localScale = transform.worldScale;
		;
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
	transform.worldScale *= 1;

	for (int i = 0; i < 6; i++)
	{
		planObjet[i].Init();
		planObjet[i].isActive = true;
		planObjet[i].color.SetRandomColor();
	}

	float dif = 0.5f;

	string tag[4] = { "Left","Right","Foward","Back" };
	vec3 box[2] = { vec3(0,0,0.5), vec3(0,0, -0.5) };
	for (int i = 0; i < 4; i++)
	{
		if (i == 2) {
			box[0] = vec3(0.5, 0, 0);
			box[1] = vec3(-0.5, 0, 0);
		}

		collider[i].InitTransform(planObjet[i + 2].transform);
		collider[i].SetBox(box, 2);
		collider[i].tag = tag[i];
	}
	collider[2].InitTransform(t);
	t.worldPosition.z = dif + 0.1;

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
	for (int i = 0; i < 6; i++)
	{
		planObjet[i].transform.ReSet();
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