#include <iostream>
#include <string>
#include <vector>

static std::vector<std::string> read_stdin()
{
    std::vector<std::string> input;
    std::string line;
    while (std::getline(std::cin, line))
        input.push_back(line);
    return input;
}

unsigned long int part_one(const std::vector<std::string> &map, int slope_x = 3, int slope_y = 1)
{
    unsigned int x(0), y(0), cnt(0), width(map[0].length()), height(map.size());
    bool finished = false;

    while (!finished) {
        if (map[y][x] == '#')
            cnt++;

        x = (x + slope_x) % width;
        y = (y + slope_y);
        if (y > height)
            finished = true;
    }
    return cnt;
}

unsigned long int part_two(const std::vector<std::string> &map)
{
    return part_one(map, 1, 1) * part_one(map, 3, 1) * part_one(map, 5, 1) * part_one(map, 7, 1) * part_one(map, 1, 2);
}

int main(int argc, char const *argv[])
{
    std::vector<std::string> input = read_stdin();
    std::cout << part_one(input) << '\n';
    std::cout << part_two(input) << '\n';
    return 0;
}
