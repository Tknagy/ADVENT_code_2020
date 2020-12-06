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


bool getValueWithKey(std::string inputString, std::string regexString,bool returnString=false, std::string *returnedValue = NULL)
{
    auto const internRegex = std::regex(regexString);
    auto const spaceRegex = std::regex(" ");
    auto positionOfValueField = std::smatch{};
    bool const myTextContainsRegex = std::regex_search(inputString, positionOfValueField, internRegex);
    if(returnString && myTextContainsRegex)
    {   
        inputString = inputString.substr(positionOfValueField.prefix().length()+regexString.length());//gets substring starting from key
        std::regex_search(inputString, positionOfValueField, spaceRegex);// executes regex now to find position of " " a.k.a end of value field
        inputString = inputString.substr(0,positionOfValueField.prefix().length());//gets value substring until a space is found
        
        returnedValue->append(inputString);
    }
    
    return myTextContainsRegex;
}

uint8_t validatePassport_Puzzle1(std::string passportLine)
{      
    return getValueWithKey(passportLine,"byr:",false,NULL) &&
    getValueWithKey(passportLine,"iyr:",false,NULL) &&
    getValueWithKey(passportLine,"eyr:",false,NULL) &&
    getValueWithKey(passportLine,"hgt:",false,NULL) &&
    getValueWithKey(passportLine,"hcl:",false,NULL) &&
    getValueWithKey(passportLine,"ecl:",false,NULL) &&
    getValueWithKey(passportLine,"pid:",false,NULL);
    
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



uint8_t validatePassport_Puzzle2(std::string passportLine)
{   
    std::string byr;
    std::string iyr;
    std::string eyr;
    std::string hgt;
    std::string hcl;
    std::string ecl;
    std::string pid;
    getValueWithKey(passportLine,"byr:",true,&byr);
    getValueWithKey(passportLine,"iyr:",true,&iyr);
    getValueWithKey(passportLine,"eyr:",true,&eyr);
    getValueWithKey(passportLine,"hgt:",true,&hgt);
    getValueWithKey(passportLine,"hcl:#",true,&hcl);
    getValueWithKey(passportLine,"ecl:",true,&ecl);
    getValueWithKey(passportLine,"pid:",true,&pid);
    

    // byr (Birth Year) - four digits; at least 1920 and at most 2002.  
    int byrDec;
     try {
        byrDec = std::stoi(byr);
    }
    catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument for the passport id: " << ia.what() << '\n';
        return 0;
    }
    if(byrDec < 1920 || byrDec > 2002) return 0;

    // iyr (Issue Year) - four digits; at least 2010 and at most 2020.
    int iyrDec;
    try {
        iyrDec = std::stoi(iyr);
    }
    catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument for the passport id: " << ia.what() << '\n';
        return 0;
    }
    if(iyrDec < 2010 || iyrDec > 2020) return 0;

    // eyr (Expiration Year) - four digits; at least 2020 and at most 2030.
    int eyrDec;
    try {
        eyrDec = std::stoi(eyr);
        std::cout << "eyrDec:" << eyrDec << std::endl;
    }
    catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument for the passport id: " << ia.what() << '\n';
        return 0;
    }
    
    if(eyrDec < 2020 || eyrDec > 2030) return 0;

    // hgt (Height) - a number followed by either cm or in:
    // If cm, the number must be at least 150 and at most 193.
    // If in, the number must be at least 59 and at most 76.
    int hgtDec;
    if(getValueWithKey(hgt,"cm",false,NULL))
    {
        hgtDec = std::stoi(hgt.substr(0, hgt.size()-2));
        if(hgtDec < 150 || hgtDec > 193) return 0;
    }else if(getValueWithKey(hgt,"in",false,NULL))
    {
        hgtDec = std::stoi(hgt.substr(0, hgt.size()-2));
        if(hgtDec < 59 || hgtDec > 76) return 0;
    }else return 0; // if cm nor in is present on hgt String

    // hcl (Hair Color) - a # followed by exactly six characters 0-9 or a-f.
    if(hcl.size() == 6)
    {   
        //try to read the value that is expected to be an HEX
        try {
           int hclHex = std::stoi(hcl,nullptr,16);
        }
        catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument for the hair color: " << ia.what() << '\n';
            return 0;
        }
        
    }else return 0; // if the length is not 6, it isn't valid
    
    // ecl (Eye Color) - exactly one of: amb blu brn gry grn hzl oth.
    if(ecl == "amb" || ecl == "blu" || ecl == "brn" || ecl == "gry" || ecl == "grn" || ecl == "hzl" || ecl == "oth" )
    {

    }
    else return 0;
    // pid (Passport ID) - a nine-digit number, including leading zeroes.
    if(pid.length()==9)
    {
        //try to read the value that is expected to be a number
        try {
           long long pidDec = std::stoll(pid);
        }
        catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument for the passport id: " << ia.what() << '\n';
            return 0;
        }
    }
    else return 0;
    // cid (Country ID) - ignored, missing or not. So, doesnt even consider it
    //If all criterias passed, then return true a.k.a the passport is valid
    return 1;

}

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
        if(!inputLine.empty()) passports.back().append(inputLine+ " ");
        else passports.push_back("");
    }
    entries.close();
    std::vector<uint8_t> passportCounter;
    std::transform(passports.begin(),passports.end(), std::back_inserter(passportCounter),validatePassport_Puzzle2);

    std::cout << "result puzzle 1: " << std::accumulate(passportCounter.begin(),passportCounter.end(),0) << std::endl;

    return 0;
}