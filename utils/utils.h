
#include <algorithm>
#include <cassert>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

std::vector<std::string> split(const std::string &s, const char delim);

std::vector<std::string> read_stdin();
std::vector<std::string> read_stdin_ungrouped();
std::vector<std::string> read_file(const std::string &filename);
std::vector<std::string> read_file_ungrouped(const std::string &filename);

using ull = unsigned long long int;
using ll = long long int;
