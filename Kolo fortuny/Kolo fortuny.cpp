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

string nazwy_plikow[Y] = { "Kraje", "Pojazdy", "Sprzet", "Zwierzeta", "Rosliny" };

string TAB_samogloski[12] = {"a", "A", "e", "E", "i", "I", "o", "O", "u", "U", "y", "Y"};

int Kolo[] = { -1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000 }; // -1 bankrut // 0 strata kolejki
    

struct Gracz {
    string imie;
    int kasa = 0; //Kasa z wygranej RUNDY
    int portfel = 0; 
};

struct Gracz TAB_gracze[GRACZE];

//Wypełnainie tablic

string wypelnianiePola(string Haslo, int i, string litera)
{
    int check = 0;

    string Wielka_litera, Mala_litera;
    string Tablica_Haslo = Haslo;
    string TabPorownanieZwpisem[25];
    string PustePole = "_";
    string Spacja = " ";
    
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
            if (TabPorownanieZwpisem[i] == "_")
            {
                return Spacja;
            }

            return PustePole;
        }
    
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

//Sprawdzanie litery

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

int jest_samogloska(string Litera)
{
    if (Litera == "a" || Litera == "e" || Litera == "i" || Litera == "o" || Litera == "u" || Litera == "y" ||
        Litera == "A" || Litera == "E" || Litera == "I" || Litera == "O" || Litera == "U" || Litera == "Y")
    {
        return 1;
    }

    return 0;
}

