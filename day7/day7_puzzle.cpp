#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

// Reverse Baggage Search uses the given relevantLuggage set (filled in the
// funcion call with the the luggage to perform the search) and repeats itself n
// times until all the possible luggages that may contain the first luggage are
// inserted into the relevant luggages set.
void reverseBaggageSearch(
    std::set<std::string> *relevantLuggages,
    std::map<std::string, std::vector<std::pair<std::string, int>>>
        *inputLuggages) {
  for (auto relevantLuggage : *relevantLuggages) {
    for (auto l : *inputLuggages) {
      for (auto l2 : l.second) {
        if (l2.first == relevantLuggage) {
          // add baggage to list if not there already
          if (relevantLuggages->find(l.first) == relevantLuggages->end()) {
            relevantLuggages->insert(l.first);
            reverseBaggageSearch(relevantLuggages, inputLuggages);
          }
        }
      }
    }
  }
}
//given a luggage color, calculates the number of internal luggages that can fit into it
//This function call itself recursively until all relevant luggages are conted into the return value
int calculateNumberOfBagsInside(
    std::string luggageColor,
    std::map<std::string, std::vector<std::pair<std::string, int>>>
        *inputLuggages) {
  int numerOfBaggsInside = 1;
  if (inputLuggages->find(luggageColor) != inputLuggages->end()) {
    for (auto v : inputLuggages->find(luggageColor)->second) {
      numerOfBaggsInside +=
          v.second * calculateNumberOfBagsInside(v.first, inputLuggages);
    }
  }

  return numerOfBaggsInside;
}

int main(int argc, char *argv[]) {
  std::string fileName = argv[1];
  std::string baggageToSearch;
  if (argc > 2)
    baggageToSearch = argv[2];
  else
    baggageToSearch = "shiny gold";
  std::ifstream entries;
  std::string inputLine;
  std::map<std::string, std::vector<std::pair<std::string, int>>> inputLuggages;
  std::regex bag_contain_regex("([A-z]+?\\s[A-z]+)\\sbags\\scontain",
                               std::regex_constants::ECMAScript |
                                   std::regex_constants::icase);
  std::regex contained_bag_regex("(\\d)\\s([A-z]+\\s[A-z]+)\\sbags?,?\\.?",
                                 std::regex_constants::ECMAScript |
                                     std::regex_constants::icase);
  std::smatch myRegexMatch;
  // Step 1: populate inputLuggages with all luggages from input file
  entries.open(fileName);
  if (!entries.is_open()) {
    std::cerr << "File can not be open \n";
    return -1;
  }
  while (std::getline(entries, inputLine)) {
    if (!inputLine.empty()) {
      if (std::regex_search(inputLine, myRegexMatch, bag_contain_regex)) {
        std::string inputLuggage = myRegexMatch.str(1);
        std::vector<std::pair<std::string, int>> luggagesInside;
        // std::cout << "Found luggage: " << inputLuggage << std::endl;
        for (std::sregex_iterator i = std::sregex_iterator(
                 inputLine.begin(), inputLine.end(), contained_bag_regex);
             i != std::sregex_iterator(); ++i) {
          std::smatch match = *i;
          int auxInputLuggageAmount = stoi(match.str(1));
          std::string auxInputLuggage = match.str(2);
          luggagesInside.push_back(
              make_pair(auxInputLuggage, auxInputLuggageAmount));
          // std::cout << ", with " << auxInputLuggageAmount << " " <<
          // auxInputLuggage<< " inside" << std::endl;
        }
        inputLuggages.insert(make_pair(inputLuggage, luggagesInside));
      }
    } else
      std::cerr << "Input line is empty, cannot read Luggage information."
                << std::endl;
  }
  entries.close();

  std::set<std::string> relevantLuggages;

  relevantLuggages.insert(baggageToSearch);
  reverseBaggageSearch(&relevantLuggages, &inputLuggages);
  std::cout << "Result puzzle 1: " << relevantLuggages.size() - 1 << std::endl;

  std::cout << "Result puzzle 2: "
            << calculateNumberOfBagsInside(baggageToSearch, &inputLuggages) - 1
            << std::endl;

  return 0;
}