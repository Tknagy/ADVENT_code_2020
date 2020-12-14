#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

void invertInstruction(
    std::pair<std::string, std::pair<int, int> > *instruction)
{
  if (instruction->first == "jmp")
  {
    //std::cout << "Inverted jmp to nop. " << std::endl;
    instruction->first = "nop";
  }

  else if (instruction->first == "nop")
  {
    //std::cout << "Inverted nop to jmp. " << std::endl;
    instruction->first = "jmp";
  }
}

void resetInstructionCounter(
    std::vector<std::pair<std::string, std::pair<int, int> > > *instructions)
{
  for (auto i = instructions->begin(); i < instructions->end();i++) i->second.second = 0;
}




bool puzzle(
    std::vector<std::pair<std::string, std::pair<int, int> > > *instructions)
{
  int it = 0; // it as position of vector instead of iterator to check if inside
              // boundaries
  int positionLastInstruction = 0;
  int acc = 0 ;
  while (it < instructions->size() && it >= 0 &&
         instructions->at(it).second.second < 1)
  {

    instructions->at(it).second.second++; // increase the "accessed" counter
                                          // from instruction vector
    // std::cout << "Instruction " << instructions->at(it)->first << " param "
    // << instructions->at(it)->second.first
    //          << " accessed " << instructions->at(it)->second.second << "
    //          times." << std::endl;
    if (instructions->at(it).first == "nop")
    {
      // do nothing
      it++;
    }
    else if (instructions->at(it).first == "acc")
    {
      acc += instructions->at(it).second.first;
      it++;
    }
    else if (instructions->at(it).first == "jmp")
    {
      it += instructions->at(it).second.first;
    }
    else
      std::cerr << "Instruction is outside specified values [nop.acc,jmp]"
                << std::endl;
    
  }
  if (it == instructions->size()) // if program ended
  {
    std::cout << "Program terminated with acc:" << acc << std::endl;

    return 1;
  }
  if (instructions->at(it).second.second >= 1)
  {
    std::cout << "Program looped on position " << it << " with acc: " << acc << std::endl;
  }
  resetInstructionCounter(instructions);
  return 0;
}

int main(int argc, char *argv[])
{
  std::string fileName = argv[1];
  std::vector<std::pair<std::string, std::pair<int, int> > > instructions;
  std::string inputLine;
  std::ifstream entries;
  std::regex instruction_regex("([A-z]+)\\s(\\-?\\+?\\d+)",
                               std::regex_constants::ECMAScript |
                                   std::regex_constants::icase);
  std::smatch myRegexMatch;
  // Step 1: populate inputLuggages with all luggages from input file
  entries.open(fileName);
  if (!entries.is_open())
  {
    std::cerr << "File can not be open \n";
    return -1;
  }
  while (std::getline(entries, inputLine))
  {
    if (!inputLine.empty())
    {
      if (std::regex_search(inputLine, myRegexMatch, instruction_regex))
      {
        std::string inputInstruction = myRegexMatch.str(1);
        int inputInstructionParameter = stoi(myRegexMatch.str(2));
        instructions.push_back(std::make_pair(
            inputInstruction, std::make_pair(inputInstructionParameter, 0)));
      }
    }
    else
      std::cerr << "Input line is empty, cannot read Luggage information."
                << std::endl;
  }
  entries.close();

  std::cout << "Puzzle 1 : " <<  std::endl;
  puzzle(&instructions);

  std::cout << "\nPuzzle 2 : " <<  std::endl;
  size_t flippedInstructionPosition = 0;

  for (flippedInstructionPosition = 0;
       flippedInstructionPosition < instructions.size();
       flippedInstructionPosition++)
  {
   // std::cout << "Flipped pos: " << flippedInstructionPosition << std::endl;
    

    // invert jmp-nops
     invertInstruction(&instructions.at(flippedInstructionPosition));
    // if the invert solve puzzle break from while
    resetInstructionCounter(&instructions);
    if (puzzle(&instructions))
      break;
    // if not then re-invert and go to next instruction
    else
    {
       invertInstruction(&instructions.at(flippedInstructionPosition));
    }
  }

  return 0;
}