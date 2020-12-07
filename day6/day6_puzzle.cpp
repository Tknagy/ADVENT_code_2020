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
    std::set<char> uniqueAnswers;
    uint8_t commonAnswersSize ;
    //count number of users in the group using the space delimiter 
    size_t groupSize = std::count(groupAnswers.begin(), groupAnswers.end(), ' ');

    //Then, populate the set with all answers in the group
    for(auto answerChar : groupAnswers)
    {   
        if(answerChar != ' ') uniqueAnswers.insert(answerChar);
    }
    //To check common answers;
    //for this, consider that all unique answers are common answers
    commonAnswersSize = uniqueAnswers.size();
    //then, for all given answers
    for(auto oneAnswer : uniqueAnswers)
    {   
        //check which chars does not repeat in all user responses by counting it and comparing with the group size
        //if the value is different than the group size, it means that this unique char does not appear in one of the user entries and
        //therefore is not common. Therefore, decrease the commonAnswersSize;
        if(std::count(groupAnswers.begin(), groupAnswers.end(), oneAnswer) != groupSize)commonAnswersSize--;
    }
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