#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

string fileName = "todo.txt"; //read file

int menu() {
    cout << "To-do List " << endl << endl;
    string line;
    int number = 1;
    ifstream inFile(fileName.c_str(), ios::in);
    if(!inFile) {
        cout << "File not found." << endl;
        exit(1);
    }
    getline(inFile, line);
    while (!inFile.eof()) { //number of items
        cout << number << ". " << line
             << endl;
        ++number;
        getline(inFile, line);
    }
    inFile.close();
    cout << endl << endl;
    int choice;
    cout << "Main Menu" << "\n"
    << "0. Exit" << "\n"
    << "1. To add item" << "\n"
    << "2. To delete item"
        << endl; //display to-do list
    cout << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void addItem() {
    cin.clear(); //clear error flag on cin
    cin.sync(); //read in the rest of the output
    ofstream outFile(fileName.c_str(), ios::app);
    string item;
    cout << "Please enter an item: ";
    getline(cin, item);
    if (!outFile) {
        cout << "File not found." << endl;
        exit(1);
    }
    outFile << item << endl; //read in
    outFile.close();
    cout << endl;
}

void deleteItem() {
    int option;
    cin.clear();
    cin.sync();
    cout << "Which item do you want to delete? ";
    cin >> option; //number

    vector<string> items;
    int number = 1;

    ifstream inFile(fileName.c_str(), ios::in);//for input
    if(!inFile) {
        cout << "File not found. " << endl;
        exit(1);
    }
    string item;
    getline(inFile, item);
    while (!inFile.eof()) {
        if (number != option)
            items.push_back(item);//ignore and store item to items
        ++number;
        getline(inFile, item);
    }
    inFile.close();

    ofstream outFile(fileName.c_str(), ios::out);//for output
    if(!outFile) {
        cout << "File not found. " << endl;
        exit(1);
    }
    //rewrite item to to-do list
    for(int i = 0; i < items.size(); ++i)
        outFile << items[i] << endl;
    outFile.close();
}

int main()
{
    int choice;
    while(choice != 0) {
        choice = menu();
        switch(choice) {
            case 1:
                addItem();
                break;
            case 2:
                deleteItem();
                break;
            case 0:
                break;
            default:
                cout << "Invalid input."<< endl;
        }
    }return 0;
}
