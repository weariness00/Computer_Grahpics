#include "Afx.h"

int windowSize_W = 1080;
int windowSize_H = 860;

bool isFullScreen = false;
bool isOnTimer = false;
bool isErase = false;

bool left_button = false;
bool right_button = false;

int ObjectSpawnCount = 0;

time_t Start_Time;
int Time_Duration;

Vector2 RealPosition(Vector2 pos)
{
	Vector2 real_pos;

	real_pos.x = pos.x / windowSize_W * 2;
	real_pos.y = pos.y / windowSize_H * 2;

	return real_pos;
}

Vector2 Coordinate(Vector2 pos)
{
	pos.x -= windowSize_W / 2;
	pos.y -= windowSize_H / 2;

	return pos;
}

Vector2 operator+ (const Vector2 my, const Vector2 other)
{
	Vector2 result;
	result.x = my.x + other.x;
	result.y = my.y + other.y;

	return result;
}

Vector2 operator- (const Vector2 my, const Vector2 other)
{
	Vector2 result;
	result.x = my.x - other.x;
	result.y = my.y - other.y;

	return result;
}

Vector2 operator* (const Vector2 my, const Vector2 other)
{
	Vector2 result;
	result.x = my.x * other.x;
	result.y = my.y * other.y;

	return result;
}

ostream& operator<< (ostream& outputStream, const Vector2& my)
{
	cout << my.x << ", " << my.y;
	return outputStream;
}

Position2 operator+(const Position2 my, const Position2 other)
{
	Position2 result;
	result.x = my.x + other.x;
	result.y = my.y + other.y;

	return result;
}

Vector2 window_RealPos = RealPosition({ 1, 1 });
Color windowColor = { 0,0,0,1 };

char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf; // Return the buffer
}