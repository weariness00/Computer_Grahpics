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
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

#pragma warning(disable : 4996)

extern char default_Cube[];

extern GLuint s_program;
extern GLuint vertexShader; //--- 버텍스 세이더 객체
extern GLuint fragmentShader; //--- 프래그먼트 세이더 객체

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

typedef struct Face {
	unsigned short* a;
	unsigned short* b;
	unsigned short* c;
}Face;

typedef struct ObjectBlock {
	vec3* vertex;
	Face* face;
	int vertIndex;
	int faceIndex;
}ObjectBlock;

Vector2 RealPosition(Vector2 pos);
Vector2 Coordinate(Vector2 pos);
Vector2 operator+ (const Vector2 my, const Vector2 other);
Vector2 operator+ (const Vector2 my, const int other);
Vector2 operator- (const Vector2 my, const Vector2 other);
Vector2 operator- (const Vector2 my, const int other);
Vector2 operator* (const Vector2 my, const Vector2 other);
Vector2 operator* (const Vector2 my, const int other);
Vector2 operator/ (const Vector2 my, const Vector2 other);
Vector2 operator/ (const Vector2 my, const int other);
ostream& operator<< (ostream& outputStream, const Vector2& my);
Position2 operator+(const Position2 my, const Position2 other);

ostream& operator<< (ostream& outputStream, const vec3& my);

extern Vector2 window_RealPos;
extern Color windowColor;
extern Vector2 StartMouse;

char* filetobuf(const char* file);
void make_vertexShaders();
void make_fragmentShaders();
void InitShader();
void FrameTimer(int value);
void ReadObj(char* fileName, ObjectBlock& block);