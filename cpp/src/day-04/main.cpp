#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <regex>

static std::vector<std::string> read_stdin()
{
    std::vector<std::string> input = {""};
    for (std::string line; std::getline(std::cin, line);) {
        if (!line.empty())
            input.back().append(" ").append(line);
        else
            input.push_back("");
    }
    return input;
}

bool part_one(const std::string &line)
{
    if (line.find("byr") != std::string::npos &&
        line.find("iyr") != std::string::npos &&
        line.find("eyr") != std::string::npos &&
        line.find("hgt") != std::string::npos &&
        line.find("hcl") != std::string::npos &&
        line.find("ecl") != std::string::npos &&
        line.find("pid") != std::string::npos)
        return true;
    else
        return false;
}

bool validate_byr(const std::string &byr)
{
    std::regex regex("^(19[0-9]{2}|200[0-3])$");
    if (std::regex_match(byr, regex))
        return true;
    else
        return false;
}

bool validate_iyr(const std::string &iyr)
{
    std::regex regex("^(201[0-9]|2020)$");
    if (std::regex_match(iyr, regex))
        return true;
    else
        return false;
}

bool validate_eyr(const std::string &eyr)
{
    std::regex regex("^(202[0-9]|2030)$");
    if (std::regex_match(eyr, regex))
        return true;
    else
        return false;
}

bool validate_hgt(const std::string &hgt)
{
    int height;
    std::string units;
    std::stringstream tmp(hgt);
    tmp >> height >> units;

    if (units == "cm" &&
        150 <= height &&
        193 >= height)
        return true;
    else if (units == "in" &&
        59 <= height &&
        76 >= height)
        return true;
    else
        return false;
    
}

bool validate_hcl(const std::string &hcl)
{
    const std::regex regex("^#[0-9a-f]{6}$");
    if (std::regex_match(hcl, regex))
        return true;
    else
        return false;
}

bool validate_ecl(const std::string &ecl)
{
    const std::regex regex("^(amb|blu|brn|gry|grn|hzl|oth)$");
    if (std::regex_match(ecl, regex))
        return true;
    else
        return false;
}

bool validate_pid(const std::string &pid)
{
    const std::regex regex("^[0-9]{9}$");
    if (std::regex_match(pid, regex))
        return true;
    else
        return false;
}

bool validate_field(const std::string &field, const std::string &line, bool (*validate_function)(const std::string &val))
{
    size_t init;
    init = line.find(field);
    if (init == std::string::npos)
        return false;

    init = init + field.size();
    unsigned int len = line.find(' ', init) - init;
    if (!validate_function(line.substr(init, len)))
        return false;
    return true;
}


bool part_two(const std::string &line)
{
    if (!validate_field("byr:", line, validate_byr))
        return false;

    if (!validate_field("iyr:", line, validate_iyr))
        return false;

    if (!validate_field("eyr:", line, validate_eyr))
        return false;

    if (!validate_field("hgt:", line, validate_hgt))
        return false;

    if (!validate_field("hcl:", line, validate_hcl))
        return false;

    if (!validate_field("ecl:", line, validate_ecl))
        return false;

    if (!validate_field("pid:", line, validate_pid))
        return false;
    return true;
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> input = read_stdin();
    std::vector<bool> first, second;
    std::transform(input.begin(), input.end(), std::back_inserter(first), part_one);
    std::transform(input.begin(), input.end(), std::back_inserter(second), part_two);
    std::cout << std::count(first.begin(), first.end(), true) << std::endl;
    std::cout << std::count(second.begin(), second.end(), true) << std::endl;
    return 0;
}
