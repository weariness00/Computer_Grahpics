#pragma once
#include<iostream>
#include<random>
#include<conio.h>

using namespace std;

namespace RC 
{
	struct Position
	{
		int x;
		int y;
	};

	class RectangleCollider
	{
	public:
		RectangleCollider();
		~RectangleCollider();

	public:
		void Init();
		void SetDotRandom();
		void PrintDot();
		
	public:
		void Move(Position moveIndex);
		void CheckCollider(RectangleCollider other);

	public:
		const Position GetDot(int i) { return dot[i]; };
		Position SetDot(int i, Position value) { dot[i] = value; };

	private:
		Position dot[2];
	};
}