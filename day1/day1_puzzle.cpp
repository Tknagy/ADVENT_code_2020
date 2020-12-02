#include <iostream>
#include <vector>
#include <chrono>

int puzzle1(){
    std::vector<int> entries;
    int number = 0;
    
    while (std::cin >> number )
    {   
    
        //std :: cout <<  number << " added" << std::endl;
        entries.push_back(number);
    }

    //std::cout << entries.size() << " entries added in the input vector. " << std::endl;
  
   int num1 = 0;
   int num2 = 0;
   int sum = 0;
   int answer;
   int size = entries.size();
   for(int i= 0; i < size ; i++)
   {    
       num1=entries.at(i);
       //std::cout << entries.at(i) <<std::endl;
       for(int j= i+1; j < size ; j++)
       {    
            num2 = entries.at(j);
            sum = num1 + num2;    
            //std::cout << "combinacao " << num1 << " + " << num2 << " = " << sum << std::endl;
            if(sum == 2020)
            {
                //std::cout << "combinacao " << num1 << " + " << num2 << " = " << sum << std::endl;
                answer = num1*num2;
                //std::cout << "Resposta: " << answer << std::endl;
                return answer;
            }
       }

   }
   std::cerr << "2020 not found :(" << std::endl;
    return -1;

}
int puzzle2(){
    std::vector<int> entries;
    int number = 0;
    
    while (std::cin >> number )
    {   
        //std :: cout <<  number << " added" << std::endl;
        entries.push_back(number);
    }

    //std::cout << entries.size() << " entries added in the input vector. " << std::endl;
  
   int num1 = 0;
   int num2 = 0;
   int num3 = 0;
   int sum = 0;
   int answer;
   int size = entries.size();
   for(int i= 0; i < size ; i++)
   {    
       num1=entries.at(i);
       //std::cout << entries.at(i) <<std::endl;
       for(int j= i+1; j < size ; j++)
       {    
            num2 = entries.at(j);
            for(int k= j+1; k < size ; k++)
                {    
                    num3 = entries.at(k);
                    sum = num1 + num2 + num3;    
                    //std::cout << "combinacao " << num1 << " + " << num2 << " = " << sum << std::endl;
                    if(sum == 2020)
                    {
                        //std::cout << "combinacao " << num1 << " + " << num2 << "+" << num3 << " = " << sum << std::endl;
                        answer = num1*num2*num3;
                        //std::cout << "Resposta: " << answer << std::endl;
                        return answer;
                    }
                }
       }

   }
    std::cerr << "2020 not found :(" << std::endl;
    return -1;
}

int puzzle3(){
    std::vector<int> entries;
    int number = 0;
    
    while (std::cin >> number )
    {   
        //std :: cout <<  number << " added" << std::endl;
        entries.push_back(number);
    }

    //std::cout << entries.size() << " entries added in the input vector. " << std::endl;
  
   int num1 = 0;
   int num2 = 0;
   int num3 = 0;
   int sum = 0;
   int answer;
   int size = entries.size();
   for(int i= 0; i < size ; i++)
   {    
       num1=entries.at(i);
       //std::cout << entries.at(i) <<std::endl;
       for(int j= 0; j < size ; j++)
       {    
            num2 = entries.at(j);
            for(int k= 0; k < size ; k++)
                {    
                    num3 = entries.at(k);
                    sum = num1 + num2 + num3;    
                    //std::cout << "combinacao " << num1 << " + " << num2 << " = " << sum << std::endl;
                    if(sum == 2020)
                    {
                        //std::cout << "combinacao " << num1 << " + " << num2 << "+" << num3 << " = " << sum << std::endl;
                        answer = num1*num2*num3;
                        //std::cout << "Resposta: " << answer << std::endl;
                        return answer;
                    }
                }
       }

   }
    std::cerr << "2020 not found :(" << std::endl;
    return -1;
}

int main()
{   
    int Answer = 0;
    std::cout << "Executing Puzzle 2 " << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();
    Answer=puzzle3();
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
    std::cout << "Execution time:: " << duration << "us" << std::endl;
    std::cout << "Answer: " << Answer << std::endl;
    return 0;
}