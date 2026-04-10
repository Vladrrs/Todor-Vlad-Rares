#include <iostream>
#include <cstdlib> 
#include <ctime>    

using namespace std;

int main()
{
    srand(time(0)); 

    
    int randomnumber = rand() % 100 + 1; 
    int attempt = 0, attemptuser = 0;

    cout << "Guess the number (between 1 and 100)" << endl;

    do {
        cout << "Enter your guess: ";
        cin >> attemptuser;
        attempt++;

        if (attemptuser < randomnumber) {
            cout << "Too low, try again" << endl;
        } 
        else if (attemptuser > randomnumber) {
            cout << "Too high, try again" << endl;
        }

    } while (attemptuser != randomnumber);

    cout << "Correct! Number of tries: " << attempt << endl;

    return 0;
}