#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

static std::vector<std::string> read_stdin()
{
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line))
        input.push_back(line);
    return input;
}

std::tuple<std::uint32_t, std::uint32_t, char, std::string> parse_information(const std::string &line)
{
    int first, second;
    char letter;
    sscanf(line.c_str(), "%d-%d %c:", &first, &second, &letter);
    std::string password(line.substr(line.find(":") + 2));

    return std::make_tuple(first, second, letter, password);
}

static bool part_one(const std::string &line)
{
    auto [min, max, letter, password] = parse_information(line);
    auto qty = std::count(password.begin(), password.end(), letter);
    return (min <= qty && qty <= max) ? true : false;
}

static bool part_two(const std::string &line)
{
    auto [first, second, letter, pwd] = parse_information(line);
    return ((pwd[first - 1] == letter) != (pwd[second - 1] == letter)) ? true : false;
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> input = read_stdin();
    std::vector<bool> first, second;
    std::transform(input.begin(), input.end(), std::back_inserter(first), part_one);
    std::transform(input.begin(), input.end(), std::back_inserter(second), part_two);
    printf("%ld\n", std::count(first.begin(), first.end(), true));
    printf("%ld\n", std::count(second.begin(), second.end(), true));
    return 0;
}
