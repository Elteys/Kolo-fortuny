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

//Ilosc graczy
const int GRACZE = 3;

fstream kategoria[Y];

string nazwy_plikow[Y] = { "Kraje", "Pojazdy", "Sprzet", "Zwierzeta", "Rosliny"};

int Kolo[] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 };

struct Gracz {
    string imie;
    int kasa = 0;
    int portfel = 0; //Kasa z wygranej RUNDY
};

struct Gracz TAB_gracze[GRACZE];

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
            return true;
        }
    }
    return false;
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
    int Kolo_Los;
    int wybor;
    int RandHaslo;
    int IloscLiter;

    string Hasla[X];
    string Kategoria_Nazwa = nazwy_plikow[RandKategoria];
    string PokazywanieLiterek[25];
    string TabPorownanieZwpisem[25];

    string Haslo;
    string Litera;
    string PustePole = "_";
 
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
    int nr_lini = 0;

    while (getline(kategoria[RandKategoria], Linia_z_pliku))
    {
  
        Hasla[nr_lini] = Linia_z_pliku; 

        nr_lini++;

    }

    kategoria[RandKategoria].close();

    //Sprawdza czy kategoria jest pusta czyli ma 0 lini
    if (nr_lini == 0)
    {
        system("cls");
        cout << "Kategoria jest pusta!" << endl;

        exit(0);
    }

    srand(time(NULL));
    RandHaslo = rand() % nr_lini;

    //Ilosc liter
    IloscLiter = Hasla[RandHaslo].length();
                
     
    //Wypelnianie tablicy z porownaniem

    for (int i = 0; i < IloscLiter; i++)
    {
        TabPorownanieZwpisem[i] = Hasla[RandHaslo][i];
    }
    
    //Podaj imiona graczy
    textColor('G');
    cout << "**************************" << endl;
    cout << "Podaj imiona graczy " << "(" << GRACZE << "): " << endl;
    
    for (int i = 0; i < GRACZE; i++)
    {
        textColor('G');
        cout << endl;
        cout << "[ " << i + 1 << " ]: "; textColor('B'); getline(cin, TAB_gracze[i].imie);
        
    }

    textColor('G');
    cout << endl;
    cout << "**************************" << endl;
    cout << "Gracze to: " << endl;
    cout << endl;

    textColor('B');
    for (int i = 0; i < GRACZE; i++)
    {
        
        cout << "-  " << TAB_gracze[i].imie << endl;

    }

    cout << endl;
    textColor('R');
    cout << "* Kliknij ENTER aby kontynuwoac *";
    cin.ignore();

    cout << endl;
    textColor('R');
    cout << "OK! OK! OK!" << endl;
    Sleep(800);
    system("cls");

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



    while (End && PorownajTablice(IloscLiter, PokazywanieLiterek, TabPorownanieZwpisem))
    {
        //Program własciwy

        Kolo_Los = Kolo[rand() % 15];

        textColor();
        cout << "********* KOLO FORTUNY **********" << endl;
        cout << "*********** RUNDA: " << Liczba_Rund << " ************" << endl << endl;

        cout << "KATEGORIA: " << Kategoria_Nazwa << endl << endl;
        cout << "liczba liter to: " << IloscLiter << endl << endl;
        Sleep(100);

        cout << "*********************************" << endl << endl;
        cout <<  "     ";


        //Rysowanie pola wypelniania

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

        

        textColor();
        cout << "*********************************" << endl << endl;

        //////////////////////////////

        cout << "1. Krec kolem" << endl;
        cout << "2. Odgadnij haslo" << endl;
        textColor('R');
        cout << "co chcesz zrobic: "; cin >> wybor;


        switch (wybor)
        {
        case 1:
            textColor('B');
            cout << Kolo_Los << endl;
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

                Sleep(1000);

                system("cls");

            }
            else
            {
                textColor('Y');
                cout << "##########" << endl;
                cout << "# Pudlo! #" << endl;
                cout << "##########" << endl;
                textColor();

                Sleep(1000);

                system("cls");
            }

            break;
        case 2:

            textColor();
            cout << "Podaj haslo: "; cin >> Haslo;
            cout << endl;

            if (OdgadnijHaslo(Hasla[RandHaslo], Haslo) == true)
            {

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

        Liczba_Rund++;

    }

    textColor('R');
    cout << "[ Brawo, wygrales! ]" << endl << endl;
    textColor();


    return 0;
}
