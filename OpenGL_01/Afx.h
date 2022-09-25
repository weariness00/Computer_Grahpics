#pragma once
#include <iostream>
#include <random>
#include <list>
#include <cmath>
#include <ctime>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

using namespace std;

#define MaxSpawnCount 10

static int windowSize_W = 1080;
static int windowSize_H = 860;

static bool isFullScreen = false;
static bool isOnTimer = false;
static bool isErase = false;

static bool left_button = false;
static bool right_button = false;

static int ObjectSpawnCount = 0;

static time_t Start_Time;
static int Time_Duration;

#pragma region  Defualt Function

typedef struct Vector2 {
	GLfloat x;
	GLfloat y;
}Vector2;

typedef struct Position2 {
	int x;
	int y;
}Position2;

typedef struct Color {
	GLclampf R;
	GLclampf G;
	GLclampf B;
	GLclampf A;
}Color;

static Vector2 RealPosition(Vector2 pos)
{
	Vector2 real_pos;

	real_pos.x = pos.x / windowSize_W * 2;
	real_pos.y = pos.y / windowSize_H * 2;

	return real_pos;
}

static Vector2 Coordinate(Vector2 pos)
{
	pos.x -= windowSize_W/2;
	pos.y -= windowSize_H/2;

	return pos;
}

static Vector2 operator+ (const Vector2 my, const Vector2 other)
{
	Vector2 result;
	result.x = my.x + other.x;
	result.y = my.y + other.y;

	return result;
}

static Vector2 operator- (const Vector2 my, const Vector2 other)
{
	Vector2 result;
	result.x = my.x - other.x;
	result.y = my.y - other.y;

	return result;
}

static Vector2 operator* (const Vector2 my, const Vector2 other)
{
	Vector2 result;
	result.x = my.x * other.x;
	result.y = my.y * other.y;

	return result;
}

static ostream& operator<< (ostream& outputStream, const Vector2& my)
{
	cout << my.x << ", " << my.y;
	return outputStream;
}

static Position2 operator+(const Position2 my, const Position2 other)
{
	Position2 result;
	result.x = my.x + other.x;
	result.y = my.y + other.y;

	return result;
}
#pragma endregion

static Vector2 window_RealPos = RealPosition({ 1, 1 });

static Color windowColor = { 0,0,0,1 };