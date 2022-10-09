#pragma once
#include "Object.h"
class GL_Window : public Object
{
public:
	GL_Window();
	~GL_Window();

public:
	void Draw();
	void OnPointClick(Vector2 Mouse_Pos);
	void SetRotateDot();
	void CheckInBox(Vector2 Mouse_Pos);

private:
	Vector2* SetRealDot();
	

public:
	Transform* MouseDot;
	Transform* RotateDot;

	float Area;
	bool isInside;

private:
	GLuint VAO, VAO_Dot, VAO_Index;

	Transform Dot[4];
	Transform notRotateDot[4]; 
	Collider Dot_Collider[5];
	Vector2 real_Dot[5];
	Transform Rotate_Dot;
};

