#define MainNumber 7

#if MainNumber == 1
#include "Matrix.h"
#include <conio.h>

void PrintResult(Matrix& A, Matrix& B, Matrix& sum, char symbol);
void PrintMatrix(Matrix& matrix, int x, int y, string name);

int main()
{
    Matrix A, B;
    A.Init();
    B.Init();

    Matrix sum;
    char cmd;
    while (true)
    {
        system("cls");
        {
            gotoxy(0, 0);
            cout << "A";
            A.print(0, 1);
        }
        {
            gotoxy(A.matrix_X + 2, 0);
            cout << "B";
            B.print(A.matrix_X + 2, 1);
        }
        gotoxy(0, A.matrix_Y + 3);
        cout << "a : ����� ����" << endl;
        cout << "d : ����� ����" << endl;
        cout << "m : ����� ����" << endl;
        cout << "r : ��Ľ��� ��" << endl;
        cout << "t : ��ġ��� " << endl;
        cout << "h : ��� ũ�� �� ����" << endl;
        cout << "s : ��İ� ���� �缳��" << endl;
        cout << "q : ���α׷� ����" << endl;

        cmd = _getch();

        if (cmd == 'a' || cmd == 'A') // ���ϱ�
        {
            sum.ReSize(A.matrix_X, A.matrix_Y);
            sum.matrix_Index = A.Plus(B);
            PrintResult(A, B, sum, '+');

            gotoxy(0, A.matrix_Y + 5);
            cout << "�ƹ�Ű�� ������ �� ȭ������ �ǵ��� �ɴϴ�." << endl;
            system("pause");
        }
        else if (cmd == 'd' || cmd == 'D')
        {
            sum.ReSize(A.matrix_X, A.matrix_Y);
            sum.matrix_Index = A.Minus(B);
            PrintResult(A, B, sum, '-');

            gotoxy(0, A.matrix_Y + 5);
            cout << "�ƹ�Ű�� ������ �� ȭ������ �ǵ��� �ɴϴ�." << endl;
            system("pause");
        }
        else if (cmd == 'm' || cmd == 'M')
        {
            sum.ReSize(A.matrix_X, A.matrix_Y);
            sum.matrix_Index = A.Multiplication(B);
            PrintResult(A, B, sum, '*');

            gotoxy(0, A.matrix_Y + 5);
            cout << "�ƹ�Ű�� ������ �� ȭ������ �ǵ��� �ɴϴ�." << endl;
            system("pause");
        }
        else if (cmd == 'r' || cmd == 'R')
        {
            system("cls");
            PrintMatrix(A, 0, 0, "A");
            gotoxy(A.matrix_X + 1, A.matrix_Y / 2 + 1);
            cout << "= " << A.determinant(A.matrix_Index, A.matrix_X);

            PrintMatrix(B, A.matrix_X + B.matrix_X + 2, 0, "B");
            gotoxy(A.matrix_X + B.matrix_X + 5, B.matrix_Y / 2 + 1);
            cout << "= " << B.determinant(B.matrix_Index, B.matrix_X);

            gotoxy(0, A.matrix_Y + B.matrix_Y + 5);
            cout << "�ƹ�Ű�� ������ �� ȭ������ �ǵ��� �ɴϴ�." << endl;
            system("pause");
        }
        else if (cmd == 't' || cmd == 'T')
        {
            system("cls");

            PrintMatrix(A, 0, 0, "A");
            A.Transposed();
            PrintMatrix(A, A.matrix_X + 1, 0, "A(T)");
            gotoxy(A.matrix_X * 2 + 1, A.matrix_Y / 2 + 1);
            cout << "= " << A.determinant(A.matrix_Index, A.matrix_X);

            PrintMatrix(B, 0, A.matrix_Y + 2, "B");
            B.Transposed();
            PrintMatrix(B, B.matrix_X + 1, A.matrix_Y + 2, "B(T)");
            gotoxy(A.matrix_X * 2 + 1, A.matrix_Y + 4);
            cout << "= " << B.determinant(B.matrix_Index, B.matrix_X);

            gotoxy(0, A.matrix_Y + B.matrix_Y + 5);
            cout << "�ƹ�Ű�� ������ �� ȭ������ �ǵ��� �ɴϴ�." << endl;
            system("pause");
        }
        else if (cmd == 'h' || cmd == 'H')
        {
            system("cls");
            int sizeX, sizeY;
            char matrix_Name;
            cout << "�ٲ� size�� �����ֽÿ�" << endl;
            cout << "���� : ";
            cin >> sizeX;
            cout << "���� : ";
            cin >> sizeY;
            cout << endl;
            cout << "�ٲ� Matrix�� �����ֽÿ�" << endl;
            cout << "A, B �ܿ� �ٸ� Ű �Է½� A,B �� ������ ������" << endl;
            cin >> matrix_Name;
            if (matrix_Name == 'a' || matrix_Name == 'A')
                A.ReSize(sizeX, sizeY);
            else if (matrix_Name == 'b' || matrix_Name == 'B')
                B.ReSize(sizeX, sizeY);
            else
            {
                A.ReSize(sizeX, sizeY);
                B.ReSize(sizeX, sizeY);
            }

            system("pause");
        }
        else if (cmd == 's' || cmd == 'S')
        {
            system("cls");
            cout << "���� �� ������ Matrix�� ����ֽÿ�" << endl;
            cout << "A, B �ܿ� �ٸ� Ű �Է½� A,B �� �� ������" << endl;

            char matrix_Name;
            cin >> matrix_Name;
            if (matrix_Name == 'a' || matrix_Name == 'A')
                A.Init();
            else if (matrix_Name == 'b' || matrix_Name == 'B')
                B.Init();
            else
            {
                A.Init();
                B.Init();
            }
            system("pause");
        }
        
        if (cmd == 'q' || cmd == 'Q')
            break;
    }
}

