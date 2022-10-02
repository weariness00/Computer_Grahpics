#pragma once
#include "Object.h"
class GL_Triangle : public Object
{
public:
	GL_Triangle();
	~GL_Triangle();

public:
	void Update();
	Vector2* GetDot();
	Color* GetColor();

public:
	void MoveWindow();
	void SetRandomSpeed();
	void SetRandomZigZagRadius();
	void MoveZigZag();

public:
	int speed;
	int radius;

private:
	Vector2 Dot[3];
	Vector2 real_Dot[3]; // �ӽ�
	Color c[3];

private: //���� Ǯ�̸� ���� �ӽ� ������
	float zigzag_Radius;	//���� ��� ����
	int zigzag_Count;
	int zigzag_Speed;
	bool isZigZagCountMax;
};