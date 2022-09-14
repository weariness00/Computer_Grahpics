#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

#pragma warning(disable : 4996)

void LoadData(list<string>& text, string name);
void PrintText(list<string>& text);
int CountWord(list<string> text);
int CountNumber(list<string> text);
int CountUpper(list<string> text);