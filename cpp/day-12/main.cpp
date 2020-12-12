#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <utility>
#include <vector>

#include "utils.h"

std::pair<char, ull> parse_instruction(const std::string &instruction)
{
    std::istringstream inst(instruction);
    char action;
    ull value;
    inst >> action >> value;
    return std::make_pair(action, value);
}

std::pair<ll, ll> rotate(const std::pair<ll, ll> &vec, const ll degrees)
{
    std::pair<ll, ll> ret;
    double angle = degrees * M_PI / 180;
    ret.first = std::llround(vec.first * cos(angle) - vec.second * sin(angle));
    ret.second = std::llround(vec.first * sin(angle) + vec.second * cos(angle));
    return ret;
}

ull part_one(const std::vector<std::string> &instructions)
{
    std::pair<ll, ll> pos(0, 0);
    ll heading = 0;

    for (const auto &instruction : instructions) {
        auto [action, value] = parse_instruction(instruction);
        switch (action) {
        case 'N':
            pos.second += value;
            break;
        case 'S':
            pos.second -= value;
            break;
        case 'E':
            pos.first += value;
            break;
        case 'W':
            pos.first -= value;
            break;
        case 'L':
            heading += value;
            break;
        case 'R':
            heading -= value;
            break;
        case 'F':
            pos.first += std::llround(value * cos(heading * M_PI / 180));
            pos.second += std::llround(value * sin(heading * M_PI / 180));
            break;
        default:
            break;
        }
    }
    return std::abs(pos.first) + std::abs(pos.second);
}

ull part_two(const std::vector<std::string> &instructions)
{
    std::pair<ll, ll> pos(0, 0);
    std::pair<ll, ll> waypoint(10, 1);
    auto tmp = waypoint;

    for (const auto &instruction : instructions) {
        auto [action, value] = parse_instruction(instruction);
        switch (action) {
        case 'N':
            waypoint.second += value;
            break;
        case 'S':
            waypoint.second -= value;
            break;
        case 'E':
            waypoint.first += value;
            break;
        case 'W':
            waypoint.first -= value;
            break;
        case 'L':
            waypoint = rotate(waypoint, value);
            break;
        case 'R':
            waypoint = rotate(waypoint, -value);
            break;
        case 'F':
            pos.first += value * waypoint.first;
            pos.second += value * waypoint.second;
            break;

        default:
            break;
        }
    }
    return std::abs(pos.first) + std::abs(pos.second);
}

int main(int argc, char const *argv[])
{
    auto input = read_stdin();

    std::cout << part_one(input) << '\n';
    std::cout << part_two(input) << '\n';
    return 0;
}
