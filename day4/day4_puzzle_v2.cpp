#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<algorithm>
#include<numeric>
#include <regex>

//Puzzle 1 Objective:
// Read from the data on day4_input and detect the following substrings:
// byr ->(Birth Year)
// iyr ->(Issue Year)
// eyr ->(Expiration Year)
// hgt ->(Height)
// hcl ->(Hair Color)
// ecl ->(Eye Color)
// pid ->(Passport ID)
// cid ->(Country ID) -> NOT RELEVANT FOR PUZZLE 1
//If the above fields are there, then consider it as a valid passport

uint8_t validatePassport(std::string passportLine)
{
    if(passportLine.find("byr:") != std::string::npos &&
    passportLine.find("iyr:") != std::string::npos &&
    passportLine.find("eyr:") != std::string::npos &&
    passportLine.find("hgt:") != std::string::npos &&
    passportLine.find("hcl:") != std::string::npos &&
    passportLine.find("ecl:") != std::string::npos &&
    passportLine.find("pid:") != std::string::npos )return 1;
    else return 0;

}

uint8_t validatePassportWithRegex(std::string passportLine)
{   
    auto const regexByr = std::regex("byr:");
    auto const regexIyr = std::regex("iyr:");
    auto const regexEyr = std::regex("eyr:");
    auto const regexHgt = std::regex("hgt:");
    auto const regexHcl = std::regex("hcl:");
    auto const regexEcl = std::regex("ecl:");
    auto const regexPid = std::regex("pid:");
    return std::regex_search(passportLine, regexByr) && 
    std::regex_search(passportLine, regexIyr) && 
    std::regex_search(passportLine, regexEyr) && 
    std::regex_search(passportLine, regexHgt) && 
    std::regex_search(passportLine, regexHcl) && 
    std::regex_search(passportLine, regexEcl) && 
    std::regex_search(passportLine, regexPid);
    

}
//Puzzle 2 Objective: validate the data as follows
// byr (Birth Year) - four digits; at least 1920 and at most 2002.
// iyr (Issue Year) - four digits; at least 2010 and at most 2020.
// eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
// hgt (Height) - a number followed by either cm or in:
// If cm, the number must be at least 150 and at most 193.
// If in, the number must be at least 59 and at most 76.
// hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
// ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
// pid (Passport ID) - a nine-digit number, including leading zeroes.
// cid (Country ID) - ignored, missing or not.

// uint8_t validatePassport_puzzle2(std::string passportLine)
// {   
//     int byr;
//     int iyr;
//     int eyr;
//     std::string hgtString;
//     int hgtValue;
//     int hcl;
//     std::string ecl;
//     double pid;
//     //int cid;
    
//     if(sscanf(passportLine.substr(passportLine.find("byr:")+4).c_str(), "%d", &(byr)) )
//     {
//         if(byr <2002 || byr >1920) return 0;
//     } 
//     else return 0;
//     if(sscanf(passportLine.substr(passportLine.find("iyr:")+4).c_str(), "%d", &(iyr)) )
//     {
//         if(iyr <2010 || iyr >2020) return 0;
//     } 
//     else return 0;
//     if(sscanf(passportLine.substr(passportLine.find("eyr:")+4).c_str(), "%d", &(eyr)) )
//     {
//         if(eyr <2020 || eyr >2030) return 0;
//     } 
//     else return 0;
    
//     std::size_t sizeOfHclField = passportLine.find(" ",passportLine.find("hcl:#")+5);
//     if(sizeOfHclField == 6 && sscanf(passportLine.substr(passportLine.find("hcl:#")+5,sizeOfHclField).c_str(), "%x", &(hcl)) )
//     {} 
//     else return 0;
//     std::size_t sizeOfPidField = passportLine.find(" ",passportLine.find("pid:")+4);
//     if(sizeOfPidField==9 && sscanf(passportLine.substr(passportLine.find("pid:")+4,sizeOfPidField ).c_str(), "%d", &(pid)))
//     {}
//     else return 0;
    
//     ecl = passportLine.substr(passportLine.find("ecl:")+4);
//     if(ecl == "amb" || ecl == "blu" || ecl == "brn" || ecl == "gry" || ecl == "grn" || ecl == "hzl" || ecl == "oth" )
//     {
//     } 
    
//     //For the hgt field, check if it is in cm or in
//     passportLine.find("cm",passportLine.find("hgt:")+4);
//     std::size_t sizeOfHgtField = passportLine.find("cm",passportLine.find("hgt:")+4);
//     if( sizeOfHgtField != std::string::npos)
//     {   
//         //verify for cm
//         sscanf(passportLine.substr(passportLine.find("hgt:")+4,sizeOfHgtField).c_str(),"%d",&hgtValue );
//         // If cm, the number must be at least 150 and at most 193.
//         if(hgtValue <150 || hgtValue >193 )return 0;          
//     }
//     else return 0;



//     // If in, the number must be at least 59 and at most 76.
//     else 
//     {
//         std::cerr << "Error in the hgt field of one Passport - type undefined" << std::endl;
//         tempPassport->hgtFormat = "not specified";
//         sscanf(hgtTempString.c_str(), "%d", &(tempPassport->hgtValue));

//     }   

//     return 1;

// }

int main(int argc, char *argv[])
{   
    std::string fileName = argv[1];
    std::ifstream entries;
    std::vector<std::string> passports;
    std::string inputLine;
    
   
    entries.open(fileName);
    if (!entries.is_open())
    {
        std::cerr << "File can not be open \n" ;
        return -1;   
    }
    std::string line;
    passports.push_back("");
    while ( std::getline(entries, inputLine) )
    {   
        if(!inputLine.empty()) passports.back().append(inputLine);
        else passports.push_back("");
    }
    entries.close();
    std::vector<uint8_t> passportCounter;
    std::transform(passports.begin(),passports.end(), std::back_inserter(passportCounter),validatePassportWithRegex);

    std::cout << "result puzzle 1: " << std::accumulate(passportCounter.begin(),passportCounter.end(),0) << std::endl;

    return 0;
}