#include "GL_Crane.h"

GL_Crane::GL_Crane()
{
}

GL_Crane::~GL_Crane()
{
}

void GL_Crane::Init()
{
	for (int i = 0; i < Cube_MaxIndex; i++)
	{
		cube_Object[i].Init();
		cube_Object[i].color.SetRandomColor();
	}

	// ¸öÃ¼
	cube_Object[Cube_Body].transform.worldScale.y = 0.25;
	cube_Object[Cube_Body].transform.worldPivot.y -= 0.25;

	//Á¶Á¾¼®
	cube_Object[Cube_Handle].transform.worldScale *= 0.25;
	cube_Object[Cube_Handle].transform.worldScale.x *= 2;
	cube_Object[Cube_Handle].transform.worldScale.z *= 2;

	for (int i = Cube_Left; i < Cube_MaxIndex; i++)
	{
		cube_Object[i].transform.worldPivot.y = 0.25;
		cube_Object[i].transform.worldScale.x *= 0.25;
		cube_Object[i].transform.worldScale.z *= 0.25;
		cube_Object[i].transform.worldScale *= 0.25;
	}
	//¿ÞÂÊ ÆÈ
	cube_Object[Cube_Left].transform.worldPivot.z = 0.1;
	cube_Object[Cube_Left].color.SetColor(Color(1, 0, 0, 1));

	//¿À¸¥ÂÊ ÆÈ
	cube_Object[Cube_Right].transform.worldPivot.z = -0.1;
	cube_Object[Cube_Right].color.SetColor(Color(0, 1, 0, 1));

}

void GL_Crane::Draw()
{
	if (!isActive)
		return;

	MoveMent();

	for (int i = 0; i < Cube_MaxIndex; i++)
	{
		cube_Object[i].transform.localPivot = transform.worldPivot;
		cube_Object[i].transform.localPosition = transform.worldPosition;
		cube_Object[i].transform.localRotation = transform.worldRotation;
		cube_Object[i].transform.localScale = transform.worldScale;

		cube_Object[i].Draw();
	}
}

void GL_Crane::ReSet()
{
	transform.ReSet();
	for (int i = 0; i < Cube_MaxIndex; i++)
	{
		cube_Object[i].transform.ReSet();
		cube_Object[i].zRotate = 0;
	}

	//¸öÃ¼
	cube_Object[Cube_Body].transform.worldScale.y = 0.25;
	cube_Object[Cube_Body].transform.worldPivot.y = -0.25;

	//Á¶Á¾¼®
	cube_Object[Cube_Handle].transform.worldScale *= 0.25;
	cube_Object[Cube_Handle].transform.worldScale.x *= 2;
	cube_Object[Cube_Handle].transform.worldScale.z *= 2;

	for (int i = Cube_Left; i < Cube_MaxIndex; i++)
	{
		cube_Object[i].transform.worldPivot.y = 0.25;
		cube_Object[i].transform.worldScale.x *= 0.25;
		cube_Object[i].transform.worldScale.z *= 0.25;
		cube_Object[i].transform.worldScale *= 0.25;
	}

	//¿ÞÂÊ ÆÈ
	cube_Object[Cube_Left].transform.worldPivot.z = 0.1;

	//¿À¸¥ÂÊ ÆÈ
	cube_Object[Cube_Right].transform.worldPivot.z = -0.1;
}

void GL_Crane::MoveMent()
{
	transform.worldPosition += worldSpeed;
}