void PrintMatrix(Matrix& matrix, int x, int y, string name)
{
    gotoxy(x, y);
    cout << name;
    matrix.print(x, y + 1);
}

void PrintResult(Matrix& A, Matrix& B, Matrix& sum, char symbol)
{
    system("cls");
    PrintMatrix(A, 0, 0, "A");

    gotoxy(A.matrix_X + 1, A.matrix_Y/2 + 1);
    cout << symbol;

    PrintMatrix(B, A.matrix_X + 2, 0, "B");

    gotoxy(A.matrix_X + B.matrix_X + 3, B.matrix_Y / 2 + 1);
    cout << "=";

    PrintMatrix(sum, A.matrix_X + B.matrix_X + 4, 0, "sum");
}
#elif MainNumber == 2
#include "LoadFile.h"

#define FileName "Data.txt"

int main()
{
    list<string>* text = new list<string>;

    LoadData(*text, FileName);

    PrintText(*text);

    int wordCount = CountWord(*text);
    int numberCount = CountNumber(*text);
    int upperCount = CountUpper(*text);
    cout << "word : " << wordCount << endl;
    cout << "number : " << numberCount << endl;
    cout << "upper : " << upperCount << endl;
}
#elif MainNumber == 3
#include "LoadFile.h"
#include "ControlString.h"
#include<conio.h>  

#define FileName "Data.txt"
string symbol = "@@";

using namespace CS;

int main()
{
    list<string>* text = new list<string>;
    LoadData(*text, FileName);

    char cmd;
    bool isInsert = false;
    while (true)
    {
        system("cls");
        PrintText(*text);
        PrintMenu();
        cmd = _getch();

        system("cls");
        if (cmd == 'q' || cmd == 'Q')
            break;
        else if (cmd == 'd' || cmd == 'D')
        {
            StringReverse(*text);
        }
        else if (cmd == 'e' || cmd == 'E')
        {
            Insert(*text, 4, symbol, isInsert);
        }
        else if (cmd == 'f' || cmd == 'F')
        {
            SpaceStandardReverse(*text, symbol, isInsert);     
        }
        else if (cmd == 'g' || cmd == 'G')
        {
            PrintText(*text);
            cout << endl;
            string searchWord;
            string changeWord;
            
            cout << "Search Word : ";
            cin >> searchWord;
            cout << "Change Word : ";
            cin >> changeWord;
            ChangeCharacter(*text, searchWord, changeWord);
        }
        else if (cmd == 'h' || cmd == 'H')
        {
            PrintText(*text);
            cout << endl;
            FIndSameWordFrontOfBack(*text);
            cout << "\n�ƹ� Ű �Է½� �޴��� ���ư��ϴ�." << endl;
            system("pause");
            continue;
        }

        PrintText(*text);
        cout << "\n�ƹ� Ű �Է½� �޴��� ���ư��ϴ�." << endl;
        system("pause");
    }
}

