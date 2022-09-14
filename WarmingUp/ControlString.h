#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <sstream>
#include <regex>

using namespace std;

#pragma warning(disable : 4996)

namespace CS 
{
	void StringReverse(list<string>& text);
	void Insert(list<string>& text, int interval, string symbol, bool& isInsert);
	void SpaceStandardReverse(list<string>& text, string symbol, bool isInsert);
	void ChangeCharacter(list<string>& text, string searchWord, string changeWord);
	void FIndSameWordFrontOfBack(list<string>& text);
	void PrintMenu();
}
