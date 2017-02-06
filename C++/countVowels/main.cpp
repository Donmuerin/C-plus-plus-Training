#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    char c;
    int acount, ecount, icount, ocount, ucount;
    acount = ecount = icount = ocount = ucount = 0;
    ifstream inFile("count.txt", ios::in);
    inFile.get(c);
    while (!inFile.eof()) {
        cout << c;
        if (c == 'a' || c == 'A')
            ++acount;
        else if (c == 'e' || c == 'E')
            ++ecount;
        else if (c == 'i' || c == 'I')
            ++icount;
        else if (c == 'o' || c == 'O')
            ++ocount;
        else if (c == 'u' || c == 'U')
            ++ucount;
        inFile.get(c);
    }
    cout << endl << endl;
    cout << "There are " << acount
        << " as in the file. " << endl;
    cout << "There are " << ecount
        << " es in the file. " << endl;
    cout << "There are " << icount
        << " is in the file. " << endl;
    cout << "There are " << ocount
        << " os in the file. " << endl;
    cout << "There are " << ucount
        << " us in the file. " << endl;
    inFile.close();
    return 0;
}
