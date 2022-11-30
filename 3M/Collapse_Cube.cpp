#include "Collapse_Cube.h"

ObjectBlock* CollapseCube::collapseCube_Block = nullptr;

CollapseCube::CollapseCube()
{
	name = "CollapseCube";

	if (collapseCube_Block == nullptr)
	{
		collapseCube_Block = new ObjectBlock;
		ReadObj((char*)"Collapse_Cube.obj", *collapseCube_Block);
	}

	block.vertexIndices = collapseCube_Block->vertexIndices;
	block.vertices = collapseCube_Block->vertices;
	block.faceIndex = collapseCube_Block->faceIndex;
	block.face = collapseCube_Block->face;

	block.groupIndex = collapseCube_Block->groupIndex;
	cell = new CollapseCube_Cell[block.groupIndex];
	for (int i = 0; i < block.groupIndex; i++)
	{
		cell[i].block.vertices = collapseCube_Block->vertices;
		cell[i].block.face = collapseCube_Block->fGroups[i];
	}

	isDistroy = false;
	delCount = 0;
}

CollapseCube::~CollapseCube()
{

}

void CollapseCube::Init()
{
	transform.worldPivot.y = 0.5;
	color.SetRandomColor();

	for (int i = 0; i < block.groupIndex; i++)
	{
		cell[i].name = "CollapseCube_Cell-" + to_string(i);
		cell[i].color.SetColor(color);
	}
}

void CollapseCube::Update()
{
	for (int i = 0; i < block.groupIndex; i++)
	{
		cell[i].transform.localPivot = transform.worldPivot + transform.localPivot;
		cell[i].transform.localPosition = transform.worldPosition + transform.localPosition;
		cell[i].transform.localRotation = transform.worldRotation + transform.localRotation;
		cell[i].transform.localScale = transform.worldScale * transform.localScale;
	}

	Handle_Evnet(key);
	DistroyAnimation();
}

void CollapseCube::Handle_Evnet(unsigned char key)
{
	switch (key)
	{
	case 'f':
		if (delCount == block.groupIndex)
			break;
		if (isDistroy)
		{
			delCount = block.groupIndex;
			isDistroy = false;
			Camera::mainCamera->yRotate = 0;
			Camera::mainCamera->cameraPos.z = defaultCameraDistance;
			Camera::mainCamera->cameraPos.x = 0;
			for (int i = 0; i < block.groupIndex; i++)
				cell[i].SetActive(false);
			break;
		}

		delTime = clock();
		isDistroy = true;
		break;
	case 'c':
		color.SetRandomColor();
		for (int i = 0; i < block.groupIndex; i++)
		{
			cell[i].SetActive(true);
			cell[i].color.SetColor(color);
		}
		isDistroy = false;
		delCount = 0;
		break;

		break;
	}
}

void CollapseCube::DistroyAnimation()
{
	if (!isDistroy)
		return;

	Camera::mainCamera->yRotate += 10 * FrameTime::oneFrame;
	Camera::mainCamera->cameraPos.x = defaultCameraDistance * sin(radians(Camera::mainCamera->yRotate));
	Camera::mainCamera->cameraPos.z = defaultCameraDistance * cos(radians(Camera::mainCamera->yRotate));

	if ((clock() - delTime) / 1000 < 0.2)
		return;

	cell[delCount].SetActive(false);
	delCount++;
	delTime = clock();

	if (delCount == block.groupIndex)
	{
		isDistroy = false;
		Camera::mainCamera->yRotate = 0;
		Camera::mainCamera->cameraPos.z = 5;
		Camera::mainCamera->cameraPos.x = 0;
	}
}