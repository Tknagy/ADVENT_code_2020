

#include <string>
#include <vector>

std::vector<std::string> split(const std::string &s, const char delim);

std::vector<std::string> read_stdin();
std::vector<std::string> read_stdin_ungrouped();
std::vector<std::string> read_file(const std::string &filename);
std::vector<std::string> read_file_ungrouped(const std::string &filename);

using ull = unsigned long long int;
using ll = long long int;
