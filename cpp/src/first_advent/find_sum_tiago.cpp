#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
using namespace std;

int main()
{
    string line;
    ifstream data_file;
    data_file.open("/home/tknagy/Repositories/ADVENT_code_2020/cpp/data/first_advent");

    vector<int> data_vector;
    
    if (data_file.is_open())
    {
        while(getline(data_file,line))
        {            
            data_vector.push_back(stoi(line));
        }
        data_file.close();
    }
    else cout << "Unable to open file";

    sort(data_vector.begin(), data_vector.end());

    for (auto bigger_value_it = data_vector.end(); bigger_value_it != data_vector.begin(); --bigger_value_it)
    {
        for (const auto &smaller_value : data_vector)
        {        
            const int sum = smaller_value + *bigger_value_it;
            if(sum > 2020) break;
            if(sum == 2020)
            {
                std::cout<< "The solution is: " << smaller_value * *bigger_value_it << endl;
            }
        }
        
    }
    
}