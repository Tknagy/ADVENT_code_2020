#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<regex>
#include<map>

void expandBaggageSearch(std::set<std::string>* luggagesThatSomehowContainsGoldenLuggage,
std::map<std::string, std::vector<std::pair<std::string, int>>>* inputLuggages)
{
    //bool somethingFound = false;
    for( auto relevantLuggage : *luggagesThatSomehowContainsGoldenLuggage)    
    {
        for(auto l : *inputLuggages)
        {
            for(auto l2 : l.second)
            {
                if(l2.first == relevantLuggage)
                {   
                    //add baggage to list if not there already
                    if(luggagesThatSomehowContainsGoldenLuggage->find(l.first) == luggagesThatSomehowContainsGoldenLuggage->end())
                    {
                        luggagesThatSomehowContainsGoldenLuggage->insert(l.first);
                        //std::cout << "Baggage " << relevantLuggage << " found inside baggage " << l.first <<std::endl;
                        expandBaggageSearch(luggagesThatSomehowContainsGoldenLuggage,inputLuggages);
                        
                    }
                }
            }
        }
    }
}

int calculateNumberOfBagsInside(std::string luggageName,
std::map<std::string, std::vector<std::pair<std::string, int>>>* inputLuggages)
{
    int numerOfBaggsInside = 1;
    if(inputLuggages->find(luggageName) != inputLuggages->end())
    {
        for(auto v : inputLuggages->find(luggageName)->second)
        {
            numerOfBaggsInside += v.second * calculateNumberOfBagsInside(v.first, inputLuggages);
            //std::cout << "inside calculatenumber w value: " << numerOfBaggsInside << std::endl;
        }
        
    }
    
    return numerOfBaggsInside;
}



int main(int argc, char *argv[])
{   
    std::string fileName = argv[1];
    std::string baggageToSearch = "shiny gold";
    std::ifstream entries;
    std::string inputLine;
    std::map<std::string, std::vector<std::pair<std::string, int>>> inputLuggages;
    std::string containDelimiter = " bags contain ";
    
    // Step 1: populate luggages with all luggages from input
    entries.open(fileName);
    if (!entries.is_open())
    {
        std::cerr << "File can not be open \n" ;
        return -1;   
    }
    while ( std::getline(entries, inputLine) )
    {   
        
        if(!inputLine.empty())
        {  
            std::regex self_regex(containDelimiter,
            std::regex_constants::ECMAScript | std::regex_constants::icase);
            std::smatch myRegexMatch;
            std::regex bag_contain_regex("( bags contain )",
            std::regex_constants::ECMAScript | std::regex_constants::icase);
            std::regex contained_bag_regex("( bag)(s)?(,)?(.)?",
            std::regex_constants::ECMAScript | std::regex_constants::icase);
            std::regex contained_bag_amout_regex("(\\d)( )(.*)",
            std::regex_constants::ECMAScript | std::regex_constants::icase);
            
            

            if (std::regex_search(inputLine,myRegexMatch,bag_contain_regex)) {
                //std::cout << "Text contains the phrase "<< luggageDelimitatorString <<"\n";
                std::string inputLuggage;
                std::vector<std::pair<std::string, int>> luggagesInside;
                inputLuggage = myRegexMatch.prefix().str();
                //remove substring with baggage color and keep only internal baggages
                inputLine = inputLine.substr(myRegexMatch.prefix().str().size() +myRegexMatch[0].str().size());
                //std::cout << "Baggage: " << inputLuggage <<std::endl;
                
                while(std::regex_search(inputLine,myRegexMatch,contained_bag_regex))
                {   
                    std::smatch bag_amount_match;
                    if(std::regex_search(myRegexMatch.prefix().str(),bag_amount_match,contained_bag_amout_regex))
                    {
                        int auxInputLuggageAmount = stoi(bag_amount_match[1].str());
                        std::string auxInputLuggage = bag_amount_match[3].str();
                        luggagesInside.push_back(make_pair(auxInputLuggage, auxInputLuggageAmount));
                        //std::cout << "Contains: " << auxInputLuggage <<std::endl;
                    }
                    //remove substring with first occurence of internal baggage
                    inputLine = inputLine.substr(myRegexMatch.prefix().str().size()+myRegexMatch[0].str().size()); 
                    
                    
                }
                
                inputLuggages.insert(make_pair(inputLuggage, luggagesInside));
            }
            else  std::cerr << "Error: Text does not contains the phrase " <<"\n";

        }
        else std::cerr << "Input line is empty, cannot read Luggage information." << std::endl;
    }
    entries.close();


    std::set<std::string> luggagesThatSomehowContainsGoldenLuggage;
    
    luggagesThatSomehowContainsGoldenLuggage.insert(baggageToSearch);
    expandBaggageSearch(&luggagesThatSomehowContainsGoldenLuggage, &inputLuggages);
    std::cout << "Result puzzle 1: " <<luggagesThatSomehowContainsGoldenLuggage.size()-1 <<std::endl;;

    std::cout << "Result puzzle 2: " << calculateNumberOfBagsInside(baggageToSearch,  &inputLuggages)-1 << std::endl;

    return 0;
}