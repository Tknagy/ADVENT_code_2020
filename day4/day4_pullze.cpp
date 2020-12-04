#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

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

struct Passport
{
    int byr;
    int iyr;
    int eyr;
    std::string hgtFormat;
    int hgtValue;
    int hcl;
    std::string ecl;
    double pid;
    int cid;
    Passport(): byr(-1), iyr(-1), eyr(-1), hgtFormat(""), hgtValue(-1), hcl(-1), ecl(""), pid(-1), cid(-1){}
};

std::vector<Passport> loadPassports(std::string fileName, bool print = false)
{
    std::string inputFileName = fileName;
    std::ifstream entriesFile;
    std::vector<Passport> myEntries;
    std::string tempString = "" ;
    Passport* tempPassport = new Passport();
    entriesFile.open(inputFileName);

    if (entriesFile.is_open())
    {   
        while ( std::getline(entriesFile, tempString) ) // Consumes each line of the file until EOF
        {   
           
            //Here, consume the file and populate each Passport.
            // Verifies if the field is empty or invalid ("" or -1, depending on th type) just to short shircuit the if and avoid unnecessary calls to find() 
            if(tempPassport->byr == -1 && tempString.find("byr:") != std::string::npos) sscanf(tempString.substr(tempString.find("byr:")+4).c_str(), "%d", &(tempPassport->byr));
            if(tempPassport->iyr == -1 && tempString.find("iyr:") != std::string::npos) sscanf(tempString.substr(tempString.find("iyr:")+4).c_str(), "%d", &(tempPassport->iyr));
            if(tempPassport->eyr == -1 && tempString.find("eyr:") != std::string::npos) sscanf(tempString.substr(tempString.find("eyr:")+4).c_str(), "%d", &(tempPassport->eyr));
            if(tempPassport->hcl == -1 && tempString.find("hcl:") != std::string::npos)
            {   
                char c = ' ';
                sscanf(tempString.substr(tempString.find("hcl:")+4).c_str(), "#%x", &(tempPassport->hcl));
                sscanf(tempString.substr(tempString.find("hcl:")+4).c_str(), "%x", &(tempPassport->hcl));
                sscanf(tempString.substr(tempString.find("hcl:")+4).c_str(), "%c", &c);
                if(c!= ' ')
                {
                    tempPassport->hcl=0;
                }
            } 
            if(tempPassport->pid == -1 && tempString.find("pid:") != std::string::npos) sscanf(tempString.substr(tempString.find("pid:")+4).c_str(), "%lf", &(tempPassport->pid));
            if(tempPassport->cid == -1 && tempString.find("cid:") != std::string::npos) sscanf(tempString.substr(tempString.find("cid:")+4).c_str(), "%d", &(tempPassport->cid));
            if(tempPassport->ecl == "" && tempString.find("ecl:") != std::string::npos) tempPassport->ecl = tempString.substr(tempString.find("ecl:")+4,3);
            //For the hgt field, check if it is in cm or in
            if(tempPassport->hgtValue == -1 && tempString.find("hgt:") != std::string::npos)
            {   
               
                std::string hgtTempString = tempString.substr(tempString.find("hgt:")+4);
                if( hgtTempString.find("in") != std::string::npos)
                {
                    tempPassport->hgtFormat = "in";
                    sscanf(hgtTempString.c_str(), "%din", &(tempPassport->hgtValue));
                }
                else if (hgtTempString.find("cm") != std::string::npos)
                {
                    tempPassport->hgtFormat = "cm";
                    sscanf(hgtTempString.c_str(), "%dcm", &(tempPassport->hgtValue));
                }
                else 
                {
                    std::cerr << "Error in the hgt field of one Passport - type undefined" << std::endl;
                    tempPassport->hgtFormat = "not specified";
                    sscanf(hgtTempString.c_str(), "%d", &(tempPassport->hgtValue));

                }            
            } 
            
            //If the line is empty, then Jump to the next Passport on the vector
            if(tempString.empty())
            {   
                myEntries.push_back(*tempPassport); 
                delete tempPassport; 
                tempPassport = new Passport();
            }
        }
        //As the last line does not ends with a \n, emplace the last Passport indo the entries vector
        myEntries.push_back(*tempPassport);
        delete tempPassport;        
        entriesFile.close();
    }
        std::cout << "Passports vector size: " << myEntries.size() << std::endl;
    if(print)
    {
        

        if(myEntries.size())
        {
            for(Passport p :myEntries)
            {   
                std::cout << "\nPrinting Passport:" << std::endl;
                std::cout << "byr: " << p.byr << std::endl;
                std::cout << "iyr: " << p.iyr << std::endl;
                std::cout << "eyr: " << p.eyr << std::endl;
                std::cout << "hgt: " << p.hgtValue << p.hgtFormat << std::endl;
                std::cout << "hcl: " << std::hex << p.hcl << std::dec << std::endl;
                std::cout << "ecl: " << p.ecl << std::endl;
                std::cout << "pid: " << p.pid << std::endl;
                std::cout << "cid: " << p.cid << std::endl; 
            }

        }
    }

    return myEntries;
}

int countValidPassports(std::vector<Passport> passports, bool includeNorthPoleCredentials = true)
{   
    int validPassportsCounter = 0;

    for(Passport p : passports)
    {   
        if(includeNorthPoleCredentials)
        {
            if(p.byr == -1  || p.eyr == -1 || p.hcl == -1 || p.hgtValue == -1 || p.iyr == -1 || p.pid == -1 || p.ecl == "")
            {
                
            }
            else validPassportsCounter++;
        }
        else
        {
            if(p.byr == -1 || p.cid == -1 || p.eyr == -1 || p.hcl == -1 || p.hgtValue == -1 || p.iyr == -1 || p.pid == -1 || p.ecl == "")
            {
               
            }
            else validPassportsCounter++;
        }
        
      
    }

    return validPassportsCounter;
}

int main(int argc, char *argv[])
{   
    
    std::cout << "Total valid passports: " << countValidPassports(loadPassports(argv[1])) << std::endl;

    return 0;
}