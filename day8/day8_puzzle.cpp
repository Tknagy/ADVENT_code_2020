#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char *argv[]) {
  std::string fileName = argv[1];
  std::vector<std::pair<std::string, std::pair<int,int>>> instructions;
	int acc{0};
  std::string inputLine;
	std::ifstream entries;
  std::regex instruction_regex("([A-z]+)\\s(\\-?\\+?\\d+)",
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
      if (std::regex_search(inputLine, myRegexMatch, instruction_regex)) {
      std::string inputInstruction = myRegexMatch.str(1);
			int inputInstructionParameter = stoi(myRegexMatch.str(2));
			instructions.push_back(std::make_pair(inputInstruction, std::make_pair(inputInstructionParameter,0)));
      }
    } else
      std::cerr << "Input line is empty, cannot read Luggage information."
                << std::endl;
  }
  entries.close();
	std::vector<std::pair<std::string, std::pair<int,int>>>::iterator it = instructions.begin();
	while(it->second.second < 1 )
	{
		it->second.second++; //increase the "accessed" counter from instruction vector
		std::cout << "Instruction " << it->first << " param " << it->second.first << " accessed " << it->second.second << " times." << std::endl;
		if(it->first == "nop")
		{
			//do nothing
			it++;
		}
		else if (it->first == "acc")
		{
			acc += it->second.first;
			it++;
		}
		else if (it->first == "jmp")
		{
			it += it->second.first;
		}
		else std::cerr << "Instruction is outside specified values [nop.acc,jmp]" << std::endl;
		
	}

	std::cout << "Accumulator: " << acc << std::endl;


	

  return 0;
}