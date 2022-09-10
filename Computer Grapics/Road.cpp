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
			cout << setw(i + 1);
			if (board[y][x] == numberSize - 1)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				
			 cout << board[y][x];
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << endl;
	}
}

void Road::SetRoad()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(false, true);
	std::uniform_int_distribution<int> MC(1, 8);

	numberSize = 1;
	Position maxMove;
	Position increase_Pos;
	Position value_Pos;
	maxMove = value_Pos = increase_Pos = { 0,0 };
	board[increase_Pos.y][increase_Pos.x] = numberSize++;

	int moveCount = 0;
	bool buf = false;
	while(true)
	{		
		moveCount = MC(gen);
		increase_Pos = { 0,0 };

		(dis(gen)) ? ((dis(gen) ? increase_Pos.x++ : increase_Pos.x--)) : ((dis(gen) ? increase_Pos.y++ : increase_Pos.y--));

		if (abs(increase_Pos.x) == 1)
			maxMove.x += moveCount * increase_Pos.x;
		else if (abs(increase_Pos.y) == 1)
			maxMove.y += moveCount * increase_Pos.y;

		if (abs(maxMove.x) < 8 && abs(maxMove.y) < 8)
		{
			if (increase_Pos.x > 0)
			{
				if (maxMove.x < 0)
					maxMove.x = 0;

				maxMove.x += moveCount * increase_Pos.x;
				maxMove.y = 0;
			}
			else if (increase_Pos.x < 0)
			{
				if (maxMove.x > 0)
					maxMove.x = 0;

				maxMove.x += moveCount * increase_Pos.x;
				maxMove.y = 0;
			}
			else if (increase_Pos.y > 0)
			{
				if (maxMove.y < 0)
					maxMove.y = 0;

				maxMove.y += moveCount * increase_Pos.y;
				maxMove.x = 0;
			}
			else if (increase_Pos.y < 0)
			{
				if (maxMove.y > 0)
					maxMove.y = 0;

				maxMove.y += moveCount * increase_Pos.y;
				maxMove.x = 0;
			}
		}
		else
		{
			if (abs(increase_Pos.x) == 1)
				maxMove.x -= moveCount * increase_Pos.x;
			else if (abs(increase_Pos.y) == 1)
				maxMove.y -= moveCount * increase_Pos.y;
			continue;
		}
			

		for (int i = 0; i < moveCount; i++)
		{
			if ((value_Pos.x + increase_Pos.x < 0 || value_Pos.x + increase_Pos.x >= MaxLen) ||
				(value_Pos.y + increase_Pos.y < 0 || value_Pos.y + increase_Pos.y >= MaxLen))
				break;
			
			system("cls");
			cout << moveCount << endl;
			cout << "a ¸¦ ´©¸¦¾¾ ½ºµh" << endl;
			PrintBoard();
			if (!buf)
			{
				char buffer = _getch();
				if (buffer == 'a')
					buf = true;
			}

			value_Pos.x += increase_Pos.x;
			value_Pos.y += increase_Pos.y;
			board[value_Pos.y][value_Pos.x] = numberSize++;

			if (value_Pos.x == MaxLen - 1 &&
				value_Pos.y == MaxLen - 1)
				return;
		}
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
