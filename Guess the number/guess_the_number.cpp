#include <iostream>
#include <cstdlib> 
#include <ctime>    

using namespace std;

int main()
{
    srand(time(0)); 

    
    int randomnumber = rand() % 100 + 1; 
    int attempt = 0, attemptuser = 0;

    cout << "Ghiceste numarul (între 1 și 100)" << endl;

    do {
        cout << "Ghiceste: ";
        cin >> attemptuser;
        attempt++;

        if (attemptuser < randomnumber) {
            cout << "Prea mic, mai incearca" << endl;
        } 
        else if (attemptuser > randomnumber) {
            cout << "Prea mare, mai incearca" << endl;
        }

    } while (attemptuser != randomnumber);

    cout << "Correct! Numarul de incercari: " << attempt << endl;

    return 0;
}
