#include "Collider.h"

Collider::Collider()
{
	isCollide = false;
	isMouseCollide = false;
	isWindowCollide = false;
}

Collider::~Collider()
{
}

void Collider::InitTransform(Transform& t)
{
	transform = &t;
}

//bool Collider::OnMouseCollide(Vector2 mousePos)
//{
//	Vector2 this_Box[2];
//
//	isMouseCollide = false;
//
//	for (int i = 0; i < 2; i++)
//		this_Box[i] = Collider_Box[i] * transform->Scale + transform->Position;
//
//	if (mousePos.x >= this_Box[0].x &&
//		mousePos.x <= this_Box[1].x &&
//		mousePos.y <= this_Box[0].y &&
//		mousePos.y >= this_Box[1].y)
//	{
//		isMouseCollide = true;
//		return isMouseCollide;
//	}
//
//	return isMouseCollide;
//}
//
//bool Collider::WindowColider()
//{
//	Vector2 window_Pos[2];
//	window_Pos[0] = Coordinate({0,0});
//	window_Pos[1] = Coordinate({(float)windowSize_W, (float)windowSize_H});
//
//	isWindowCollide = false;
//
//	if (Collider_Box[0].x * transform->Scale.x + transform->Position.x <= window_Pos[0].x ||
//		-(Collider_Box[0].x * transform->Scale.x) + transform->Position.x <= window_Pos[0].x ||
//		Collider_Box[1].x * transform->Scale.x + transform->Position.x <= window_Pos[0].x ||
//		-(Collider_Box[1].x * transform->Scale.x) + transform->Position.x <= window_Pos[0].x)
//		isWindowCollide = true;
//	else if (Collider_Box[0].x * transform->Scale.x + transform->Position.x >= window_Pos[1].x ||
//		-(Collider_Box[0].x * transform->Scale.x) + transform->Position.x >= window_Pos[1].x ||
//		Collider_Box[1].x * transform->Scale.x + transform->Position.x >= window_Pos[1].x ||
//		-(Collider_Box[1].x * transform->Scale.x) + transform->Position.x >= window_Pos[1].x)
//		isWindowCollide = true;
//	else if (Collider_Box[0].y * transform->Scale.y + transform->Position.y <= window_Pos[0].y||
//		-(Collider_Box[0].y * transform->Scale.y) + transform->Position.y <= window_Pos[0].y ||
//		Collider_Box[1].y * transform->Scale.y + transform->Position.y <= window_Pos[0].y || 
//		-(Collider_Box[1].y * transform->Scale.y) + transform->Position.y <= window_Pos[0].y)
//		isWindowCollide = true;
//	else if (Collider_Box[0].y * transform->Scale.y + transform->Position.y >= window_Pos[1].y ||
//		-(Collider_Box[0].y * transform->Scale.y) + transform->Position.y >= window_Pos[1].y ||
//		Collider_Box[1].y * transform->Scale.y + transform->Position.y >= window_Pos[1].y ||
//		-(Collider_Box[1].y * transform->Scale.y) + transform->Position.y >= window_Pos[1].y)
//		isWindowCollide = true;
//
//	return isWindowCollide;
//}
//
//bool Collider::OnCollide(Vector2 other[])
//{
//	Collider co;
//	co.transform = new Transform;
//	for (int i = 0; i < 2; i++)
//		co.Collider_Box[i] = other[i];
//
//	OnCollide(co);
//
//	return false;
//}
//
//bool Collider::OnCollide(Collider other)
//{
//	Vector2 this_Box[2];
//	Vector2 other_Box[2];
//	isCollide = false;
//	for (int i = 0; i < 2; i++)
//	{
//		this_Box[i] = Collider_Box[i] * transform->Scale + transform->Position;
//		other_Box[i] = other.Collider_Box[i] * other.transform->Scale + other.transform->Position;
//	}
//
//	if ((this_Box[0].x <= other_Box[0].x && this_Box[1].x >= other_Box[0].x) ||
//		(this_Box[0].x <= other_Box[1].x && this_Box[1].x >= other_Box[1].x))
//	{
//		if ((this_Box[0].y <= other_Box[0].y && this_Box[0].y >= other_Box[1].y) ||
//			(this_Box[0].y >= other_Box[0].y && this_Box[1].y <= other_Box[0].y))
//		{
//			isCollide = true;
//		}
//	}
//	else if ((this_Box[0].y >= other_Box[0].y && this_Box[1].y <= other_Box[0].y) ||
//		(this_Box[0].y >= other_Box[1].y && this_Box[1].y <= other_Box[1].y))
//	{
//		if ((this_Box[0].x >= other_Box[0].x && this_Box[0].x <= other_Box[1].x) ||
//			(this_Box[0].x <= other_Box[0].x && this_Box[1].x >= other_Box[0].x))
//		{
//			isCollide = true;
//		}
//	}
//	return isCollide;
//}
//
//void Collider::SetCollider(Vector2 dot[2])
//{
//	Vector2 d[2];
//	d[0] = dot[0];
//	d[1] = dot[0];
//	for (int i = 1; i < 2; i++)
//	{
//		if (d[0].x > dot[i].x)
//			d[0].x = dot[i].x;
//		if (d[0].y < dot[i].y)
//			d[0].y = dot[i].y;
//
//		if (d[1].x < dot[i].x)
//			d[1].x = dot[i].x;
//		if (d[1].y > dot[i].y)
//			d[1].y = dot[i].y;
//	}
//
//	for (int i = 0; i < 2; i++)
//	{
//		Collider_Box[i] = d[i];
//	}
//
//}