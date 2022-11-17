#include "GL_Maze.h"

GL_Maze::GL_Maze()
{
	wall_Object = NULL;
	wall_number = { 0,0 };
}

GL_Maze::~GL_Maze()
{
	for (int i = 0; i < wall_number.y; i++)
		delete[] wall_Object[i];
	delete[] wall_Object;	
}

void GL_Maze::Init()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<GLclampf> randomScale(0.1f, 10.0f);
	uniform_int_distribution<int> randomScaleSpeed(0, 1 + 1);

	transform.worldScale *= 0.1;

	cin >> wall_number.x >> wall_number.y;

	wall_Object = new Cube*[wall_number.y];
	for (int i = 0; i < wall_number.y; i++)
		wall_Object[i] = new Cube[wall_number.x];

	for (int y = 0; y < wall_number.y; y++)
	{
		for (int x = 0; x < wall_number.x; x++)
		{
			wall_Object[y][x].transform.worldPosition.x = x - wall_number.x / 2;
			wall_Object[y][x].transform.worldPosition.z = y - wall_number.y / 2;

			float rScale_Y = randomScale(gen);
			wall_Object[y][x].transform.worldScale.y = rScale_Y;
			wall_Object[y][x].transform.worldPivot.y = rScale_Y / 2;

			if(randomScaleSpeed(gen) > 0)
				wall_Object[y][x].yScaleSpeed = 0.1f;
			else
				wall_Object[y][x].yScaleSpeed = -0.1f;
		}
	}
}

void GL_Maze::Update()
{
	RandomMovingScaleAnimaiton();

	for (int y = 0; y < wall_number.y; y++)
	{
		for (int x = 0; x < wall_number.x; x++)
		{
			wall_Object[y][x].transform.localPivot = transform.worldPivot;
			wall_Object[y][x].transform.localPosition = transform.worldPosition;
			wall_Object[y][x].transform.localRotation = transform.worldRotation;
			wall_Object[y][x].transform.localScale = transform.worldScale;
		}
	}
}

void GL_Maze::MakeMaze()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> exitX(0, wall_number.x);
	uniform_int_distribution<int> exitY(0, wall_number.y);
	uniform_int_distribution<int> randomBool(0, 1 + 1);

	for (int y = 0; y < wall_number.y; y++)
		for (int x = 0; x < wall_number.x; x++)
			wall_Object[y][x].isActive = true;

	Position2 mazeExit = {0,0};
	if (randomBool(gen) > 0)
		mazeExit.x = exitX(gen);
	else
		mazeExit.y = exitY(gen);
	wall_Object[mazeExit.x][mazeExit.y].isActive = false;

	Position2 load = { wall_number.x / 2, wall_number.y / 2 };
	bool loadXY;
	bool load_P_M;
	while (true)
	{
		loadXY = randomBool(gen);
		load_P_M = randomBool(gen);

		for (int i = 0; i < 3; i++)
		{
			if (load.x == mazeExit.x && load.y == mazeExit.y)
				return;

			if (load.x == 0)
				load.x += 2;
			else if (load.x == wall_number.x)
				load.x -= 2;
			else if (load.y == 0)
				load.y += 2;
			else if (load.y == wall_number.y)
				load.y -= 2;

			wall_Object[load.x][load.y].isActive = false;

			if ((load.x - 1 == 0 && load.y == mazeExit.y) ||
				(load.x == mazeExit.x && load.y - 1 == 0))
				return;

			if (loadXY)
			{
				if (load_P_M)
					load.x--;
				else
					load.x++;
			}
			else
			{
				if (load_P_M)
					load.y--;
				else
					load.y++;
			}
		}
	}
}

void GL_Maze::RandomMovingScaleAnimaiton()
{
	if (!isRandomScaleMoveing)
		return;

	for (int y = 0; y < wall_number.y; y++)
	{
		for (int x = 0; x < wall_number.x; x++)
		{
			if (wall_Object[y][x].transform.worldScale.y <= 0.1f)
				wall_Object[y][x].yScaleSpeed = 0.1f;
			else if (wall_Object[y][x].transform.worldScale.y >= 10.0f)
				wall_Object[y][x].yScaleSpeed = -0.1f;

			wall_Object[y][x].transform.worldScale.y += wall_Object[y][x].yScaleSpeed;
			wall_Object[y][x].transform.worldPivot.y = wall_Object[y][x].transform.worldScale.y / 2;
		}
	}
}

void GL_Maze::SetWall_YScale(float yScale)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<GLclampf> randomScale(-0.5f, 0.5f);

	for (int y = 0; y < wall_number.y; y++)
	{
		for (int x = 0; x < wall_number.x; x++)
		{
			wall_Object[y][x].transform.worldScale.y = yScale + randomScale(gen);
			wall_Object[y][x].transform.worldPivot.y = wall_Object[y][x].transform.worldScale.y / 2;
		}
	}
}
