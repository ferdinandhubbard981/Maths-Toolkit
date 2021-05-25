#include "operation-handler.cpp"
#include <iostream>
int main()
{
  std::string inputstring = "Mult 2 2 0 0 0 0 2 2 0 0 0 0";
  std::cout << DoOperation(inputstring);
  return 0;
}
