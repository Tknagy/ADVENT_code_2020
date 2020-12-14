#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

#include "utils.h"

std::pair<ull, std::vector<std::string>> parse_input(const std::vector<std::string> &input)
{
    return std::make_pair(std::stoull(input[0]), split(input[1], ','));
}

ull wait_time(const ull time, const ull id) { return id - (time % id); }

ull part_one(const ull earliest_timestamp, const std::vector<std::string> &bus_ids)
{
    std::vector<ull> ids;
    for (const auto &bus : bus_ids)
        if (bus != "x")
            ids.push_back(std::stoull(bus));

    auto bus = *std::min_element(ids.begin(), ids.end(), [earliest_timestamp](const auto &a, const auto &b) {
        return wait_time(earliest_timestamp, a) < wait_time(earliest_timestamp, b);
    });
    return bus * wait_time(earliest_timestamp, bus);
}

auto part_two(const std::vector<std::string> &bus_ids)
{
    // All busses are coprimes (and even also primes) =)
    // To increase speed in finding the timestamp, we can increase the
    // step once a valid timestamp has been found for the previous busses.
    // Example, 17 and 37...
    // Once a valid timestamp has been found for 17 (0, 17, ...)
    // We can search for a valid timestamp with the step of 17.
    // Once a valid timestamp has been found for 37 with a timestep of 17
    // (also making it multiple of 17 and therefore valid for 17)
    // we can increase the timestep to 17*37, this way we guarantee that the
    // next timestamp found is valid both for 17 and 37. Also, because the
    // numbers are coprimes, we are guaranteed to not miss any value in between
    // when increasing the timestep
    ull timestamp = 0;
    ull timestep = 1;

    for (size_t i = 0; i < bus_ids.size(); i++) {
        if (bus_ids[i] == "x")
            continue;

        ull id = std::stoull(bus_ids[i]);

        while ((timestamp + i) % id != 0) {
            timestamp += timestep;
        }
        timestep *= id;
    }
    return timestamp;
}

int main(int argc, char const *argv[])
{
    auto input = read_stdin();
    auto [earliest_timestamp, bus_ids] = parse_input(input);

    std::cout << part_one(earliest_timestamp, bus_ids) << '\n';
    std::cout << part_two(bus_ids) << '\n';
    return 0;
}
