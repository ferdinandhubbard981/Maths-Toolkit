#include "operation-handler.cpp"
#include <iostream>
int main()
{
  std::string inputstring = "Matrix DetA 2 2 0 0 0 0 2 2 0 0 0 0 1";
  std::cout << "working" << endl;
  std::cout << DoOperation(inputstring) << endl;
  return 0;
}
