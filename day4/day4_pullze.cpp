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
    int pid;
    int cid;
    Passport(): byr(-1), iyr(-1), eyr(-1), hgtFormat(""), hgtValue(-1), hcl(-1), ecl(""), pid(-1), cid(-1){}
};

int main(int argc, char *argv[])
{   
    std::string inputFileName = argv[1];
    std::ifstream entriesFile;
    std::vector<Passport> myEntries;
    std::string tempString = "" ;
    Passport* tempPassport = new Passport();
    entriesFile.open(inputFileName);

    if (entriesFile.is_open())
    {   
        while ( std::getline(entriesFile, tempString) ) // Consumes each line of the file until EOF
        {   
            std::cout<< "inside getline" << std::endl;
            //Here, consume the file and populate each Passport.
            // Verifies if the field is empty or invalid ("" or -1, depending on th type) just to short shircuit the if and avoid unnecessary calls to find() 
            if(tempPassport->byr == -1 && tempString.find("byr:") != std::string::npos) sscanf(tempString.c_str(), "byr:%d", &(tempPassport->byr));
            if(tempPassport->iyr == -1 && tempString.find("iyr:") != std::string::npos) sscanf(tempString.c_str(), "iyr:%d", &(tempPassport->iyr));
            if(tempPassport->eyr == -1 && tempString.find("eyr:") != std::string::npos) sscanf(tempString.c_str(), "eyr:%d", &(tempPassport->eyr));
            if(tempPassport->hcl == -1 && tempString.find("hcl:") != std::string::npos) sscanf(tempString.c_str(), "hcl:%d", &(tempPassport->hcl));
            if(tempPassport->pid == -1 && tempString.find("pid:") != std::string::npos) sscanf(tempString.c_str(), "pid:%d", &(tempPassport->pid));
            if(tempPassport->cid == -1 && tempString.find("cid:") != std::string::npos) sscanf(tempString.c_str(), "cid:%d", &(tempPassport->cid));
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
                else std::cerr << "Error in the hgt field of one Passport - type undefined" << std::endl;
            } 
            
            //If the line is empty, then Jump to the next Passport on the vector
            if(tempString.empty())
            {   
                myEntries.push_back(*tempPassport);  
                tempPassport = new Passport();
            }
        }
        //As the last line does not ends with a \n, emplace the last Passport indo the entries vector
        myEntries.push_back(*tempPassport);        
        entriesFile.close();
    }

    std::cout << "Passports vector size: " << myEntries.size() << std::endl;

    if(myEntries.size())
    {
        for(Passport p :myEntries)
        {   
            std::cout << "\nPrinting Passport:" << std::endl;
            std::cout << "byr: " << p.byr << std::endl;
            std::cout << "iyr: " << p.iyr << std::endl;
            std::cout << "eyr: " << p.eyr << std::endl;
            std::cout << "hgt: " << p.hgtValue << p.hgtFormat << std::endl;
            std::cout << "hcl: " << p.hcl << std::endl;
            std::cout << "ecl: " << p.ecl << std::endl;
            std::cout << "pid: " << p.pid << std::endl;
            std::cout << "cid: " << p.cid << std::endl; 
        }

    }

    return 0;
}