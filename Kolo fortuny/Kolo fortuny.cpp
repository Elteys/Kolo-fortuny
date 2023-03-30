#include <iostream>
#include <cstdlib>
#include <Windows.h>

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


    cout << "------- GENEROWANIE HASLA -------" << endl;

    for(int i = 0; i < 10; i++)
    {
        cout << "---------------------------------" << endl;
        Sleep(100);
    }
    system("cls");
    
    cout << "********* KOLO FORTUNY **********" << endl;

    cout << "liczba liter to: " << IloscLiter << endl;
    Sleep(100);

    cout << "*********************************" << endl;
    
    cout << "[ ";  PolaWypelniania(IloscLiter); cout << "]" << endl;

    cout << "---------------------------------" << endl;

    cout << "Podaj pierwsza litere: "; cin >> Litera;




    












    
    
    return 0;
}

