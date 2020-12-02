#include <iostream>
#include <vector>
#include <string>
#include <fstream>

bool isPasswordValid_Puzzle1(std::string inputString)
{   
    int occurences = 0;
    int atLeast = 0;
    int atMost = 0;
    char relevantChar = '0';
    std::string password = "";
    std::string tempString = "";
    std::string rangeString = "";
    std::size_t tempIndex = 0;

    //First, get the first segment of line with atLeast-atMost:
    tempIndex = inputString.find(" ");
    rangeString = inputString.substr(0, tempIndex); // get first and second numbers (atLeast and atMost)
    inputString = inputString.substr(tempIndex+1);
    //std::cout << "Tempstring for atLeast and atMost: " << rangeString << std::endl;
    
    //Then, get the second segment of line with the relevant Char:
    tempIndex = inputString.find(" ");
    tempString = inputString.substr(0, tempIndex); // get charactere (relevantChar)
    relevantChar = tempString[0];
    
    //std::cout << "Tempstring for relevantChar: " << tempString << std::endl;
    //Then, get the password substring
    password = inputString.substr(tempIndex+1); // get password 
    std::cout << "Tempstring for password: " << password << std::endl;

    //Now, convert the rangeString to two integers and save it to atLeast and atMost
    tempString = rangeString.substr(0, rangeString.find("-")); // get atLeast inside rangeString
    //std::cout << "Tempstring for atLeast: " << tempString << std::endl;
    atLeast = std::stoi (tempString);
    tempIndex = rangeString.find("-")+1;

    tempString = rangeString.substr(tempIndex); // get atLeast
    //std::cout << "Tempstring for atLeast: " << tempString << std::endl;
    atMost = std::stoi (tempString);

    
    //Now, get the amount of relevant char in the password string
    tempIndex = password.find(relevantChar);
    while (tempIndex != std::string::npos) // When it is not found anymore
    {
        occurences++;
        tempIndex = password.find(relevantChar,tempIndex+1);
        
    }
    //std::cout << occurences << " occurences of " << relevantChar << " found on  '" << password << "'. Range: " << rangeString ; 
    if(occurences >= atLeast && occurences <= atMost )
    {   
       // std::cout << ", password is VALID." << std::endl ; 
        return true;
    }
    else
    {   
     //   std::cout << " , password is INVALID." << std::endl ; 
        return false;  
    }

}


bool isPasswordValid_Puzzle2(std::string inputString)
{   
    int occurences = 0;
    int position1 = 0;
    int position2 = 0;
    char relevantChar = '0';
    std::string password = "";
    std::string tempString = "";
    std::string rangeString = "";
    std::size_t tempIndex = 0;

    //First, get the first segment of line with position1-position2:
    tempIndex = inputString.find(" ");
    rangeString = inputString.substr(0, tempIndex); // get first and second numbers (position1 and position2)
    inputString = inputString.substr(tempIndex+1);
    //std::cout << "Tempstring for position1 and position2: " << rangeString << std::endl;
    
    //Then, get the second segment of line with the relevant Char:
    tempIndex = inputString.find(" ");
    tempString = inputString.substr(0, tempIndex); // get charactere (relevantChar)
    relevantChar = tempString[0];
    
    //std::cout << "Tempstring for relevantChar: " << tempString << std::endl;
    //Then, get the password substring
    password = inputString.substr(tempIndex+1); // get password 
    std::cout << "Tempstring for password: " << password << std::endl;

    //Now, convert the rangeString to two integers and save it to position1 and position2
    tempString = rangeString.substr(0, rangeString.find("-")); // get position1 inside rangeString
    //std::cout << "Tempstring for position1: " << tempString << std::endl;
    position1 = std::stoi (tempString);
    tempIndex = rangeString.find("-")+1;

    tempString = rangeString.substr(tempIndex); // get position1
    //std::cout << "Tempstring for position1: " << tempString << std::endl;
    position2 = std::stoi (tempString);

    //decrease positions so that it corresponds to cpp indexes
    position1--;
    position2--;
    if(password[position1] == relevantChar) occurences++; 
    if(password[position2] == relevantChar) occurences++;
    if(occurences == 1) return true;
    else return false;


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
        if(isPasswordValid_Puzzle2(tempString))
        {
            numberOfValidPasswords++;
        }
        }
        entries.close();
    }
    std::cout << "Number of valid Passwords: " << numberOfValidPasswords << std::endl;

    return 0;
}