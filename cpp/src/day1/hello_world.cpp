#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> msg {"Hello", "Lago'sTeam", "!", " ** ", "ADVENT", "of", "Code", "2020"};

    for (const string& word : msg)
    {
        cout << word << " ";
    }
    cout << endl;
}