#include "Sphere.h"

Sphere::Sphere()
{
	name = "Sphere";
}

Sphere::~Sphere()
{
}

void Sphere::Init()
{
	isActive = false;

	transform.worldScale *= 0.05;

	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);

	color.SetRandomColor();

	vec3 box[2] = { vec3(-1,-1,1), vec3(1,1,-1) };
	collider.InitTransform(transform);
	collider.SetBox(box,2);
	collider.tag = "Object";

	Render::mainRender->AddObject(this);
}

void Sphere::Update()
{
	if (!isActive)
		return;

	MoveMent();
	transform.worldPosition += rigidBody.UpdateRigid();

	SetMatrix();
}

void Sphere::ObjcetDraw()
{
	if (!isActive)
		return;

	Object::ObjcetDraw();

	gluSphere(obj, 1.0, 20, 20);
}

void Sphere::Collision()
{
	if (!collider.isCollide)
		return;

	collider.CheckCollision();

	for (auto& other : collider.onCollideList)
	{
		if (other->tag == "Wall_X" || other->tag == "Wall_Y")
		{
			transform.worldPosition.y -= rigidBody.UpdateRigid().y;
			rigidBody.velocity = -rigidBody.velocity;
		}
	}

}

void Sphere::MoveMent()
{
	transform.worldRotation += worldRotateSpeed;
	transform.localRotation += localRotateSpeed;
}

