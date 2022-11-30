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
	//uniform_real_distribution<GLclampf> randomScale(0.1f, 1/transform.worldScale.x * 1.5);
	uniform_real_distribution<GLclampf> randomScale(0.1f, 5);
	uniform_int_distribution<int> randomScaleSpeed(0, 1 + 1);

	transform.worldScale *= 0.2;

	wall_Object = new Cube*[wall_number.y];
	for (int i = 0; i < wall_number.y; i++)
		wall_Object[i] = new Cube[wall_number.x];

	for (int y = 0; y < wall_number.y; y++)
	{
		for (int x = 0; x < wall_number.x; x++)
		{
			wall_Object[y][x].transform.worldPosition.x = x - wall_number.x / 2 + 0.5;
			wall_Object[y][x].transform.worldPosition.z = y - wall_number.y / 2 + 0.5;

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

	Handle_Evnet(key);
	Handle_Evnet(specialKey);
}

void GL_Maze::Handle_Evnet(unsigned char key)
{
	switch (key)
	{
	case 'm':
		isRandomScaleMoveing = !isRandomScaleMoveing;
		break;

	case '=':
		scaleMovingSpeed++;
		if (scaleMovingSpeed > 10)
			scaleMovingSpeed = 10;
		else if (scaleMovingSpeed < 0)
			scaleMovingSpeed = 0;
		else if (scaleMovingSpeed == 0)
			scaleMovingSpeed++;
		for (int y = 0; y < wall_number.y; y++) 
		{
			for (int x = 0; x < wall_number.x; x++)
			{
				if(wall_Object[y][x].yScaleSpeed >= 0)
					wall_Object[y][x].yScaleSpeed = scaleMovingSpeed;
				else if (wall_Object[y][x].yScaleSpeed < 0)
					wall_Object[y][x].yScaleSpeed = -scaleMovingSpeed;
			}
		}
		
		break;
	case '-':
		scaleMovingSpeed--;
		if (scaleMovingSpeed > 10)
			scaleMovingSpeed = 10;
		else if (scaleMovingSpeed < 0)
			scaleMovingSpeed = 0;
		else if (scaleMovingSpeed == 0)
			scaleMovingSpeed++;
		for (int y = 0; y < wall_number.y; y++)
		{
			for (int x = 0; x < wall_number.x; x++)
			{
				if (wall_Object[y][x].yScaleSpeed >= 0)
					wall_Object[y][x].yScaleSpeed = -scaleMovingSpeed;
				else if (wall_Object[y][x].yScaleSpeed < 0)
					wall_Object[y][x].yScaleSpeed = scaleMovingSpeed;

			}
		}
		break;
	case 'v':
		if (isRandomScaleMoveing)
		{
			isRandomScaleMoveing = false;
			SetWall_YScale(2.0f);
		}
		else
			isRandomScaleMoveing = true;
		break;
	default:
		break;
	}
}

void GL_Maze::Handle_Evnet(int specialKey)
{
}

void GL_Maze::ReSet()
{
	SetWall_YScale(2.0f);
	isRandomScaleMoveing = false;
	for (int y = 0; y < wall_number.y; y++)
	{
		for (int x = 0; x < wall_number.x; x++)
		{
			wall_Object[y][x].SetActive(true);
		}
	}

}

void GL_Maze::MakeMaze()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> exitX(1, wall_number.x - 2);
	uniform_int_distribution<int> exitY(1, wall_number.y - 2);
	uniform_int_distribution<int> randomBool(0, 1 + 1);
	int count = (wall_number.x + wall_number.y - 4) / 2;
	uniform_int_distribution<int> randomCount(0, count - 1);

	Position2* mazeDotPos = new Position2[count];
	Position2 pivot_Maze = { wall_number.x / 2, wall_number.y / 2 };

	for (int y = 0; y < wall_number.y; y++)
		for (int x = 0; x < wall_number.x; x++)
			wall_Object[y][x].SetActive(true);
	
	Position2 mazeExit = { 1,1 };
	if (randomBool(gen) > 0)
		mazeExit.x = exitX(gen);
	else
		mazeExit.y = exitY(gen);
	wall_Object[mazeExit.y - 1][mazeExit.x].SetActive(false);
	wall_Object[mazeExit.y][mazeExit.x - 1].SetActive(false);
	wall_Object[mazeExit.y][mazeExit.x].SetActive(false);
	
	wall_Object[pivot_Maze.y][pivot_Maze.x].SetActive(false);
	for (int i = 0; i < count; i++)
		mazeDotPos[i] = { exitX(gen), exitY(gen) };

	{	//시작점과 출구 연결해주기
		for (int y = pivot_Maze.y; y != mazeExit.y; (pivot_Maze.y - mazeExit.y > 0) ? y-- : y++)
			wall_Object[y][pivot_Maze.x].SetActive(false);
		wall_Object[mazeExit.y][pivot_Maze.x].SetActive(false);

		for (int x = pivot_Maze.x; x != mazeExit.x; (pivot_Maze.x - mazeExit.x > 0) ? x-- : x++)
			wall_Object[mazeExit.y][x].SetActive(false);
		wall_Object[mazeExit.y][mazeExit.x].SetActive(false);
	}
	for (int i = 0; i < count; i++)
	{
		// 시작점과 모든 정점 연결해주기
		for (int y = pivot_Maze.y; y != mazeDotPos[i].y; (pivot_Maze.y - mazeDotPos[i].y > 0) ? y-- : y++)
			wall_Object[y][pivot_Maze.x].SetActive(false);
		wall_Object[mazeDotPos[i].y][pivot_Maze.x].SetActive(false);

 		for (int x = pivot_Maze.x; x != mazeDotPos[i].x; (pivot_Maze.x - mazeDotPos[i].x > 0) ? x-- : x++)
			wall_Object[mazeDotPos[i].y][x].SetActive(false);
		wall_Object[mazeDotPos[i].y][mazeDotPos[i].x].SetActive(false);
		
		// i번쨰 정점과 랜덤한 정점 1개를 연결해주기
		int rc = i + 1;
		if (rc >= count)
			return;
		for (int y = mazeDotPos[i].y; y != mazeDotPos[rc].y; (mazeDotPos[i].y - mazeDotPos[rc].y > 0) ? y-- : y++)
			wall_Object[y][mazeDotPos[i].x].SetActive(false);
		for (int x = mazeDotPos[i].x; x != mazeDotPos[rc].x; (mazeDotPos[i].x - mazeDotPos[rc].x > 0) ? x-- : x++)
			wall_Object[mazeDotPos[rc].y][x].SetActive(false);
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
			if (!wall_Object[y][x].ActiveSelf())
				continue;

			if (wall_Object[y][x].transform.worldScale.y < 0.1f)
				wall_Object[y][x].yScaleSpeed = scaleMovingSpeed;
			else if (wall_Object[y][x].transform.worldScale.y > 5)
				wall_Object[y][x].yScaleSpeed = -scaleMovingSpeed;

			wall_Object[y][x].transform.worldScale.y += wall_Object[y][x].yScaleSpeed * FrameTime::oneFrame;
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
