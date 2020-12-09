#include <algorithm>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <numeric>
#include <string>
#include <tuple>
#include <vector>

#include "utils.h"

using ull = unsigned long long;

std::tuple<std::deque<ull>, std::deque<ull>> get_preamble_and_numbers(const int preamble_len,
                                                                      const std::deque<ull> &list)
{
    std::deque<ull> preamble;
    for (size_t i = 0; i < preamble_len; i++)
        preamble.push_back(list[i]);

    std::deque<ull> numbers(std::next(list.begin(), preamble_len), list.end());
    return std::make_tuple(preamble, numbers);
}

bool is_sum_of_preamble(std::deque<ull> preamble, const ull num)
{
    std::sort(preamble.begin(), preamble.end());
    for (const auto preamble_val : preamble) {
        long long val = num - preamble_val;
        if (std::binary_search(preamble.begin(), preamble.end(), std::abs(val)))
            return true;
    }
    return false;
}

ull part_one(std::deque<ull> preamble, std::deque<ull> numbers)
{
    const auto cnt = numbers.size();
    for (size_t i = 0; i < cnt; i++) {
        if (!is_sum_of_preamble(preamble, numbers.front()))
            return numbers.front();

        preamble.pop_front();
        preamble.push_back(numbers.front());
        numbers.pop_front();
    }
    return 0;
}

ull part_two(const ull num, const std::deque<ull> &list)
{
    auto init = list.begin();
    auto end = init;

    for (auto sum = std::reduce(init, end); sum != num; sum = std::reduce(init, end)) {
        if (sum < num)
            end = std::next(end);
        else if (sum > num)
            init = std::next(init);
    }
    return *std::min_element(init, end) + *std::max_element(init, end);
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> input = read_stdin();

    std::deque<ull> list;
    std::transform(input.begin(), input.end(), std::back_inserter(list), [](const auto &s) { return std::stoull(s); });

    const int preamble_len = list.front();
    list.pop_front();
    auto [preamble, numbers] = get_preamble_and_numbers(preamble_len, list);

    ull num = part_one(preamble, numbers);

    std::cout << num << '\n';
    std::cout << part_two(num, list) << '\n';

    return 0;
}
