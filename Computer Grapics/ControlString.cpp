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
        cout << "\n\n�޴� ����Դϴ�." << endl;
        cout << "d : ���� ��ü�� ������" << endl;
        cout << "e : ������ ���ݿ� Ư������ ����" << endl;
        cout << "f : ���⸦ �������� �ܾ� ������" << endl;
        cout << "g : Ư�� ���ڸ� �ٸ� ���ڷ� �ٲٱ�" << endl;
        cout << "h : �յڿ��� �о��� �� ������ ���� �������� ����ϱ�" << endl;
        cout << "q : ���α׷� ����" << endl;
    }
}