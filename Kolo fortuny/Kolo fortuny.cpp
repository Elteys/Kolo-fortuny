#include <iostream>
#include <cstdlib>
#include <Windows.h>

using namespace std;

string slowa[10] = { "pies","kot","klawiatura","tranzystor","kondensator","myszka","komputer","lampka","monitor","glowa"};

int main()
{
    srand(time(NULL));

    int x = rand() % 10;

    int IloscLiter = slowa[x].length();


    cout << "------- GENEROWANIE HASLA -------" << endl;

    for(int i = 0; i < 10; i++)
    {
        cout << "---------------------------------" << endl;
        Sleep(100);
    }
    system("cls");

    cout << "------- KOLO FORTUNY -------" << endl;

    cout << "liczba liter to: " << IloscLiter << endl;

    
    
    return 0;
}
