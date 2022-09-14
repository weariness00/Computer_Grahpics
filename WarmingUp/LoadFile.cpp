#include "LoadFile.h"

void LoadData(list<string>& text , string name)
{
    ifstream iFile(name);

    if (!iFile)
    {
        cout << "파일이 존재하지 않습니다." << endl;
        return;
    }

    while (!iFile.eof())
    {
        string str;
        getline(iFile, str);
        text.push_front(str);
    }
}

void PrintText(list<string>& text)
{
    for (auto str = text.rbegin(); str != text.rend(); str++)
    {
        cout << *str << endl;
    }
}

int CountWord(list<string> text)
{
    string line;
    char* word;
    int count = 0;

    for (auto str = text.rbegin(); str != text.rend(); str++)
    {
        line = *str;
        char* tok = new char[line.length() + 1];
        line.copy(tok, line.length());
        tok[line.length()] = '\0';
        word = strtok(tok, " ");
        for (int i = 0; i < strlen(word); i++)
        {
            if (word[i] < 48 || word[i] > 57)
            {
                count++;
                break;
            }
        }

        while (true)
        {
            word = strtok(NULL, " ");
            if (word == NULL)
                break;

            for (int i = 0; i < strlen(word); i++)
            {
                if (word[i] < 48 || word[i] > 57)
                {
                    count++;
                    break;
                }
            }
        }  
    }
    return count;
}

int CountNumber(list<string> text)
{
    string line;
    char* word;
    int count = 0;

    for (auto str = text.rbegin(); str != text.rend(); str++)
    {
        line = *str;
        char* tok = new char[line.length() + 1];
        line.copy(tok, line.length());
        tok[line.length()] = '\0';
        word = strtok(tok, " ");
        for (int i = 0; i < strlen(word); i++)
        {
            if (word[i] < 48 || word[i] > 57)
                break;
            if (i == strlen(word) - 1)
                count++;
        }
        while (true)
        {
            word = strtok(NULL, " ");
            if (word == NULL)
                break;
            for (int i = 0; i < strlen(word); i++)
            {
                if (word[i] < 48 || word[i] > 57)
                    break;
                if (i == strlen(word) - 1)
                    count++;
            }
        }
    }
    return count;
}

int CountUpper(list<string> text)
{
    string line;
    char* word;
    int count = 0;

    for (auto str = text.rbegin(); str != text.rend(); str++)
    {
        line = *str;
        char* tok = new char[line.length() + 1];
        line.copy(tok, line.length());
        tok[line.length()] = '\0';
        word = strtok(tok, " ");
        for (int i = 0; i < strlen(word); i++)
        {
            if (word[i] >= 65 && word[i] <= 90)
            {
                count++;
                break;
            }
        }
        while (true)
        {
            word = strtok(NULL, " ");
            if (word == NULL)
                break;
            for (int i = 0; i < strlen(word); i++)
            {
                if (word[i] >= 65 && word[i] <= 90)
                {
                    count++;
                    break;
                }
            }
        }
    }
    return count;
}
