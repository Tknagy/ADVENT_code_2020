#include <algorithm>
#include <sstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

#include "utils.h"

std::string unsorted_intersection(std::string first, std::string second)
{
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());

    std::string res;
    std::set_intersection(first.begin(), first.end(),
                        second.begin(), second.end(),
                        std::back_inserter(res));
    return res;
}

unsigned int part_one(const std::string &line)
{
    std::unordered_set<char> questions;
    for (auto &&letter : line)
        if (letter != ' ')
            questions.insert(letter);
    return questions.size();
}

unsigned int part_two(const std::string &line)
{
    std::vector<std::string> answers = split(line, ' ');
    if (answers.size() == 1)
        return answers.front().size();

    std::string init = "abcdefghijklmnopqrstuvwxyz";
    std::string res = std::reduce(answers.begin(), answers.end(), init, unsorted_intersection);
    return res.size();
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> input = read_stdin_ungrouped();
    std::vector<unsigned int> first, second;
    std::transform(input.begin(), input.end(), std::back_inserter(first), part_one);
    std::transform(input.begin(), input.end(), std::back_inserter(second), part_two);
    std::cout << std::reduce(first.begin(), first.end()) << std::endl;
    std::cout << std::reduce(second.begin(), second.end()) << std::endl;
    return 0;
}
