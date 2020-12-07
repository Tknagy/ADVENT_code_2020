#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<algorithm>
#include<numeric>
#include <set>

uint8_t calculateYesAnswers_Puzzle1(std::string groupAnswers)
{
    std::set<char> uniqueAnswers;

    for(auto answerChar : groupAnswers)
    {   
        if(answerChar != ' ') uniqueAnswers.insert(answerChar);
    }

    return uniqueAnswers.size();
}

uint8_t calculateYesAnswers_Puzzle2(std::string groupAnswers)
{
    
    uint8_t commonAnswersSize = 0 ;
    //count number of users in the group using the space delimiter 
    size_t groupSize = std::count(groupAnswers.begin(), groupAnswers.end(), ' ');

    //Then, check if the occurence of each letter from a-z in the group answers. 
    //If equal to group size, add one to commonAnswerSize
    for (char c = 'a'; c <= 'z'; ++c) if(std::count(groupAnswers.begin(), groupAnswers.end(), c) == groupSize)commonAnswersSize++;

    return commonAnswersSize;
}



int main(int argc, char *argv[])
{   
    std::string fileName = argv[1];
    std::ifstream entries;
    std::vector<std::string> groupQuestions;
    std::string inputLine;
    
   
    entries.open(fileName);
    if (!entries.is_open())
    {
        std::cerr << "File can not be open \n" ;
        return -1;   
    }
    std::string line;
    groupQuestions.push_back("");
    while ( std::getline(entries, inputLine) )
    {   
        if(!inputLine.empty()) groupQuestions.back().append(inputLine+ " ");
        else groupQuestions.push_back("");
    }
    entries.close();
    std::vector<uint8_t> yesAnswerCounter;
    std::transform(groupQuestions.begin(),groupQuestions.end(), std::back_inserter(yesAnswerCounter),calculateYesAnswers_Puzzle1);

    std::cout << "result puzzle 1: " << std::accumulate(yesAnswerCounter.begin(),yesAnswerCounter.end(),0) << std::endl;

    //for(auto s : groupQuestions) std::cout << s << std::endl;

    std::vector<uint8_t> commonAnswerCounter;
    std::transform(groupQuestions.begin(),groupQuestions.end(), std::back_inserter(commonAnswerCounter),calculateYesAnswers_Puzzle2);

    std::cout << "result puzzle 1: " << std::accumulate(commonAnswerCounter.begin(),commonAnswerCounter.end(),0) << std::endl;

    return 0;
}