#elif MainNumber == 4
#include"RectangleCollider.h"

using namespace RC;

#define MoveLenth 10

int main()
{
    RectangleCollider rectangle[2];

    bool A_B = false; // true A , false B
    Position movePos;
    char cmd;
    while (true)
    {
        system("cls");
        cout << "���� Rect " << A_B + 1 << "�� ������ ����" << endl;
        cout << "����Ű �Է½� " << MoveLenth << " ��ŭ �̵�" << endl;
        cout << "q : ���α׷� ����" << endl;
        cout << "Rect 1 : ";
        rectangle[0].PrintDot();
        cout << endl;
        cout << "Rect 2 : ";
        rectangle[1].PrintDot();
        cout << endl;

        movePos = { 0,0 };
        cmd = _getch();

        if (cmd == -32)
            cmd = _getch();

        if (cmd == 'q' || cmd == 'Q')
            break;
        else if (cmd == 75) // <- Left
        {
            movePos = { -MoveLenth, 0 };
        }
        else if (cmd == 77) // -> Right
        {
            movePos = { MoveLenth, 0 };
        }
        else if (cmd == 72) // ^ Up
        {
            movePos = { 0, MoveLenth };
        }
        else if (cmd == 80) // V Down
        {
            movePos = { 0, -MoveLenth };
        }
        rectangle[A_B].Move(movePos);
        rectangle[A_B].CheckCollider(rectangle[!A_B]);
        A_B = !A_B;

        cout << "�ƹ�Ű �Է½� ��� ����" << endl;
        system("pause");
    }
}

#elif MainNumber == 5
#include"List.h"

using namespace ListMenu;

int main()
{
    List list;
    NecessaryData data;
    char cmd;

    Init_List(list, data);

    while (true)
    {
        system("cls");
        PrintMenu();

        cmd = _getch();

        if (cmd == 'q' || cmd == 'Q') 
            break;
        else if (cmd == '+')
        {
            Push_Front(list,data);
        }
        else if (cmd == '-')
        {
            Pop_Front(list, data);
        }
        else if (cmd == 'e' || cmd == 'E')
        {
            Push_Back(list, data);
        }
        else if (cmd == 'd' || cmd == 'D')
        {
            Pop_Back(list, data);
        }
        else if (cmd == 'c' || cmd == 'C')
        {
            data.top = data.bottom = 0;
        }
        else if (cmd == 'm' || cmd == 'M')
        {
            FindFarDot(list, data);
        }
        else if (cmd == 'n' || cmd == 'N')
        {
            FindNearDot(list, data);
        }
        else if (cmd == 's' || cmd == 'S')
        {
            SortList(list, data);
        }
        else if (cmd == 'l' || cmd == 'L')
        {
            cout << "\n���� ���� : " << data.top - data.bottom << endl;
        }
        system("pause");
    }
}

#elif MainNumber == 6
#include "Road.h"

int main()
{
    Road road;
    char cmd;

    while (true)
    {
        system("cls");

        road.PrintBoard();
        cout << endl;
  
        cout << "r : ��� �� ����" << endl;
        cout << "����Ű : �������� �� ��� �̵�" << endl;
        cout << "q : ���α׷� ����" << endl;

        cmd = _getch();

        if (cmd == -32)
            cmd = _getch();

        system("cls");

        if (cmd == 'q' || cmd == 'Q')
            break;
        else if (cmd == 'r' || cmd == 'R')
        {
            road.Init();
            road.SetRoad();
        }
        else if (cmd == 75) // <-
        {
            road.MoveBoard(true);        
        }
        else if (cmd == 77) // ->
        {
            road.MoveBoard(false);
        }

        system("cls");
        road.PrintBoard();

        system("pause");
    }
}
#elif MainNumber == 7
#include "FindCard.h"

int main()
{
    FindCardGame game;
    game.Update();
}
#endif // 0
