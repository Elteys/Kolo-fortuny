#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <string>
#include <typeinfo>

void textColor(char c = 'W')
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    auto colors = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; //default white gray
    switch (c) {
    case 'Y': //yellow
        colors = FOREGROUND_RED | FOREGROUND_GREEN;
        break;
    case 'R':
        colors = 12;
        break;
    case 'G':
        colors = FOREGROUND_GREEN;
        break;
    case 'B':
        colors = FOREGROUND_BLUE | FOREGROUND_GREEN;
        break;
    case 'P':
        colors = FOREGROUND_RED | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
    }
    SetConsoleTextAttribute(hStdOut, colors);
}

using namespace std;

string slowa[10] = { "pies","kot","klawiatura","tranzystor","kondensator","myszka","komputer","lampka","monitor","glowa"};

void PolaWypelniania(int x)
{
    int* wypelnianie;

    wypelnianie = new int[x];

    for (int i = 0; i < x; i++)
    {
        wypelnianie[i] = 0;
    }

    for (int i = 0; i < x; i++)
    {
        if (wypelnianie[i] == 0)
        {
            cout << "_ ";
        }
    }

}

int main()
{
    srand(time(NULL));

    int x = rand() % 10;

    int IloscLiter = slowa[x].length();
    string Litera;

    textColor('G');
    cout << "------- GENEROWANIE HASLA -------" << endl;

    for(int i = 0; i < 10; i++)
    {
        cout << "---------------------------------" << endl;
        Sleep(100);
    }
    system("cls");
    
    textColor();
    cout << "********* KOLO FORTUNY **********" << endl;

    cout << "liczba liter to: " << IloscLiter << endl;
    Sleep(100);

    cout << "*********************************" << endl << endl;

    textColor('G');
    cout << "[ ";  PolaWypelniania(IloscLiter); cout << "]" << endl << endl;

    textColor();
    cout << "Podaj pierwsza litere: "; cin >> Litera;





    












  
    return 0;
}

