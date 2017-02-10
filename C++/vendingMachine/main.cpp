
#include <iostream>

using namespace std;

int menu(){
    int choice;
     cout << "Main Menu" << "\n"
    << "0. Exit" << "\n"
    << "1. Insert money" << "\n"
    << "2. Purchase item"
        << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    while(!cin){
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Invalid input! Numeric input is required: ";
            cin >> choice;
        }
    return choice;
}

int insertMoney(){
    double money;
    cout << "Accepted $1, $5, $10 only. Please enter your amount: ";
    cin >> money;
    while(!cin || money != 0.0 && money != 1.0 && money != 5.0 && money != 10.0){
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Money is not accepted! Please enter again: ";
            cin >> money;
        }
    return money;
}

void printOptions() {

     cout <<"\n**********************\n";
     cout <<"LAY'S Vending Machine \n";
     cout <<"**********************\n";
     cout << "Chose your flavors! \n";
     cout << "1 - Barbecue Flavored Potato Chips....................$2.5\n";
     cout << "2 - Cheddar & Sour Cream Flavored Potato Chips........$3.0\n";
     cout << "3 - Chile Limon Flavored Potato Chips.................$3.5\n";
     cout << "4 - Classic Potato Chips..............................$2.0\n";
     cout << "5 - Deli Style Original Potato Chips..................$2.5\n";
     cout << "What is your flavors? (1/5): ";
}


void purchase(){
     enum Snacks{barbecue, cheddar, limon, classic, deli};
     int i;
     double money;
     printOptions();
     cin >> i;
     while(!cin || i < 0 || i > 5){
            cin.clear();
            cin.ignore(256,'\n');
            cout << "Please choose your option from range 1 - 5. ";
            cin >> i;
        }
     cout << "\n";
     switch(i-1)
       {
        case barbecue:
            if (money < 2.5){
                cout << "Not enough money! ";
                break;
            }
            money -= 2.5;
            cout << "Barbecue Flavored Potato Chips is selected. \nPlease take your change: $" << money;
            break;


        case cheddar:
            if (money < 3.0){
                cout << "Not enough money! ";
                break;
            }
            money -= 3.0;
            cout << "Cheddar & Sour Cream Flavored Potato Chips is selected. \nPlease take your change: $" << money;
            break;


        case limon:
            if (money < 3.5){
                cout << "Not enough money! ";
                break;
            }
            money -= 3.5;
            cout << "Chile Limon Flavored Potato Chips is selected. \nPlease take your change: $" << money;
            break;

        case classic:
            if (money < 2.0){
                cout << "Not enough money! ";
                break;
            }
            money -= 2.0;
            cout << "Classic Potato Chips is selected. \nPlease take your change: $" << money;
            break;

         case deli:
            if (money < 2.5){
                cout << "Not enough money! ";
                break;
            }
            money -= 2.5;
            cout << "Deli Style Original Potato Chips is selected. \nPlease take your change: $" << money;
            break;
       }


}

int main()
{
    int choice;
    while(choice != 0) {
        cout << "\n";
        choice = menu();
        switch(choice) {
            case 1:
                insertMoney();
            case 2:
                purchase();
                break;
            case 0:
                break;
            default:
                cout << "Invalid input."<< endl;
        }
    }return 0;
}