int main()
{
    srand(time(NULL));
    int RandKategoria = rand() % Y;

    int Liczba_Rund = 1;
    int Kolo_Los;
    int RandHaslo;
    int IloscLiter;
    int nr_lini = 0;
    int Kolejnosc_graczy = 2;

    char wybor_kolo;
    char wybor;

    string Hasla[X];
    string Kategoria_Nazwa = nazwy_plikow[RandKategoria];
    string PokazywanieLiterek[25];
    string TabPorownanieZwpisem[25];

    string Haslo;
    string Litera;
    string samogloska;
    string Linia_z_pliku;
    string PustePole = "_";
 
    bool End = true;
    bool Next = true;
    bool Moze_odgadnac_samogloske = false;

    //Losowanie kategorii

    kategoria[RandKategoria].open(nazwy_plikow[RandKategoria]+".txt", ios::in);

    if (kategoria[RandKategoria].good() == false && !kategoria[RandKategoria].is_open())
    {
        system("cls");
        textColor('R');

        cout << "Plik nie istnieje lub jest otwarty!";

        exit(0);
    }

    //Przypisywanie hasel do tablicy

    while (getline(kategoria[RandKategoria], Linia_z_pliku))
    {
  
        Hasla[nr_lini] = Linia_z_pliku; 

        nr_lini++;

    }

    kategoria[RandKategoria].close();

    if (nr_lini == 0) //Sprawdza czy kategoria jest pusta (czyli ma 0 lini)
    {
        system("cls");
        cout << "Kategoria jest pusta!" << endl;

        exit(0);
    }

    //Losowanie hasla

    srand(time(NULL));
    RandHaslo = rand() % nr_lini;

    //Ilosc liter

    IloscLiter = Hasla[RandHaslo].length();
                
    for (int i = 0; i < IloscLiter; i++) //Wypelnianie tablicy z porownaniem
    {
        TabPorownanieZwpisem[i] = Hasla[RandHaslo][i];
    }
    
    //Podaj imiona graczy

    while (true)
    {
        system("cls");

        textColor('G');
        cout << "**************************" << endl;
        cout << "Podaj imiona graczy " << "(" << GRACZE << "): " << endl;

        for (int i = 0; i < GRACZE; i++)
        {
            textColor('G');
            cout << endl;
            cout << "[ " << i + 1 << " ]: "; textColor('B'); getline(cin, TAB_gracze[i].imie);
        }

        system("cls");
        textColor('G');
        cout << "**************************" << endl;
        textColor('B');
        cout << "TOWJE LOBBY: " << endl;
        cout << endl;

        for (int i = 0; i < GRACZE; i++)
        {

            cout << "-  " << TAB_gracze[i].imie << endl;

        }

        cout << endl;
        textColor('R');
        cout << "Kliknij dowolny klawisz by kontynuowac..." << endl << endl;
        cout << "Lub klawisz \"1\" aby edytowac. " << endl << endl;
        cout << "---> ";
        while (true) { // usuwanie znakow z bufora wejsciowego
            while (_kbhit()) {
                _getch();
            }
            wybor = _getch();
            break;
        }

        if (wybor != '1')
        {
            break;
        }

    }

    // Animacja 
    cout << endl << endl ;
    for (int i = 0; i < 6; i++)
    {
        int queue = i % 3;
        switch (queue)
        {
        case 0:
            textColor('B');
            break;
        case 1:
            textColor('Y');
            break;
        case 2:
            textColor('G');
            break;
        }

        cout << "OK! ";
        Sleep(150);
    }

    system("cls");

    // Animacja generowania hasła

    textColor('G');
    cout << "------- GENEROWANIE HASLA -------" << endl;

    for (int i = 0; i < 12; i++) 
    {
        int queue = i % 4;
        switch (queue)
        {
        case 0:
            textColor('R');
            break;
        case 1:
            textColor('G');
            break;
        case 2:
            textColor('B');
            break;
        case 3:
            textColor('Y');
            break;
        }
        

        cout << "---------------------------------" << endl;
        Sleep(100);
    }
    system("cls");


    for (int i = 0; i < IloscLiter; i++)
    {
        PokazywanieLiterek[i] = PustePole;
    }

    while (End && PorownajTablice(IloscLiter, PokazywanieLiterek, TabPorownanieZwpisem)) //Program własciwy
    {
        if (Next)
        {
            Kolejnosc_graczy = (Kolejnosc_graczy + 1) % GRACZE;
        }
        
        srand(time(NULL));
        Kolo_Los = rand() % 15;

        textColor();
        cout << "*********"; textColor('R'); cout << " KOLO FORTUNY "; textColor(); cout << "**********" << endl;
        cout << "***********"; textColor('R'); cout << " RUNDA: " << Liczba_Rund; textColor(); cout << " ************" << endl << endl;
        cout << "KATEGORIA: " << Kategoria_Nazwa << endl << endl;
        cout << "LICZBA LITER: " << IloscLiter << endl << endl;
        textColor('B');
        for (int i = 0; i < GRACZE; i++)
        {
            if (i == Kolejnosc_graczy)
            {
                textColor('P'); cout << TAB_gracze[i].imie << " ( " << TAB_gracze[i].kasa << " )" << endl;
            }
            else
            {
                textColor('B'); cout << TAB_gracze[i].imie << " ( " << TAB_gracze[i].kasa << " )" << endl;
            }
        }
        textColor();
        cout << endl;
        cout << "*********************************" << endl << endl;
        cout << "     ";


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
        cout << "1. Krec kolem" << endl;
        cout << "2. Odgadnij haslo" << endl;
        cout << "3. Kup samogloske" << endl;
        textColor('R');
        cout << "Co chcesz zrobic? --> "; cin >> wybor;
        

        switch (wybor)
        {
        case '1':
            if (Kolo_Los == 0)
            {
                TAB_gracze[Kolejnosc_graczy].kasa = 0;

                cout << endl;
                textColor('Y');
                cout << "############" << endl;
                cout << "# Bankrut! #" << endl;
                cout << "############" << endl;
                textColor();

                Sleep(1000);

                system("cls");

                Liczba_Rund++;
                Next = true;
                Moze_odgadnac_samogloske = false;

                break;
            }
            if (Kolo_Los == 1)
            {
                cout << endl;
                textColor('Y');
                cout << "##################" << endl;
                cout << "# Strata kolejki!#" << endl;
                cout << "##################" << endl;
                textColor();

                Sleep(1000);

                system("cls");

                Liczba_Rund++;
                Next = true;
                Moze_odgadnac_samogloske = false;

                break;
            }

            cin.ignore();
            cout << endl;
            textColor('B');
            cout << "[ " << Kolo[Kolo_Los] << " ]" << endl << endl;
            textColor();
            cout << "Podaj litere: "; textColor('Y'); cin >> Litera;
            cout << endl;

            if (Czy_Dobra_Litera(Litera, TabPorownanieZwpisem, IloscLiter) == true)
            {
                TAB_gracze[Kolejnosc_graczy].kasa = TAB_gracze[Kolejnosc_graczy].kasa + Kolo[Kolo_Los];

                if (jest_samogloska(Litera) != 1)
                {
                    Moze_odgadnac_samogloske = true;
                }

                textColor('Y');
                cout << "###########################" << endl;
                cout << "# Brawo, odgadles litere! #" << endl;
                cout << "###########################" << endl;
                textColor();

                Sleep(1000);

                system("cls");

                Next = false;

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

                Next = true;
                Moze_odgadnac_samogloske = false;
            }

            Liczba_Rund++;

            break;
        case '2':
            cin.ignore();
            cout << endl;
            textColor();
            cout << "Podaj haslo: "; textColor('Y'); getline(cin, Haslo); // wczytaj całą linię tekstu, w tym spacje
            textColor();
            cout << endl;
            
            // zamień spacje na podkreślenia
            for (int i = 0; i < Haslo.length(); i++) {
                if (Haslo[i] == ' ') {
                    Haslo[i] = '_';
                }
            }

            if (Hasla[RandHaslo] == Haslo)
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

            Liczba_Rund++;
            Next = true;
            Moze_odgadnac_samogloske = false;

            break;
        case '3':
            if (Moze_odgadnac_samogloske == true)
            {
                if (TAB_gracze[Kolejnosc_graczy].kasa >= 500)
                {
                    TAB_gracze[Kolejnosc_graczy].kasa = TAB_gracze[Kolejnosc_graczy].kasa - 500;

                    while (true)
                    {
                        cout << endl;
                        textColor('B');
                        cout << "[ -500 ]" << endl << endl;
                        textColor();
                        cout << "Odkryj samogloske: "; textColor('Y'); cin >> samogloska;
                        cout << endl;

                        if (jest_samogloska(samogloska) == 1)
                        {
         
                            for (int i = 0; i < IloscLiter; i++)
                            {
                                if (PokazywanieLiterek[i] == PustePole)
                                {
                                    srand(time(NULL));
                                    PokazywanieLiterek[i] = wypelnianiePola(Hasla[RandHaslo], i, samogloska);
                                }

                                if (PokazywanieLiterek[i] == samogloska)
                                {
                                    textColor('R');
                                    cout << PokazywanieLiterek[i] << " ";
                                    textColor();
                                }
                                else
                                {
                                    textColor('Y');
                                    cout << PokazywanieLiterek[i] << " ";
                                    textColor();
                                }
                            }
                            
                            break;
                        }

                        textColor('R');
                        cout << "PODAJ SAMOGLOSKE!";
                        textColor();
                    }
                }
                else
                {
                    cout << "Nie masz kasy aby kupic samogloske!";
                    Next = false;
                }
            }
            else
            {
                cout << "Musisz odgadnac spolgloske!";
                Next = false;
            }
         

            Sleep(1200);
            system("cls");

            break;
        default:
            system("cls");
 
            textColor('R');
            cout << "#################################" << endl;
            cout << "#  Podaj liczbe z zakresu 1-2!  #" << endl;
            cout << "#################################" << endl << endl;
            textColor();
            
            Sleep(1000);

            break;
        }
    }

    // Koniec programu

    system("cls");
    textColor('R');
    cout << "[ Gracz " << TAB_gracze[Kolejnosc_graczy].imie << " wygrywa gre! ]" << endl << endl;
    textColor();

    return 0;
}
