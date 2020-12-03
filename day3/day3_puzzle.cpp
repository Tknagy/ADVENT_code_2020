#include <iostream>
#include <vector>
#include <string>
#include <fstream>

bool encounterChecker(std::string line, int position)
{
    if(line.at(position)=='#') return 1;
    else return 0;

}

int puzzle(std::string fileName, int slopeX = 1, int slopeY = 1)
{
    std::ifstream entries;
    std::vector<std::string> entries_vec;
    std::string tempString;
    int positionX = 0;
    int positionY = 0;
    int encounterCounter = 0;
    int deltaX = slopeX;
    int deltaY = slopeY;

    entries.open(fileName);
    if (entries.is_open())
    {   
        while ( std::getline(entries, tempString) )
        {
        
        if(positionY%slopeY == 0) // if the line counter matches the slope on Y, verify for tree
        {     
            if(encounterChecker(tempString, positionX))
            {
                encounterCounter++;
            }
            positionX = (positionX+deltaX)%tempString.size(); // increments X in 3 for the next line. % guarantees that x remain inside input columns
           
        }
         positionY++; //increment one in the line counter
        }
        entries.close();
    }
    return encounterCounter;
}



int main(int argc, char *argv[])
{   
    std::string inputFileName = argv[1];
   
    int puzzle_3_1 = puzzle(inputFileName,3,1);
    std::cout << "---Advent of code, day 3---" << std::endl;
    std::cout << "Puzzle 1: Number of trees encountered: " << puzzle_3_1 << std::endl;

    int puzzle_1_1 = puzzle(inputFileName,1,1);
    int puzzle_5_1 = puzzle(inputFileName,5,1);
    int puzzle_7_1 = puzzle(inputFileName,7,1);
    int puzzle_1_2 = puzzle(inputFileName,1,2);
    long productOfPuzzles = long(puzzle_1_1) * long(puzzle_3_1) * long(puzzle_5_1) * long(puzzle_7_1) * long(puzzle_1_2);
    
    std::cout << "Puzzle 2: Number of trees encountered: " << std::endl;
    std::cout << "[1,1] ->" << puzzle_1_1 << std::endl; 
    std::cout << "[3,1] ->" << puzzle_3_1 << std::endl; 
    std::cout << "[5,1] ->" << puzzle_5_1 << std::endl; 
    std::cout << "[7,1] ->" << puzzle_7_1 << std::endl; 
    std::cout << "[1,2] ->" << puzzle_1_2 << std::endl; 
    std::cout << "Product: " << productOfPuzzles << std::endl;
    

    return 0;
}