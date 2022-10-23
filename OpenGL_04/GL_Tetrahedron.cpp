#include "GL_Tetrahedron.h"

GL_Tetrahedron::GL_Tetrahedron()
{

}
GL_Tetrahedron::~GL_Tetrahedron()
{

}

void GL_Tetrahedron::Draw()
{
	if (!isActive)
		return;

	MoveMent();
	Animaition();

	floor.transform.localPosition = transform.worldPosition;
	floor.transform.localRotation = transform.worldRotation;
	floor.transform.localScale = transform.worldScale;
	floor.transform.localPivot = transform.worldPivot;
	floor.Draw();
	for (int i = 0; i < 4; i++)
	{
		triangleObject[i].transform.localPosition = transform.worldPosition;
		triangleObject[i].transform.localRotation = transform.worldRotation;
		triangleObject[i].transform.localScale = transform.worldScale;
		triangleObject[i].transform.localPivot = transform.worldPivot;

		triangleObject[i].Draw();
	}
}

void GL_Tetrahedron::Init()
{
	transform.worldRotation += 30;

	floor.Init();
	floor.isActive = true;
	floor.color.SetRandomColor();
	for (int i = 0; i < 4; i++)
	{
		triangleObject[i].Init();
		triangleObject[i].isActive = true;
		triangleObject[i].color.SetRandomColor();

		triangleObject[i].transform.worldPivot.y = 0.5f;
		triangleObject[i].transform.worldPosition.y = -0.5f;
	}

	floor.transform.worldPivot.y = -0.5;
	floor.transform.worldRotation.y = 180;

	float dif = 0.5f;
	//앞
	triangleObject[T_Foward].transform.worldPosition.z = dif;
	triangleObject[T_Foward].transform.worldRotation.x = -30;

	//뒤
	triangleObject[T_Back].transform.worldPosition.z = -dif;
	triangleObject[T_Back].transform.worldRotation.x = -30;
	triangleObject[T_Back].transform.worldRotation.y = 180;

	// 왼쪽
	triangleObject[T_Left].transform.worldPosition.x = -dif;
	triangleObject[T_Left].transform.worldRotation.y = -90;
	triangleObject[T_Left].transform.worldRotation.x = -30;

	// 오른쪽
	triangleObject[T_Right].transform.worldPosition.x = dif;
	triangleObject[T_Right].transform.worldRotation.y = 90;
	triangleObject[T_Right].transform.worldRotation.x = -30;
}

void GL_Tetrahedron::Animaition()
{
	if (triangleObject[0].transform.worldRotation.x > 180 + 30)
	{
		for (int i = 0; i < 4; i++)
		{
			triangleObject[i].rotateSpeed.x = 0;
			triangleObject[i].transform.worldRotation.x = 180 + 30;
		}
	}
	else if (triangleObject[0].transform.worldRotation.x < -30)
	{
		for (int i = 0; i < 4; i++)
		{
			triangleObject[i].rotateSpeed.x = 0;
			triangleObject[i].transform.worldRotation.x = -30;
		}
	}
}

void GL_Tetrahedron::MoveMent()
{
	transform.worldPosition += speed;
	transform.worldRotation = (transform.worldRotation + rotateSpeed);
}