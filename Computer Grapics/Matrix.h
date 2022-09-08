#pragma once
#include <iostream>
#include <random>
#include <windows.h>

using namespace std;

class Matrix {
public:
	Matrix();
	Matrix(int X, int Y);
	~Matrix();

public:
	void Init();
	void Remove();
	void print(int go_x, int go_y);

public:
	void ReSize(int X, int Y);
	int** Plus(const Matrix& other);
	int** Minus(const Matrix& other);
	int** Multiplication(const Matrix& other);
	int determinant(int** matrix, int n);
	void Transposed();

public:
	int** matrix_Index;
	int matrix_X;
	int matrix_Y;
};

void gotoxy(int x, int y);