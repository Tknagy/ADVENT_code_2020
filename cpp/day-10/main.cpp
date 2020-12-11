#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <vector>

#include "utils.h"

using ull = unsigned long long;

std::vector<ull> parse_input(const std::vector<std::string> &input)
{
    std::vector<ull> jolts{0};
    std::transform(input.begin(), input.end(), std::back_inserter(jolts), [](const auto &s) { return std::stoull(s); });
    std::sort(jolts.begin(), jolts.end());
    jolts.push_back(jolts.back() + 3);
    return jolts;
}

ull part_one(const std::vector<ull> &jolts)
{
    std::vector<ull> diff;
    std::adjacent_difference(jolts.begin(), jolts.end(), std::back_inserter(diff));
    return std::count(diff.begin(), diff.end(), 1) * std::count(diff.begin(), diff.end(), 3);
}

ull count_branches(const ull from, const std::vector<ull> &jolts)
{
    static std::unordered_map<ull, ull> cache;
    if (cache.count(from) == 1)
        return cache[from];

    if (!std::binary_search(jolts.begin(), jolts.end(), from))
        return 0;

    if (from == jolts.back())
        return 1;

    ull sum = 0;
    for (ull i = 0; i < 3; i++) {
        sum += count_branches(from + i + 1, jolts);
    }

    cache[from] = sum;
    return sum;
}

ull part_two(const std::vector<ull> &jolts) { return count_branches(jolts.front(), jolts); }

int main(int argc, char const *argv[])
{
    auto input = read_stdin();
    auto jolts = parse_input(input);
    std::cout << part_one(jolts) << '\n';
    std::cout << part_two(jolts) << '\n';

    return 0;
}
