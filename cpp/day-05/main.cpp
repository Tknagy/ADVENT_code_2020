#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "utils.h"

unsigned int seat_id(const std::string &line)
{
    unsigned int min = 0;
    unsigned int max = 127;

    for (size_t i = 0; i < 7; i++) {
        if (line[i] == 'F')
            max -= (max - min) / 2.0;
        else if (line[i] == 'B')
            min += (max - min) / 2.0 + 1;
        else
            std::abort();
    }
    if (min != max)
        std::abort();
    unsigned int row = min;

    min = 0;
    max = 7;
    for (size_t i = 0; i < 3; i++) {
        if (line[7 + i] == 'L')
            max -= (max - min) / 2.0;
        else if (line[7 + i] == 'R')
            min += (max - min) / 2.0 + 1;
        else
            std::abort();
    }
    if (min != max)
        std::abort();
    unsigned int column = min;

    return 8 * row + column;
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> input = read_stdin();
    std::vector<unsigned int> ids;
    std::transform(input.begin(), input.end(), std::back_inserter(ids), seat_id);
    std::sort(ids.begin(), ids.end());

    const auto it =
        std::adjacent_find(ids.begin(), ids.end(), [](unsigned int a, unsigned int b) { return (b - a) != 1; });

    std::cout << ids.back() << '\n';
    std::cout << (*it) + 1 << '\n';

    return 0;
}
