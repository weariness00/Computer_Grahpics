#pragma once
#include "Object.h"

class Shape : public Object
{
public:
	Shape();
	~Shape();
	void Draw();

public:
	Vector2* GetDot();
	void SetShape();

	void RandomRadius();
	void Animaiton();

public:
	int shapeSize;	// 1 : ��, 2 : ��, 3: �ﰢ��, 4: �簢��, 5 : ������
	bool isChagneShapeAni = false;

private:
	GLuint VAO, VAO_Dot, VAO_Index;

	Vector2* Dot;
	Vector2* real_Dot;
	Vector2* change_Dot;
	Vector2* StartAni_Dot;

	int radius;
	int ChangeAniCount = 1;
};