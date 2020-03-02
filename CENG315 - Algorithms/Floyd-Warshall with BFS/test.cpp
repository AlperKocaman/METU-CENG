#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <cassert>
#include "the3.h"


void printVector(std::vector<int>& array){

    std::cout << "size: " << array.size() << std::endl;
    for (unsigned i = 0; i < array.size(); ++i){
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}


int Important(int n, int**& edgeList, double*& scores);

bool TestTask()
{
    
    // time variables
  clock_t begin;
  clock_t end;
  double duration;
  int expectedTime = 500;
  int true_answer = 2;
  int solution = -1;
    
    // generate solution
  if ((begin = clock ()) == -1) 
      std::cerr << "clock err" << std::endl;
      
  //solution =Important(n, edgeList, scores);


  if ((end = clock ()) == -1) 
      std::cerr << "clock err" << std::endl;
      
  duration = ((double)end-begin) / CLOCKS_PER_SEC * 1000000;
  
  cout << "Elapsed time  " << duration << " vs " << expectedTime << " microsecs" << std::endl;

  return (solution == true_answer);
}





int main()
{
    srandom(time(0));       // no need to initialize second time

  if (TestTask())
    std::cout << "PASSED TASK" << std::endl << std::endl;
  else
    std::cout << "FAILED TASK" << std::endl << std::endl;
  

  return 0;
}