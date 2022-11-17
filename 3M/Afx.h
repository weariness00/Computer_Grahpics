#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <list>
#include <map>
#include <cmath>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include "FrameTime.h"

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
using namespace glm;

#pragma warning(disable:4996)

extern char default_Cube[];

extern GLuint s_program;
extern GLuint vertexShader; //--- ���ؽ� ���̴� ��ü
extern GLuint fragmentShader; //--- �����׸�Ʈ ���̴� ��ü

extern int windowSize_W;
extern int windowSize_H;

extern bool isFullScreen;

extern int Time_Duration;

extern float PI;

typedef struct Vector2 {
	GLfloat x;
	GLfloat y;
}Vector2;

typedef struct Vector3 {
	GLfloat x;
	GLfloat y;
	GLfloat z;
}Vector3;

typedef struct Position2 {
	int x;
	int y;
}Position2;

typedef struct Face {
	unsigned short a;
	unsigned short b;
	unsigned short c;
}Face;

typedef struct ObjectBlock {
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector<vec3> vertices;
	vector<vec2> vertices_uvs;
	vector<vec3> vertices_normals;
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
ostream& operator<< (ostream& outputStream, const Face& my);

vec3 operator* (const vec3 my, const float other);
vec3 operator/ (const vec3 my, const float other);
bool operator== (const vec3 my, const float other);

extern Vector2 window_RealPos;
extern Vector2 StartMouse;

float DistanceVec3(const vec3 my, const vec3 other);
float RandomFloat(float first, float second);

char* filetobuf(const char* file);
void make_vertexShaders();
void make_fragmentShaders();
void InitShader();
void FrameTimer(int value);
void ReadObj(char* fileName, ObjectBlock& block);