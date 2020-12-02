#include <iostream>
#include <vector>
#include <string>
#include <fstream>

bool isPasswordValid(std::string inputString)
{   
    int occurences = 0;
    int atLeast = 0;
    int atMost = 0;
    char relevantChar = '0';
    std::string password = "";
    std::string tempString = "";
    tempString = inputString.substr(0, inputString.find("-")); // get first number (atLeast)
    std::cout << "Tempstring for atLeast: " << tempString << std::endl;
    atLeast = std::stoi (tempString);
    tempString = inputString.substr(1, inputString.find("-")); // get second number (atMost)
     std::cout << "Tempstring for atMost: " << tempString << std::endl;
    atMost = std::stoi (tempString);
    tempString = inputString.substr(1, inputString.find(" ")); // get charactere (relevantChar)
    relevantChar = tempString[0];
    password = inputString.substr(2, inputString.find(" ")); // get password 

    std::size_t positionRelevantChar = password.find_first_of(relevantChar);
    while (positionRelevantChar != std::string::npos)
    {
        occurences++;
        positionRelevantChar = password.find_first_of(positionRelevantChar+1);
        std::cout << occurences << " occurences of " << relevantChar << "found on  '" << password << "'" << std::endl; 
    }

    if(occurences >= atLeast && occurences <= atMost )
    {
        return true;
    }
    else
    {
        return false;  
    }

}


int main()
{
    std::ifstream entries;
    std::vector<std::string> entries_vec;
    std::string tempString;
    int numberOfValidPasswords = 0;

    entries.open("./day2_input.txt");
    if (entries.is_open())
    {
        while ( std::getline(entries, tempString) )
        {
        //std::cout << tempString << '\n';
        if(isPasswordValid(tempString))
        {
            numberOfValidPasswords++;
        }
        }
        entries.close();
    }
    std::cout << "Number of valid Passwords: " << numberOfValidPasswords << std::endl;

    return 0;
}