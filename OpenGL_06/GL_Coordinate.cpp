#include "GL_Coordinate.h"

GL_Coordinate::GL_Coordinate()
{
}

GL_Coordinate::~GL_Coordinate()
{

}

void GL_Coordinate::Draw()
{
	if (!isActive)
		return;

	for (int i = 0; i < 3; i++)
	{
		lineObject[i].transform.localPosition = transform.worldPosition;
		lineObject[i].transform.localRotation = transform.worldRotation;
		lineObject[i].transform.localScale = transform.worldScale;
		lineObject[i].transform.localPivot = transform.worldPivot;
		lineObject[i].Draw();
	}
}

void GL_Coordinate::Init()
{
	transform.worldScale *= 10;
	Color color(0, 0, 0, 1);
	for (int i = 0; i < 3; i++)
	{
		lineObject[i].Init();
		lineObject[i].color.SetColor(color);
		lineObject[i].isActive = true;
	}
	lineObject[0].color.R = 1;
	lineObject[1].color.G = 1;
	lineObject[2].color.B = 1;

	lineObject[1].transform.worldRotation.z = 90;	
	lineObject[2].transform.worldRotation.y = 90;
}