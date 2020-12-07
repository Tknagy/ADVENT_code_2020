#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<algorithm>
#include<numeric>

bool returnBiggest (int i,int j) { return (i>j); }

int calculateSeatIds_Puzzle1(std::string seatSpecification)
{
    int seatId;
    size_t pos;
    while ((pos = seatSpecification.find("B")) != std::string::npos) {
        seatSpecification.replace(pos, 1, "1");
    }
    while ((pos = seatSpecification.find("F")) != std::string::npos) {
        seatSpecification.replace(pos, 1, "0");
    }
    while ((pos = seatSpecification.find("R")) != std::string::npos) {
        seatSpecification.replace(pos, 1, "1");
    }
    while ((pos = seatSpecification.find("L")) != std::string::npos) {
        seatSpecification.replace(pos, 1, "0");
    }
    
    std::string seatColumn = seatSpecification.substr(7,3);
    std::string seatRow = seatSpecification.substr(0,7);
    int seatColumnDec;
    int seatRowDec;
      try {
        seatColumnDec = std::stoi(seatColumn,nullptr,2);
        seatRowDec = std::stoi(seatRow,nullptr,2);
        seatId = seatRowDec * 8 + seatColumnDec;
    }
    catch (const std::invalid_argument& ia) {
        //std::cerr << "Invalid argument for the seat specification: " << ia.what() << '\n';
        return 0;
    }
    //std::cout << "row: " <<seatRowDec << ", Column: " <<seatColumnDec <<",Id: " << seatId <<  std::endl;
    return seatId;
}

int main(int argc, char *argv[])
{   
    std::string fileName = argv[1];
    std::ifstream entries;
    std::vector<std::string> boardingPasses;
    std::string inputLine;
    
   
    entries.open(fileName);
    if (!entries.is_open())
    {
        std::cerr << "File can not be open \n" ;
        return -1;   
    }
    std::string line;
    
    while ( std::getline(entries, inputLine) )
    {   
        boardingPasses.push_back(inputLine);
    }
    entries.close();
    std::vector<int> seatIds;
    std::transform(boardingPasses.begin(),boardingPasses.end(), std::back_inserter(seatIds), calculateSeatIds_Puzzle1);
    std::sort (seatIds.begin(), seatIds.end(), returnBiggest); 

    std::cout << "result puzzle 1: " << seatIds.at(0) << std::endl;

    for(int i=0; i< seatIds.size()-1; i++)
    {
        if(seatIds.at(i+1)+1 != (seatIds.at(i)))
        {
            std::cout << "result puzzle 2: " << seatIds.at(i+1)+1 << std::endl;
            return 0;
        }
    }
    std::cerr << "Result Puzzle 2 not found, Seat Id Vector is continuous" << std::endl;

    return 0;
}