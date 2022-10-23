#pragma once
#include "Afx.h"

class Color {
public:
	Color();
	~Color();

public:
	void SetRandomColor();
	void SetColor(Color color);
	void SetColor(GLclampf i[]);

private:

public:
	GLclampf R;
	GLclampf G;
	GLclampf B;
	GLclampf A;

private:

};