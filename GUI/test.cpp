#include "operation-handler.cpp"
#include <iostream>
int main()
{
  std::string inputstring = "Simul Solve 2 3 1 1 1 -1 3 1";
  
  std::cout << DoOperation(inputstring) << endl;
  return 0;
}
