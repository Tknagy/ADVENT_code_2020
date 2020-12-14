#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>

bool xmas_puzzle2(int positionOfNonCompliantNumber, std::vector<long long int> *numbers)
{
	for(size_t it2 = 0; it2 < positionOfNonCompliantNumber ; it2++)
	{
		for(size_t it3 = it2+1; it3 < positionOfNonCompliantNumber ; it3++)
		{	
			long long int sum = 0;
			for(int i = it2 ; i <= it3 ; i++)
			{
				sum += numbers->at(i);
			}
			//std::cout << "sum from " << it2 << " to " << it3 << ": " << sum << std::endl;
			if(numbers->at(positionOfNonCompliantNumber)==sum) 
			{
				std::cout << numbers->at(positionOfNonCompliantNumber) <<
				" is equal to the sum from pos " << it2 << " to " << it3  << std::endl;
				auto it2_2 = numbers->begin() + it2;
				auto it3_2 = numbers->begin() + it3;
				const auto [min, max] = std::minmax_element(it2_2, it3_2);
				std::cout << "min = " << *min << ", max = " << *max << ", sum: " << (*min+*max) <<'\n';

				return true;
			}
			
		}
	}
return false;
}

bool xmas(int preamble_size, std::vector<long long int> *numbers)
{
	
    for(size_t it = preamble_size; it < numbers->size(); it++)
    {
			bool xmasCompliant = false;
			for(size_t it2 = it-preamble_size; it2 < it ; it2++)
			{
				for(size_t it3 = it2+1; it3 < it ; it3++)
				{	
					//std::cout << it2 << "+" << it3 << ": " << (it2+it3) << std::endl;
					if(numbers->at(it) == numbers->at(it2) + numbers->at(it3) )
					{
						// std::cout << numbers->at(it) << " on pos " << it 
						// <<" equal to " << numbers->at(it2) << "on pos " << it2
						// << " + " << numbers->at(it3) << "on pos " << it3
						// << std::endl;
						xmasCompliant = true;
					}
				}
			}
			if(!xmasCompliant)
			{
				std::cout << numbers->at(it) << " on pos " << it  << " is not XMAS compliant"<< std::endl;
				xmas_puzzle2(it, numbers);
				return false;
			} 
				//std::cout << "it = " << it << std::endl;

    }
return true;
}

int main(int argc, char *argv[])
{
  std::string fileName = argv[1];
  std::vector<long long int> numbers;
  std::string inputLine;
  std::ifstream entries;
  
  
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
        numbers.push_back(stoll(inputLine));
    }
    else
      std::cerr << "Input line is empty, cannot read number."
                << std::endl;
  }
  entries.close();

	xmas(25,&numbers);
  
  return 0;
}