#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
	int months= 0;
	double sInterest, mInterest, sBalance, sdeposits, swithdrawal, fInterest, fBalance;
	sInterest = mInterest = sBalance = sdeposits = swithdrawal = fInterest = fBalance = 0;

	cout<<"What is the annual interest rate?: ";
	cin >> sInterest;
	while (!cin || sInterest < 0){
        cout << "Invalid input! What is the annual interest rate?: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> sInterest;
    }

	cout<<"What is the starting balance?: ";
	cin >> sBalance;
	while (!cin || sBalance < 0){
        cout << "Invalid input! What is the starting balance?: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> sBalance;
    }

	cout <<"How many months passed?: ";
    cin >> months;
    while (!cin || months < 0 || months > 12){
        cout << "Invalid input! How many months passed?: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> months;
    }

	fBalance = sBalance;
	mInterest = sInterest/12;

    cout<< "Total deposits?: $";
    double deposits;
    cin >> deposits;
    while (!cin || deposits < 0){
        cout << "Invalid input!";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> deposits;
    }
    fBalance += deposits;

    cout<<"Total withdrawal?: $";
    double withdrawal;
    cin >> withdrawal;
    while (!cin || withdrawal < 0 || withdrawal > fBalance){
        cout << "Invalid input!";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> withdrawal;
    }
    fBalance -= withdrawal;

    fInterest += (fBalance * mInterest);

	cout << "Amount of interest earned:" << " $ " << fInterest * months <<endl;
	cout << "Ending balance:" << " $ " << fInterest * months + fBalance << endl;

	return 0;
}
