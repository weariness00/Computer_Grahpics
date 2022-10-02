#pragma once
#include <iostream>
#include <random>
#include <list>
#include <cmath>
#include <ctime>	
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

using namespace std;

#pragma warning(disable : 4996)

#define SapwnCount 4

//extern GLuint s_program;
//extern GLuint VAO, VBO_Dot, VBO_Color;

extern int windowSize_W;
extern int windowSize_H;

extern bool isFullScreen;
extern bool isOnTimer;
extern bool isErase;

extern bool left_button;
extern bool right_button;

extern int ObjectSpawnCount;

extern time_t Start_Time;
extern int Time_Duration;

extern float PI;

typedef struct Vector2 {
	GLfloat x;
	GLfloat y;
}Vector2;

typedef struct Position2 {
	int x;
	int y;
}Position2;

typedef struct Color3 {
	GLclampf R;
	GLclampf G;
	GLclampf B;
}Color3;

typedef struct Color {
	GLclampf R;
	GLclampf G;
	GLclampf B;
	GLclampf A;
}Color;

Vector2 RealPosition(Vector2 pos);
Vector2 Coordinate(Vector2 pos);
Vector2 operator+ (const Vector2 my, const Vector2 other);
Vector2 operator- (const Vector2 my, const Vector2 other);
Vector2 operator* (const Vector2 my, const Vector2 other);
ostream& operator<< (ostream& outputStream, const Vector2& my);
Position2 operator+(const Position2 my, const Position2 other);

extern Vector2 window_RealPos;
extern Color windowColor;
extern Vector2 StartMouse;

char* filetobuf(const char* file);
//GLuint make_vertexShaders();
//GLuint make_fragmentShaders();