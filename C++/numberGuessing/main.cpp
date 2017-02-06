#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(NULL));
    int number, guess, tries;
    tries = 1;
    number = rand() % 10 + 1;
    char cont;
    cout << "Welcome!" ;
    do {
        cout << endl << endl;
        cout << "Guess a number(1-10): ";
        cin >> guess;
        while(!cin){
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Invalid input! Please enter again: ";
            cin >> guess;
        }
        while (guess < 1 || guess > 10){
        cout << "Invalid input! ";
        cin.clear();
        cin.ignore(256,'\n');
        cout << "Enter only range 1-10: ";
        cin >> guess;
        }
        tries ++;
        if (guess == number) {
            cout << "That's right!" << endl;
            break;
        }
        else if (tries < 4 ){
            cout << "Wrong! Please try again " << endl ;
        }
        else {
            cout << "Sorry. Do you want to guess again? To quit press 'n': ";
            tries = 1; //re-initiate
            cin >> cont;
            }
    }
    while (cont != 'n');
    return 0;
}

