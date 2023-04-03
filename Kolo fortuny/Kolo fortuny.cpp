#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h> /* srand, rand */
#include <time.h> /* time */
#include <fstream>
#include <string>
#include <cctype>

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

fstream kategoria[5];

//  Wypełnainie tablic

string wypelnianiePola(string Haslo, int i, string litera)
{
    int check = 0;

    string Wielka_litera, Mala_litera;
    string Tablica_Haslo = Haslo;
    string TabPorownanieZwpisem[25];
    std::string PustePole = "_";

        Mala_litera = towlower(int(litera[0]));
        Wielka_litera = toupper(int(litera[0]));

        TabPorownanieZwpisem[i] = Tablica_Haslo[i];

        if (Wielka_litera == TabPorownanieZwpisem[i] || Mala_litera == TabPorownanieZwpisem[i])
        {
            check = 1;
        }
        else
        {
            check = 0;
        }

        if (check == 1)
        {
            if (i == 0)
            {
                return Wielka_litera;
            }
            else
            {
                return Mala_litera;
            }
        }
        else
        {
            return PustePole;
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

// Porównywanie tablic

bool PorownajTablice(int rozmiar, string tab1[], string tab2[])
{
    for (int i = 0; i < rozmiar; i++) 
    {
        if (tab1[i] != tab2[i])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    kategoria[0].open("Zwierzeta.txt", ios::in);
    kategoria[1].open("Rosliny.txt", ios::in);
    kategoria[2].open("Sprzet.txt", ios::in);
    kategoria[3].open("Pojazdy.txt", ios::in);
    kategoria[4].open("Kraje.txt", ios::in);

    srand(time(NULL));
    int RandKategoria = rand() % 5;
    srand(time(NULL));
    int RandHaslo = rand() % 3;

    string Hasla[3];
    string Kategoria_Nazwa;

    string Haslo, Litera;
    string PustePole = "_";
    string PokazywanieLiterek[25];
    string TabPorownanieZwpisem[25];

    bool End = true;

    //Przypisywanie nazwy kategori

    switch (RandKategoria)
    {
    case 0:
        Kategoria_Nazwa = "Zwierzeta";
        break;

    case 1:
        Kategoria_Nazwa = "Rosliny";
        break;

    case 2:
        Kategoria_Nazwa = "Sprzet";
        break;

    case 3:
        Kategoria_Nazwa = "Pojazdy";
        break;

    case 4:
        Kategoria_Nazwa = "Kraje";
        break;
    }
    

    //Losowanie kategorii i hasła

    if (kategoria[RandKategoria].good() == false && !kategoria[RandKategoria].is_open())
    {
        system("cls");
        textColor('R');

        cout << "Plik nie istnieje lub jest otwarty!";

        exit(0);
    }

    string LiniaZpliku;
    int nr_linii = 1;

    while (getline(kategoria[RandKategoria], LiniaZpliku))
    {
        switch (nr_linii)
        {
        case 1: Hasla[0] = LiniaZpliku; break;
        case 2: Hasla[1] = LiniaZpliku; break;
        case 3: Hasla[2] = LiniaZpliku; break;

        }

        nr_linii++;
    }

    kategoria[RandKategoria].close();


    int IloscLiter = Hasla[RandHaslo].length();
    int wybor;
                
     


    //Wypelnianie tablicy z porownaniem

    for (int i = 0; i < IloscLiter; i++)
    {
        TabPorownanieZwpisem[i] = Hasla[RandHaslo][i];
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


    for (int i = 0; i < IloscLiter; i++)
    {
        PokazywanieLiterek[i] = PustePole;
    }



    while (End)
    {
        //Program własciwy

        textColor();
        cout << "********* KOLO FORTUNY **********" << endl;

        cout << "KATEGORIA: " << Kategoria_Nazwa << endl;
        cout << "liczba liter to: " << IloscLiter << endl;
        Sleep(100);

        cout << "*********************************" << endl << endl;


        //Rysowanie pola wypelniania
        if (PorownajTablice(IloscLiter, PokazywanieLiterek, TabPorownanieZwpisem))
        {
            textColor('R');
            cout << "[ Brawo, wygrales! ]" << endl << endl;
            textColor();

            End = false;
        }
        else
        {


            textColor('G');
            cout << "[ ";
            for (int i = 0; i < IloscLiter; i++)
            {
                if (PokazywanieLiterek[i] == PustePole)
                {
                    PokazywanieLiterek[i] = wypelnianiePola(Hasla[RandHaslo], i, Litera);
                }

                cout << PokazywanieLiterek[i] << " ";
            }
            cout << "]" << endl << endl;

            cout << Hasla[RandHaslo] << endl;

        }

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

            if (OdgadnijHaslo(Hasla[RandHaslo], Haslo) == true)
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
