#include <iomanip>
#include <iostream>

using namespace std;

void buildArray(int arr[], string arr1[], int size) {
    int marks;
    string subject;
    for(int i = 0; i < size; ++i){
        cout << "Enter subject's name(eg. Data_Structure, Programming_2): ";
        cin >> subject;
        arr1[i] = subject;

        cout << "Enter marks: ";
        cin >> marks;
        arr[i] = marks;
    }
}

void displayArray(int arr[],string arr1[], int size) {

    for(int i = 0; i < size; ++i){
        string grades;
        if (arr[i] >= 80 && arr[i] < 100)
            grades = "HD";
        else if (arr[i] >= 70 && arr[i] < 80)
            grades = "D";
        else if (arr[i] >= 60 && arr[i] < 70)
            grades = "C";
        else if (arr[i] >= 50 && arr[i] < 60)
            grades = "P";
        else if (arr[i] >= 0 && arr[i] < 50)
            grades = "F";
        else
            cout << "Does not recognize input.";
        cout << arr1[i] << ": " << arr[i] <<"\t" << grades <<"\n";
    }
}

double averageNum(int arr[], int size){
    double sum = 0;
    for (int i = 0; i < size; ++ i)
        sum += arr[i];
    double average = sum / size;
    return average;

}

int maxGrade(int arr[], int size) {
    int maxValue = arr[0];
    int position = 0;
    for(int i = 1; i < size; ++i)
        if (arr[i] > maxValue) {
            maxValue = arr[i];
            position = i;
        }
    return position;
}

int minGrade(int arr[], int size) {
    int minValue = arr[0];
    int position = 0;
    for(int i = 1; i < size; ++i)
        if (arr[i] < minValue) {
            minValue = arr[i];
            position = i;
        }
    return position;
}

int main()
{
    int subjectNumber;
    string studentName;
    cout << "What is the student name? ";
    getline(cin, studentName);
    cout << "How many subjects did the student enroll? ";
    cin >> subjectNumber;
    int size = subjectNumber;
    int grades[size];
    string subjects[size];
    buildArray(grades, subjects, size);
    cout << "\n\n";
    cout << "Name: " << studentName << endl;
    cout << "Number of subjects enrolled: " << subjectNumber << endl;
    displayArray(grades, subjects, size);
    cout << endl;

    int maxPosition = maxGrade(grades, size);
    cout << "The largest grade is " << grades[maxPosition] << endl;
    int minPosition = minGrade(grades, size);
    cout << "The minimum grade is " << grades[minPosition] << endl;
    double average = averageNum(grades, size);
    cout << "Average: " << setprecision(4) << average;

    return 0;

}
