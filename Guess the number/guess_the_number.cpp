#include <iostream>   // pentru input (cin) si output (cout)
#include <cstdlib>    // pentru functia rand()
#include <ctime>      // pentru time(), folosit la random

using namespace std;

int main()
{
    // Initializam generatorul de numere random
    // time(0) face ca numerele sa fie diferite de fiecare data
    srand(time(0)); 

    // Generam un numar aleator intre 1 si 100
    int randomnumber = rand() % 100 + 1; 

    // attempt = numarul de incercari
    // attemptuser = numarul introdus de utilizator
    int attempt = 0, attemptuser = 0;

    // Mesaj pentru utilizator
    cout << "Ghiceste numarul (intre 1 si 100)" << endl;

    // Bucla care se repeta pana ghicesti numarul
    do {
        cout << "Ghiceste: ";
        cin >> attemptuser;   // citim numarul de la tastatura

        attempt++; // crestem numarul de incercari

        // Verificam daca numarul este prea mic
        if (attemptuser < randomnumber) {
            cout << "Prea mic, mai incearca" << endl;
        } 
        // Verificam daca numarul este prea mare
        else if (attemptuser > randomnumber) {
            cout << "Prea mare, mai incearca" << endl;
        }

    } while (attemptuser != randomnumber); // continua pana ghicesti corect

    // Cand ghicesti corect
    cout << "Corect! Numarul de incercari: " << attempt << endl;

    return 0; // programul se termina
}
