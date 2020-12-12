#include <algorithm>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

#include "utils.h"

bool seat_empty(const char c) { return c == 'L'; }
bool seat_occupied(const char c) { return c == '#'; }
void occupy_seat(char &c) { c = '#'; }
void empty_seat(char &c) { c = 'L'; }

bool valid_position(const std::vector<std::string> &map, const int i, const int j)
{
    return i >= 0 && j >= 0 && i < map.size() && j < map[i].size();
}

std::vector<char> get_adjacent_seats(const std::vector<std::string> &map, const size_t i, const size_t j)
{
    std::vector<char> ret;

    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0)
                continue;

            if (valid_position(map, i + x, j + y))
                ret.push_back(map[i + x][j + y]);
        }
    }
    return ret;
}

std::vector<char> get_line_of_sight_seats(const std::vector<std::string> &map, const size_t i, const size_t j)
{
    std::vector<char> ret;

    std::vector<std::pair<int, int>> directions = {{-1, 0}, {-1, 1}, {0, 1},  {1, 1},
                                                   {1, 0},  {1, -1}, {0, -1}, {-1, -1}};

    for (const auto &dir : directions) {
        int x = i + dir.first;
        int y = j + dir.second;
        while (valid_position(map, x, y)) {
            if (map[x][y] != '.') {
                ret.push_back(map[x][y]);
                break;
            }
            x += dir.first;
            y += dir.second;
        }
    }
    return ret;
}

using GetRelevantSeatsCallback = std::vector<char> (*)(const std::vector<std::string> &, const size_t, const size_t);
char apply_rules(const std::vector<std::string> &map, const size_t i, const size_t j,
                 GetRelevantSeatsCallback get_relevant_seats, int tolerance_level)
{
    char seat = map[i][j];
    std::vector<char> adjacent_seats = get_relevant_seats(map, i, j);

    if (seat_empty(map[i][j]) && std::none_of(adjacent_seats.begin(), adjacent_seats.end(), seat_occupied))
        occupy_seat(seat);
    else if (seat_occupied(map[i][j]) &&
             std::count_if(adjacent_seats.begin(), adjacent_seats.end(), seat_occupied) >= tolerance_level)
        empty_seat(seat);

    return seat;
}

char apply_first_rules(const std::vector<std::string> &map, const size_t i, const size_t j)
{
    return apply_rules(map, i, j, get_adjacent_seats, 4);
}

char apply_second_rules(const std::vector<std::string> &map, const size_t i, const size_t j)
{
    return apply_rules(map, i, j, get_line_of_sight_seats, 5);
}

using RulesCallback = char (*)(const std::vector<std::string> &, const size_t, const size_t);
std::vector<std::string> simulate_round(const std::vector<std::string> &map, RulesCallback apply_rules)
{
    std::vector<std::string> new_map(map.begin(), map.end());
    for (size_t i = 0; i < map.size(); i++)
        for (size_t j = 0; j < map[i].size(); j++)
            new_map[i][j] = apply_rules(map, i, j);
    return new_map;
}

unsigned int run_simulation(const std::vector<std::string> &map, RulesCallback apply_rules)
{
    auto prev = map;
    auto curr = simulate_round(prev, apply_rules);
    while (prev != curr) {
        prev = curr;
        curr = simulate_round(prev, apply_rules);
    }

    std::vector<ull> occupied_seats;
    std::transform(curr.begin(), curr.end(), std::back_inserter(occupied_seats), [](const std::string &line){ return std::count_if(line.begin(), line.end(), seat_occupied); });
    return std::reduce(occupied_seats.begin(), occupied_seats.end(), 0);
}

unsigned int part_one(const std::vector<std::string> &map) { return run_simulation(map, apply_first_rules); }
unsigned int part_two(const std::vector<std::string> &map) { return run_simulation(map, apply_second_rules); }

int main(int argc, char const *argv[])
{
    auto input = read_stdin();
    std::cout << part_one(input) << '\n';
    std::cout << part_two(input) << '\n';
    return 0;
}
