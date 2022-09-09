#include "ControlString.h"

void StringReverse(list<string>& text)
{
    list<string> copyText;

    string line;

    for (auto str = text.rbegin(); str != text.rend(); str++)
    {
        line = *str;
        reverse(line.begin(), line.end());
        copyText.push_front(line);
    }

    while (!text.empty())
        text.pop_front();

    text = copyText;
}

void Insert(list<string>& text, int interval, string symbol, bool& isInsert)
{
    list<string> copyText;
    string line;
    int count = 0;

    if (isInsert)
    {
        for (auto str = text.rbegin(); str != text.rend(); str++)
        {
            line = *str;
            for (int i = 0; i < symbol.length(); i++)
                line.erase(remove(line.begin(), line.end(), symbol[i]), line.end());
            copyText.push_front(line);
        }

        while (!text.empty())
            text.pop_front();

        text = copyText;
        isInsert = false;
        return;
    }

    for (auto str = text.rbegin(); str != text.rend(); str++)
    {
        line = *str;
        count = -1;
        for (int i = 0; i < line.length(); i++)
        {
            count++;
            if (count != interval)
                continue;

            line.insert(i, symbol);
            i += symbol.length();
            count = 0;
        }
        copyText.push_front(line);
    }

    while (!text.empty())
        text.pop_front();

    text = copyText;
    isInsert = true;
}

void SpaceStandardReverse(list<string>& text, string symbol, bool isInsert)
{
    list<string> copyText;

    if (!isInsert)
    {
        string line;
        string word;

        for (auto str = text.rbegin(); str != text.rend(); str++)
        {
            stringstream ssline(*str);
            while (ssline >> word)
            {
                reverse(word.begin(), word.end());
                line += word + ' ';
            }

            copyText.push_front(line);
            line.clear();
        }

        while (!text.empty())
            text.pop_front();

        text = copyText;
        return;
    }

	string tokline;
	string line;
    string sWord;
	char* word;
	int count = 0;

	for (auto str = text.rbegin(); str != text.rend(); str++)
	{
		tokline = *str;
		char* tok = new char[tokline.length() + 1];

		tokline.copy(tok, tokline.length());
		tok[tokline.length()] = '\0';
		word = strtok(tok, symbol.c_str());

        sWord = word;
		reverse(sWord.begin(), sWord.end());
        line += sWord + symbol;

		while (true)
		{
			word = strtok(NULL, symbol.c_str());
			if (word == NULL)
				break;

            sWord = word;
            reverse(sWord.begin(), sWord.end());
			line += sWord + symbol;
		}

		copyText.push_front(line);
        line.clear();
	}

	while (!text.empty())
		text.pop_front();

	text = copyText;
}

void ChangeCharacter(list<string>& text, string searchWord, string changeWord)
{
    list<string> copyText;
    string line;

    for (auto str = text.rbegin(); str != text.rend(); str++)
    {
        line = *str;
        line = regex_replace(line, regex(searchWord), changeWord);
        copyText.push_front(line);
        line.clear();
    }

    while (!text.empty())
        text.pop_front();

    text = copyText;
}

void FIndSameWordFrontOfBack(list<string>& text)
{
    string front;
    string back;
    string line;

    string sameWord;

    for (auto str = text.rbegin(); str != text.rend(); str++)
    {
        line = *str;
        front = line.substr(0, line.length() / 2);
        back = line.substr(line.length() / 2, line.length());
        reverse(back.begin(), back.end());

        for (int i = 0; i < line.length()/2; i++)
        {
            if (front[i] == back[i])
                sameWord += front[i];
            else
                break;
        }

        if (!sameWord.empty())
        {
            cout << line << " : ";
            cout << sameWord << endl;
        }
        sameWord.clear();
    }
}

namespace ControlStringMenu
{
    void PrintMenu()
    {
        cout << "\n\n메뉴 목록입니다." << endl;
        cout << "d : 문장 전체를 뒤집기" << endl;
        cout << "e : 동일한 간격에 특수문자 삽입" << endl;
        cout << "f : 띄어쓰기를 기준으로 단어 뒤집기" << endl;
        cout << "g : 특정 문자를 다른 문자로 바꾸기" << endl;
        cout << "h : 앞뒤에서 읽었을 때 어디까지 같은 문자인지 출력하기" << endl;
        cout << "q : 프로그램 종료" << endl;
    }
}