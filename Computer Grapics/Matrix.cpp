#include "Matrix.h"

Matrix::Matrix()
{
	int** index = new int* [3];
	for (int i = 0; i < 3; i++)
		index[i] = new int[3];

	matrix_Index = index;
	matrix_X = matrix_Y = 3;
}

Matrix::Matrix(int X,int Y)
{
	matrix_X = X;
	matrix_Y = Y;

	int** index = new int* [matrix_X];
	for (int i = 0; i < matrix_X; i++)
		index[i] = new int[matrix_Y];

	matrix_Index = index;
}

Matrix::~Matrix()
{
	Remove();
}

void Matrix::Init()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 2);

	for (int y = 0; y < matrix_Y; y++)
	{
		for (int x = 0; x < matrix_X; x++)
		{
			matrix_Index[x][y] = dis(gen);
		}
	}
}

void Matrix::Remove()
{
	for (int i = 0; i < matrix_X; i++)
		delete[] matrix_Index[i];

	delete[] matrix_Index;
}

void Matrix::print(int go_x, int go_y)
{
	for (int y = 0; y < matrix_Y; y++)
	{
		gotoxy(go_x, go_y + y);
		for (int x = 0; x < matrix_X; x++)
		{
			cout << matrix_Index[x][y] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void Matrix::ReSize(int X, int Y)
{
	int minX = X;
	int minY = Y;
	int** index = new int* [X];
	for (int i = 0; i < X; i++)
		index[i] = new int[Y];

	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			index[x][y] = 0;
		}
	}
	index[X-1][Y-1] = 1;

	if (X > matrix_X)
		minX = matrix_X;
	if (Y > matrix_Y)
		minY = matrix_Y;
	for (int y = 0; y < minY; y++)
	{
		for (int x = 0; x < minX; x++)
		{
			index[x][y] = matrix_Index[x][y];
		}
	}

	Remove();

	matrix_X = X;
	matrix_Y = Y;
	matrix_Index = index;
}

int** Matrix::Plus(const Matrix& other)
{
	if (matrix_X != other.matrix_X &&
		matrix_Y != other.matrix_Y)
	{
		cout << "두 행렬의 크기가 다릅니다." << endl;
		return nullptr;
	}

	int** index = new int* [matrix_X];
	for (int i = 0; i < matrix_X; i++)
		index[i] = new int[matrix_Y];

	for (int y = 0; y < matrix_Y; y++)
	{
		for (int x = 0; x < matrix_X; x++)
		{
			index[x][y] = matrix_Index[x][y] + other.matrix_Index[x][y];
		}
	}

	return index;
}

int** Matrix::Minus(const Matrix& other)
{
	if (matrix_X != other.matrix_X &&
		matrix_Y != other.matrix_Y)
	{
		cout << "두 행렬의 크기가 다릅니다." << endl;
		return nullptr;
	}

	int** index = new int* [matrix_X];
	for (int i = 0; i < matrix_X; i++)
		index[i] = new int[matrix_Y];

	for (int y = 0; y < matrix_Y; y++)
	{
		for (int x = 0; x < matrix_X; x++)
		{
			index[x][y] = matrix_Index[x][y] - other.matrix_Index[x][y];
		}
	}

	return index;
}

int** Matrix::Multiplication(const Matrix& other)
{
	if (matrix_Y != other.matrix_X)
	{
		cout << "두 행렬의 크기가 다릅니다." << endl;
		return nullptr;
	}

	int** index = new int* [matrix_X];
	for (int i = 0; i < matrix_X; i++)
		index[i] = new int[other.matrix_Y];

	for (int y = 0; y < other.matrix_Y; y++)
	{
		for (int x = 0; x < matrix_X; x++)
		{
			index[x][y] = 0;
		}
	}

	for (int i = 0; i < matrix_X; i++)
	{
		for (int y = 0; y < other.matrix_Y; y++)
		{
			for (int x = 0; x < other.matrix_X; x++)
			{
				index[y][i] = matrix_Index[i][x] * other.matrix_Index[x][y];
			}
		}
	}

	return index;
}

int Matrix::determinant(int** matrix, int n) {
	int det = 0;
	int** submatrix = new int*[n];
	for (int i = 0; i < n; i++)
		submatrix[i] = new int[n];
	if (n == 2)
		return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	else {
		for (int x = 0; x < n; x++) {
			int subi = 0;
			for (int i = 1; i < n; i++) {
				int subj = 0;
				for (int j = 0; j < n; j++) {
					if (j == x)
						continue;
					submatrix[subi][subj] = matrix[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (pow(-1, x) * matrix[0][x] * determinant(submatrix, n - 1));
		}
	}
	return det;
}

void Matrix::Transposed()
{
	int** index = new int* [matrix_Y];
	for (int i = 0; i < matrix_Y; i++)
		index[i] = new int[matrix_X];

	for (int y = 0; y < matrix_Y; y++)
	{
		for (int x = 0; x < matrix_X; x++)
		{
			index[x][y] = matrix_Index[y][x];
		}
	}

	Remove();

	int temp = matrix_X;
	matrix_X = matrix_Y;
	matrix_Y = temp;

	matrix_Index = index;
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x * 2;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}