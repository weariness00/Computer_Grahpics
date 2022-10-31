#include "GL_Atom.h"

GL_Atom::GL_Atom()
{
	radian = radianSpeed = 0;
}

GL_Atom::~GL_Atom()
{
}

void GL_Atom::Init()
{
	transform.worldRotation.x = 80;

	shpere_Object.Init();
	shpere_Object.isActive = true;
	shpere_Object.color.SetRandomColor();

	for (int i = 0; i < 3; i++)
	{
		circle_Objcet[i].Init();
		circle_Objcet[i].isActive = true;
		circle_Objcet[i].color.SetRandomColor();
	}

	circle_Objcet[1].transform.worldRotation.y = 45;
	circle_Objcet[2].transform.worldRotation.y = -45;
}

void GL_Atom::Draw()
{
	if (!isActive)
		return;

	MoveMent();

	shpere_Object.transform.localPivot = transform.worldPivot;
	shpere_Object.transform.localPosition = transform.worldPosition;
	shpere_Object.transform.localRotation = transform.worldRotation;
	shpere_Object.transform.localScale = transform.worldScale;
	shpere_Object.Draw();

	for (int i = 0; i < 3; i++)
	{
		if (!circle_Objcet[i].isActive)
			continue;

		circle_Objcet[i].transform.localPivot = transform.worldPivot;
		circle_Objcet[i].transform.localPosition = transform.worldPosition;
		circle_Objcet[i].transform.localRotation = transform.worldRotation;
		circle_Objcet[i].transform.localScale = transform.worldScale;
		circle_Objcet[i].Draw();
	}
}

void GL_Atom::MoveMent()
{
	transform.worldRotation += rotateSpeed;
}
