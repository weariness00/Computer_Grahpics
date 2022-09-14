#pragma once
#include<iostream>
#include <random>
#include <windows.h>
#include <stack>
#include <conio.h>

#define MaxLen 4
#define MaxCount 15

using namespace std;

class FindCardGame {
public:
	FindCardGame();
	~FindCardGame();
public:
	void Update();

public:
	void Init(char board[][MaxLen]);
	void SetBoard(char board[][MaxLen]);
	void PrintBoard(char board[][MaxLen]);

public:
	void OpenCard();
public:
	char cardBoard[MaxLen][MaxLen];
	char openBoard[MaxLen][MaxLen];

	int score;
	int count;

	bool isEnd;
};
