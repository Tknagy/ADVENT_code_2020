
#include "utils.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &s, const char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);

    for (std::string token; std::getline(iss, token, delim);)
        result.push_back(std::move(token));

    return result;
}

std::vector<std::string> read_stdin()
{
    std::vector<std::string> input;
    for (std::string line; std::getline(std::cin, line);)
        input.push_back(line);
    return input;
}

std::vector<std::string> read_stdin_ungrouped()
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

std::vector<std::string> read_file(const std::string &filename)
{
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("Could not open file " + filename);
    }
    std::vector<std::string> input;
    for (std::string line; std::getline(file, line);)
        input.push_back(line);
    file.close();
    return input;
}

std::vector<std::string> read_file_ungrouped(const std::string &filename)
{
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("Could not open file " + filename);
    }
    std::vector<std::string> input;
    for (std::string line; std::getline(file, line);) {
        if (!line.empty())
            input.back().append(line).append(" ");
        else
            input.push_back("");
    }
    file.close();
    return input;
}