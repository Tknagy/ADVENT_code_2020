#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <utility>
#include <vector>

#include "utils.h"

constexpr ull mem_max_val = 0xFFFFFFFFF;

std::pair<ull, ull> parse_memory_instruction(const std::string &instruction)
{
    const auto start_pos = 4;
    const auto end_pos = instruction.find("] = ");
    const auto start_num = end_pos + 4;
    ull pos = std::stoull(instruction.substr(start_pos, end_pos - start_pos));
    ull num = std::stoull(instruction.substr(start_num));
    return std::make_pair(pos, num);
}

ull set_bit(const ull num, const ull bit) { return num | 1ull << bit; }

ull clear_bit(const ull num, const ull bit) { return num & ~(1ull << bit); }

bool is_bit_set(const ull num, const ull bit) { return num & (1ull << bit); }

ull apply_mask(ull num, const std::string &mask)
{
    for (size_t i = 0; i < mask.size(); i++) {
        if (mask[i] == '1') {
            num = set_bit(num, mask.size() - 1 - i);
        } else if (mask[i] == '0') {
            num = clear_bit(num, mask.size() - 1 - i);
        }
    }
    return num;
}

ull part_one(const std::vector<std::string> &instructions)
{
    std::string mask;
    std::unordered_map<ull, ull> mem;
    for (const auto &instruction : instructions) {
        if (instruction.find("mask = ") != std::string::npos) {
            mask = instruction.substr(7);
        } else if (instruction.find("mem[") != std::string::npos) {
            auto [pos, num] = parse_memory_instruction(instruction);
            mem[pos] = apply_mask(num, mask);
        } else {
            std::abort();
        }
    }

    return std::accumulate(mem.begin(), mem.end(), 0ull, [](ull val, std::pair<ull, ull> p) { return val + p.second; });
}

std::vector<ull> decode_mem_addr(const ull addr, const std::string &mask)
{
    ull dest = addr;
    std::vector<ull> x_pos;
    for (size_t i = 0; i < mask.size(); i++) {
        if (mask[i] == '1') {
            dest = set_bit(dest, mask.size() - 1 - i);
        } else if (mask[i] == 'X') {
            dest = clear_bit(dest, mask.size() - 1 - i);
            x_pos.push_back(mask.size() - 1 - i);
        }
    }

    std::vector<ull> addresses;
    for (size_t i = 0; i < (1 << x_pos.size()); i++) {
        ull num = dest;
        for (size_t pos = 0; pos < x_pos.size(); pos++)
            num = (is_bit_set(i, pos)) ? set_bit(num, x_pos[pos]) : clear_bit(num, x_pos[pos]);
        addresses.push_back(num);
    }

    return addresses;
}

ull part_two(const std::vector<std::string> &instructions)
{
    std::string mask;
    std::unordered_map<ull, ull> mem;
    for (const auto &instruction : instructions) {
        if (instruction.find("mask = ") != std::string::npos) {
            mask = instruction.substr(7);
        } else if (instruction.find("mem[") != std::string::npos) {
            auto [pos, num] = parse_memory_instruction(instruction);
            auto addresses = decode_mem_addr(pos, mask);
            for (const auto &addr : addresses)
                mem[addr] = num;
        } else {
            std::abort();
        }
    }

    return std::accumulate(mem.begin(), mem.end(), 0ull, [](ull val, std::pair<ull, ull> p) { return val + p.second; });
}

int main(int argc, char const *argv[])
{
    // The result of an arithmetic shift operation with one operand being an int in C++ is always an int.
    // source: https://stackoverflow.com/questions/24100576/bitshifting-in-c-producing-the-wrong-answer

    auto input = read_stdin();
    std::cout << part_one(input) << '\n';
    std::cout << part_two(input) << '\n';
    return 0;
}
