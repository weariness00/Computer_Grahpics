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
}

void Road::PrintBoard()
{
	string numberLen = to_string(board[MaxLen - 1][MaxLen - 1]);
	int size = numberLen.length();
	for (int y = 0; y < MaxLen; y++)
	{
		for (int x = 0; x < MaxLen; x++)
		{
			cout << board[y][x] << "\t";
			for (int i = 0; i < size/5; i++)
			{
				cout << "\t";
			}
		}
		cout << endl;
	}
}

void Road::SetRoad()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(false, true);

	int i = 1;
	Position maxMove;
	Position pos;
	maxMove.x = maxMove.y = 0;
	pos.x = pos.y = 0;
	board[pos.y][pos.x] = i++;

	bool buf = false;
	bool move;
	while(true)
	{		
		system("cls");
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

		board[pos.y][pos.x] = i++;

		if (pos.x == MaxLen - 1 &&
			pos.y == MaxLen - 1)
			break;
	}
}
