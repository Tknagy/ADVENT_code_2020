#include <cstdio>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "utils.h"

std::vector<ull> parse_input(const std::vector<std::string> &input)
{
    std::vector<ull> ret;
    const auto numbers = split(input.front(), ',');
    std::transform(numbers.begin(), numbers.end(), std::back_inserter(ret),
                   [](const auto &n) { return std::stoull(n); });
    return ret;
}

ull take_turn(const ull last_spoken_turn, const ull last_spoken, const std::unordered_map<ull, ull> &round_spoken)
{
    return (round_spoken.count(last_spoken) == 0) ? 0 : (last_spoken_turn - round_spoken.at(last_spoken));
}

ull find_spoken_number(const std::vector<std::string> &input, ull target_turn)
{
    const std::vector<ull> nums = parse_input(input);
    std::unordered_map<ull, ull> round_spoken;
    ull last_spoken = nums.back();
    ull turn = 1;
    for (; turn < nums.size(); turn++)
        round_spoken[nums[turn - 1]] = turn;

    for (; turn < target_turn; turn++) {
        ull spoken = take_turn(turn, last_spoken, round_spoken);
        round_spoken[last_spoken] = turn;
        last_spoken = spoken;
    }

    return last_spoken;
}

ull part_one(const std::vector<std::string> &input) { return find_spoken_number(input, 2020); }

ull part_two(const std::vector<std::string> &input) { return find_spoken_number(input, 30000000); }

int main(int argc, char const *argv[])
{
    auto input = read_stdin();
    std::cout << part_one(input) << '\n';
    std::cout << part_two(input) << '\n';
    return 0;
}
