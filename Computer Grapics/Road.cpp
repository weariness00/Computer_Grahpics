#include "Road.h"

Road::Road()
{
	Init();
}

Road::~Road()
{
}

void Road::Init()
{
	for (int y = 0; y < MaxLen; y++)
		for (int x = 0; x < MaxLen; x++)
			board[y][x] = 0;

	numberSize = 0;
}

void Road::PrintBoard()
{
	int size = numberSize;
	int i = 0;
	while (size)
	{
		size = size / 10;
		i++;
	}
	for (int y = 0; y < MaxLen; y++)
	{
		for (int x = 0; x < MaxLen; x++)
		{
			cout << setw(i + 1) << board[y][x];
		}
		cout << endl;
	}
}

void Road::SetRoad()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(false, true);

	numberSize = 1;
	Position maxMove;
	Position pos;
	maxMove.x = maxMove.y = 0;
	pos.x = pos.y = 0;
	board[pos.y][pos.x] = numberSize++;

	bool buf = false;
	bool move;
	while(true)
	{		
		system("cls");
		cout << "a ¸¦ ´©¸¦¾¾ ½ºµh" << endl;
		PrintBoard();
		if (!buf)
		{
			char buffer = _getch();
			if (buffer == 'a')
				buf = true;
		}		

		move = dis(gen);
		if (abs(maxMove.x) == 8)
			move = false;
		else if (abs(maxMove.y) == 8)
			move = true;

		if (move)
		{
			move = dis(gen);
			if (pos.x >= MaxLen - 1)
				move = false;
			else if (pos.x <= 0)
				move = true;

			if (move)
			{
				pos.x++;

				if (maxMove.x < 0)
					maxMove.x = 0;
				maxMove.x++;	
			}
			else 
			{
				pos.x--;

				if (maxMove.x > 0)
					maxMove.x = 0;
				maxMove.x--;		
			}
			maxMove.y = 0;
		}
		else 
		{
			move = dis(gen);
			if (pos.y >= MaxLen - 1)
				move = false;
			else if (pos.y <= 0)
				move = true;

			if (move)
			{
				pos.y++;

				if (maxMove.y < 0)
					maxMove.y = 0;
				maxMove.y++;
			}
			else
			{
				pos.y--;

				if (maxMove.y > 0)
					maxMove.y = 0;
				maxMove.y--;		
			}
			maxMove.x = 0;
		}

		board[pos.y][pos.x] = numberSize++;

		if (pos.x == MaxLen - 1 &&
			pos.y == MaxLen - 1)
			break;
	}
}

void Road::MoveBoard(bool dir)
{
	int temp[MaxLen];
	int tempPos;
	if (dir) // left
		tempPos = 0;
	else //right
		tempPos = MaxLen - 1;

	for (int i = 0; i < MaxLen; i++)
		temp[i] = board[i][tempPos];

	if (dir) // left
		tempPos = MaxLen - 1;
	else //right
		tempPos = 0;

	for (int y = 0; y < MaxLen; y++)
	{
		for (int x = 0; x < MaxLen; x++)
		{
			if (dir && x + 1 < MaxLen)
				board[y][x] = board[y][x + 1];
			else if(!dir && MaxLen - 2 - x >= 0)
				board[y][MaxLen - 1 - x] = board[y][MaxLen - 2 - x];
		}
		board[y][tempPos] = temp[y];
	}
}
