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

//Wielkosc tablicy hasel
const int X = 50;

//Liczba kategori
const int Y = 5;

fstream kategoria[Y];

string nazwy_plikow[Y] = { "Kraje", "Pojazdy", "Rosliny", "Sprzet", "Zwierzeta" };

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

bool Czy_Dobra_Litera(string litera, string Haslo[], int Ilosc_Liter)
{
    string Wielka_litera, Mala_litera;

    Mala_litera = towlower(int(litera[0]));
    Wielka_litera = toupper(int(litera[0]));

    for (int i = 0; i < Ilosc_Liter; i++)
    {
        if (Mala_litera == Haslo[i] || Wielka_litera == Haslo[i])
        {
            return true;
        }
    }

    return false;

}

int main()
{
    srand(time(NULL));
    int RandKategoria = rand() % Y;

    int Liczba_Rund = 1;

    string Hasla[X];
    string Kategoria_Nazwa = nazwy_plikow[RandKategoria];

    string Haslo, Litera;
    string PustePole = "_";
    string PokazywanieLiterek[25];
    string TabPorownanieZwpisem[25];

    bool End = true;

    //Losowanie kategorii i hasła
    kategoria[RandKategoria].open(nazwy_plikow[RandKategoria]+".txt", ios::in);

    if (kategoria[RandKategoria].good() == false && !kategoria[RandKategoria].is_open())
    {
        system("cls");
        textColor('R');

        cout << "Plik nie istnieje lub jest otwarty!";

        exit(0);
    }

    string Linia_z_pliku;
    int nr_lini = 1;

    while (getline(kategoria[RandKategoria], Linia_z_pliku))
    {
  
        Hasla[nr_lini - 1] = Linia_z_pliku; 

        nr_lini++;

    }

    kategoria[RandKategoria].close();

    srand(time(NULL));
    int RandHaslo = rand() % nr_lini;


    int IloscLiter = Hasla[RandHaslo].length();

    if (IloscLiter == 0)
    {
        system("cls");
        cout << "Kategoria jest pusta!" << endl;

        exit(0);
    }
     
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
        cout << "*********** RUNDA: " << Liczba_Rund << " ************" << endl << endl;

        cout << "KATEGORIA: " << Kategoria_Nazwa << endl << endl;
        cout << "liczba liter to: " << IloscLiter << endl << endl;
        Sleep(100);

        cout << "*********************************" << endl << endl;
        cout <<  "     ";


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

            
            //Testowe pokazywanie hasla
       
            ///////////////////////////////////
            cout << Hasla[RandHaslo] << endl;
            ///////////////////////////////////

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
            cout << endl;

            if (Czy_Dobra_Litera(Litera, TabPorownanieZwpisem, IloscLiter) == true)
            {
                textColor('Y');
                cout << "###########################" << endl;
                cout << "# Brawo, odgadles litere! #" << endl;
                cout << "###########################" << endl;
                textColor();

                Sleep(1200);

                system("cls");

            }
            else
            {
                textColor('Y');
                cout << "##########" << endl;
                cout << "# Pudlo! #" << endl;
                cout << "##########" << endl;
                textColor();

                Sleep(1200);

                system("cls");
            }

            Liczba_Rund++;

            break;
        case 2:

            textColor();
            cout << "Podaj haslo: "; cin >> Haslo;
            cout << endl;

            if (OdgadnijHaslo(Hasla[RandHaslo], Haslo) == true)
            {

                textColor('Y');
                cout << "##########" << endl;
                cout << "# Brawo! #" << endl;
                cout << "##########" << endl;
                textColor();

                Sleep(300);
                End = false;
            }
            else
            {
                textColor('Y');
                cout << "########" << endl;
                cout << "# Zle! #" << endl;
                cout << "########" << endl;
                textColor();
                Sleep(300);
            }

            Sleep(800);

            system("cls");
            break;

        default:
            system("cls");

            textColor('R');
            cout << "###############################" << endl;
            cout << "# Podaj liczbe z zakresu 1-2! #" << endl;
            cout << "###############################" << endl;
            textColor();

            exit(0);

            break;

        }

           

    }

    return 0;
}
