#include <algorithm>
#include <sstream>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

std::vector<std::string> split(std::string const &s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim); )
        result.push_back(std::move(token));

    return result;
}

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

static std::vector<std::string> read_stdin()
{
    std::vector<std::string> input = {""};
    for (std::string line; std::getline(std::cin, line);) {
        if (!line.empty())
            input.back().append(line).append(" ");
        else
            input.push_back("");
    }
    return input;
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
    std::vector<std::string> input = read_stdin();
    std::vector<unsigned int> first, second;
    std::transform(input.begin(), input.end(), std::back_inserter(first), part_one);
    std::transform(input.begin(), input.end(), std::back_inserter(second), part_two);
    std::cout << std::reduce(first.begin(), first.end()) << std::endl;
    std::cout << std::reduce(second.begin(), second.end()) << std::endl;
    return 0;
}
