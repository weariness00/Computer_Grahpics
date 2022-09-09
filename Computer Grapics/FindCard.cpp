#include "FindCard.h"

FindCardGame::FindCardGame()
{
	Init(cardBoard);
	Init(openBoard);
	isEnd = false;
}

FindCardGame::~FindCardGame()
{
}

void FindCardGame::Update()
{
	SetBoard(cardBoard);
	count = MaxCount;
	score = 0;
	while (count)
	{
		system("cls");
		PrintBoard(openBoard);
		cout << "남은 횟수 : " << count << endl;
		cout << "score : " << score << endl;
		OpenCard();
		if (isEnd)
		{
			cout << "게임을 리셋 합니다." << endl;
			system("pause");
			Update();
			break;
		}
		count--;
	}
}

void FindCardGame::Init(char board[][MaxLen])
{
	for (int y = 0; y < MaxLen; y++)
		for (int x = 0; x < MaxLen; x++)
			board[y][x] = '*';
}

void FindCardGame::SetBoard(char board[][MaxLen])
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, MaxLen*MaxLen - 1);
	char* number = new char[MaxLen * MaxLen];
	stack<char> card;

	char temp;
	int random;
	int ask = 0;
	for (int i = 0; i < MaxLen * MaxLen; i += 2)
	{
		number[i] = 65 + ask;
		number[i + 1] = 65 + ask;
		ask++;
	}

	for (int i = 0; i < MaxLen * MaxLen; i++)
	{
		random = dis(gen);
		temp = number[random];
		number[random] = number[i];
		number[i] = temp;
	}

	for (int i = 0; i < MaxLen*MaxLen; i++)
	{
		card.push(number[i]);
	}

	for (int y = 0; y < MaxLen; y++)
	{
		for (int x = 0; x < MaxLen; x++)
		{
			board[y][x] = card.top();
			card.pop();
		}
	}
}

void FindCardGame::PrintBoard(char board[][MaxLen])
{
	cout << "\t";
	for (int i = 0; i < MaxLen; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << char(97 + i) << "\t";
	}
	cout << endl << endl;

	for (int y = 0; y < MaxLen; y++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << y << "\t";
		for (int x = 0; x < MaxLen; x++)
		{
			if(65 <= board[y][x]&& board[y][x] <= 90)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)board[y][x] - 64);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << board[y][x] << "\t";
		}
		cout << endl;
	}
}

void FindCardGame::OpenCard()
{
	int x[2], y[2];
	string input[2];

	cout << "input_01 : ";
	cin >> input[0];
	cout << "input_02 : ";
	cin >> input[1];

	for (int i = 0; i < 2; i++)
	{
		x[i] = input[i][0] - 97;
		y[i] = input[i][1] - 48;
	}

	for (int i = 0; i < 2; i++)
	{
		if (input[i][0] == 'r')
		{
			isEnd = true;
			return;
		}
	}

	for (int i = 0; i < 2; i++)
		openBoard[y[i]][x[i]] = '0';

	system("cls");
	PrintBoard(openBoard);

	cout << "아무키를 누르면 카드를 오픈 합니다." << endl;
	_getch();

	for (int i = 0; i < 2; i++)
		openBoard[y[i]][x[i]] = cardBoard[y[i]][x[i]];

	system("cls");

	PrintBoard(openBoard);

	if (openBoard[y[0]][x[0]] == openBoard[y[1]][x[1]])
	{
		cout << "카드를 맞추셨습니다." << endl;
		score += count + 1;
	}
	else
	{
		cout << "카드를 맞추시지 못하였습니다." << endl;
		for (int i = 0; i < 2; i++)
			openBoard[y[i]][x[i]] = '*';
	}
	cout << "계속하려면 아무키나 눌러주십시오" << endl;
	system("pause");
}
