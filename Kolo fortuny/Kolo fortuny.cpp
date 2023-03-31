#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <string>

using namespace std;

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

string slowa[10] = { "pies","kot","klawiatura","tranzystor","kondensator","myszka","komputer","lampka","monitor","glowa" };

//Wypełnainie tablic

string PolaWypelniania(int x, int y, string z)
{
    int* wypelnianie;
    string* porownanie;
    std::string PustePole = "_";

    wypelnianie = new int[x];
    porownanie = new string[x];

    for (int i = 0; i < x; i++)
    {
        porownanie[i] = slowa[y][i];

        if (porownanie[i] == z)
        {
            wypelnianie[i] = 1;
        }
        else
        {
            wypelnianie[i] = 0;
        }

    }

    for (int i = 0; i < x; i++)
    {
        if (wypelnianie[i] == 0 && !(wypelnianie[i] == 1))
        {
            return PustePole;
        }
        else
        {
            string literka = porownanie[i];
            return literka;
        }
    }
}

//Odgadywanie hasła

bool OdgadnijHaslo(string x, string z)
{
    if (z == x) 

    return true;

    else 

    return false;
}

int main()
{
    srand(time(NULL));

    int pozycja = rand() % 10;
    int IloscLiter = slowa[pozycja].length();
    int wybor;

    string Haslo, Litera;
    std::string PustePole = "_";
    string PokazywanieLiterek[25];
    string TabPorownanieZwpisem[25];

    bool End = true;

    //Wypelnianie tablicy z porownaniem

    for (int i = 0; i < IloscLiter; i++)
    {
        TabPorownanieZwpisem[i] = slowa[pozycja][i];
    }

    // Animacja generowania hasła

    textColor('G');
    cout << "------- GENEROWANIE HASLA -------" << endl;

    for (int i = 0; i < 10; i++)
    {
        cout << "---------------------------------" << endl;
        Sleep(100);
    }
    system("cls");


    while (End)
    {
        //Program własciwy

        textColor();
        cout << "********* KOLO FORTUNY **********" << endl;

        cout << "liczba liter to: " << IloscLiter << endl;
        Sleep(100);

        cout << "*********************************" << endl << endl;

        //Rysowanie pola wypelniania

        textColor('G');
        cout << "[ ";
        for (int i = 0; i < IloscLiter; i++)
        {
            int check;

            if (PolaWypelniania(IloscLiter, pozycja, Litera) == TabPorownanieZwpisem[i])
            {
                check = 1;
            }
            else
            {
                check = 0;
            }

            if (check ==1)
            {
               PokazywanieLiterek[i] = PolaWypelniania(IloscLiter, pozycja, Litera);
            }
            else
            {
                PokazywanieLiterek[i] = PustePole;
            }

            cout << PokazywanieLiterek[i] << " ";
        }
        cout << "]" << endl << endl;

        cout << slowa[pozycja] << endl;

        textColor();
        cout << "*********************************" << endl << endl;

        //////////////////////////////

        cout << "1. Podaj litere" << endl;
        cout << "2. Odgadnij haslo" << endl;
        textColor('R');
        cout << "co chcesz zrobic: "; cin >> wybor;


        switch (wybor)
        {
        case 1:
            textColor();
            cout << "Podaj litere: "; cin >> Litera;

            Sleep(100);

            system("cls");
            break;
        case 2:
            textColor();
            cout << "Podaj haslo: "; cin >> Haslo;

            if (OdgadnijHaslo(slowa[pozycja], Haslo) == true)
            {
                
                cout << "[ Brawo!]";

                Sleep(300);
                End = false;
            }
            else
            {
                cout << "[ Zle! ]";
                Sleep(300);
            }

            Sleep(800);

            system("cls");
            break;

        default:
            system("cls");

            textColor('R');
            cout << "podaj liczbe z zakresu 1-2!" << endl;
            textColor();
           
            exit(0);

            break;

        }

    }

    return 0;
}

