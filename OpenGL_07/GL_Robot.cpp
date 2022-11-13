#include "GL_Robot.h"

GL_Robot::GL_Robot()
{
	movingRotateValue = 0;
	movingRotateSpeed = 1;

	isMoveMent = true;
}

GL_Robot::~GL_Robot()
{
}

void GL_Robot::Init()
{
	transform.worldPivot.y -= 0.3;
	movingRotateSpeed = 0;
	collider.InitTransform(transform);

	for (int i = 0; i < Robot_MaxIndex; i++)
	{
		body_Object[i].Init();
		body_Object[i].color.SetRandomColor();
		body_Object[i].isActive = true;
	}

	body_Object[Robot_Head].transform.worldScale *= 0.5;
	body_Object[Robot_Head].transform.worldPivot.y = 1.0f;

	body_Object[Robot_Nose].transform.worldScale *= 0.2f;
	body_Object[Robot_Nose].transform.worldPivot.y = 1.0f;
	body_Object[Robot_Nose].transform.worldPivot.z = 0.3f;
	
	body_Object[Robot_Torso].transform.worldScale.y = 1.5;
		
	body_Object[Robot_LeftArm].transform.worldScale *= 0.1;
	body_Object[Robot_LeftArm].transform.worldScale.y = 1;
	body_Object[Robot_LeftArm].transform.worldPosition.x = -0.8f;
	body_Object[Robot_LeftArm].transform.worldRotation.z = -30;

	body_Object[Robot_RightArm].transform.worldScale *= 0.1;
	body_Object[Robot_RightArm].transform.worldScale.y = 1;
	body_Object[Robot_RightArm].transform.worldPosition.x = 0.8f;
	body_Object[Robot_RightArm].transform.worldRotation.z = 30;

	body_Object[Robot_LeftLeg].transform.worldScale *= 0.2;
	body_Object[Robot_LeftLeg].transform.worldScale.y = 1;
	body_Object[Robot_LeftLeg].transform.worldPosition.y = -1;
	body_Object[Robot_LeftLeg].transform.worldPosition.x = -0.3f;
		
	body_Object[Robot_RightLef].transform.worldScale *= 0.2;
	body_Object[Robot_RightLef].transform.worldScale.y = 1;
	body_Object[Robot_RightLef].transform.worldPosition.y = -1;
	body_Object[Robot_RightLef].transform.worldPosition.x = 0.3f;


	vec3 dot[2] = { vec3(-0.5, 0, -0.5), vec3(0.5, 0, 0.5) };
	collider.SetBox(dot, 2);
}

void GL_Robot::Draw()
{
	if (!isActive)
		return;

	MoveMent();
	OnAnimation();

	if (transform.worldPosition.y > 0)
		transform.worldPosition.y -= 0.01;
	else
		transform.worldPosition.y = 0;

	for (int i = 0; i < Robot_MaxIndex; i++)
	{
		body_Object[i].transform.localPivot = transform.worldPivot;
		body_Object[i].transform.localPosition = transform.worldPosition;
		body_Object[i].transform.localRotation = transform.worldRotation;
		body_Object[i].transform.localScale = transform.worldScale;
		body_Object[i].Draw();
	}
}

void GL_Robot::ReSet()
{
	transform.worldPivot *= 0;
	transform.worldPosition *= 0;
	transform.worldRotation *= 0;
	movingRotateValue = 0;
	movingRotateSpeed = 0;
	worldSpeed = vec3(0);
	transform.worldPivot.y -= 0.3;

	for (int i = 0; i < Robot_MaxIndex; i++)
	{
		body_Object[i].transform.ReSet();
	}

	body_Object[Robot_Head].transform.worldScale *= 0.5;
	body_Object[Robot_Head].transform.worldPivot.y = 1.0f;

	body_Object[Robot_Nose].transform.worldScale *= 0.2f;
	body_Object[Robot_Nose].transform.worldPivot.y = 1.0f;
	body_Object[Robot_Nose].transform.worldPivot.z = 0.3f;

	body_Object[Robot_Torso].transform.worldScale.y = 1.5;

	body_Object[Robot_LeftArm].transform.worldScale *= 0.1;
	body_Object[Robot_LeftArm].transform.worldScale.y = 1;
	body_Object[Robot_LeftArm].transform.worldPosition.x = -0.8f;
	body_Object[Robot_LeftArm].transform.worldRotation.z = -30;

	body_Object[Robot_RightArm].transform.worldScale *= 0.1;
	body_Object[Robot_RightArm].transform.worldScale.y = 1;
	body_Object[Robot_RightArm].transform.worldPosition.x = 0.8f;
	body_Object[Robot_RightArm].transform.worldRotation.z = 30;

	body_Object[Robot_LeftLeg].transform.worldScale *= 0.2;
	body_Object[Robot_LeftLeg].transform.worldScale.y = 1;
	body_Object[Robot_LeftLeg].transform.worldPosition.y = -1;
	body_Object[Robot_LeftLeg].transform.worldPosition.x = -0.3f;

	body_Object[Robot_RightLef].transform.worldScale *= 0.2;
	body_Object[Robot_RightLef].transform.worldScale.y = 1;
	body_Object[Robot_RightLef].transform.worldPosition.y = -1;
	body_Object[Robot_RightLef].transform.worldPosition.x = 0.3f;
}

void GL_Robot::OnAnimation()
{
	if (movingRotateValue <= -30)
		movingRotateSpeed = 1;
	else if (movingRotateValue >= 30)
		movingRotateSpeed = -1;

	movingRotateValue += movingRotateSpeed;

	body_Object[Robot_LeftArm].transform.worldRotation.x += movingRotateSpeed;
	body_Object[Robot_LeftArm].transform.worldPosition.z += -movingRotateSpeed * 0.01f;
	body_Object[Robot_RightArm].transform.worldRotation.x += -movingRotateSpeed;
	body_Object[Robot_RightArm].transform.worldPosition.z += movingRotateSpeed * 0.01f;	

	body_Object[Robot_LeftLeg].transform.worldRotation.x += -movingRotateSpeed;
	body_Object[Robot_LeftLeg].transform.worldPosition.z += movingRotateSpeed * 0.01f;
	body_Object[Robot_RightLef].transform.worldRotation.x += movingRotateSpeed;
	body_Object[Robot_RightLef].transform.worldPosition.z += -movingRotateSpeed * 0.01f;
}

void GL_Robot::OnCollision(Collider& other)
{
	if (!collider.Collide_XZ(other))
		return;

	cout << "Ãæµ¹ : " << other.tag << endl;
	if (other.tag == "Left")
	{
		transform.worldPosition.x += 0.9;
	}
	else if (other.tag == "Right")
	{
		transform.worldPosition.x -= 0.9;
	}
	else if (other.tag == "Foward")
	{
		transform.worldPosition.z -= 0.9;
	}
	else if (other.tag == "Back")
	{
		transform.worldPosition.z += 0.9;
	}
	else if (other.tag == "Obstacle")
	{
		if (transform.worldPosition.y < 0.05)
		{
			transform.worldPosition -= worldSpeed;
			transform.worldPosition.y += worldSpeed.y;
		}
		else
		{
			transform.worldPosition.y += 0.005;
		}

	}
}

void GL_Robot::MoveMent()
{
	if (!isMoveMent)
		return;

	if (transform.worldPosition.y >= 0.2)
		worldSpeed.y = 0;

	transform.worldPosition += worldSpeed;
}
