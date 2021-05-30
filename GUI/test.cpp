#include "operation-handler.cpp"
#include <iostream>
using namespace std;
int main()
{
  string inputstring = "Simplex Solve 2 2 0 3 6 1 0 0 -1 1 0 -1 0 1 0 1 0 0 0 1 0 5 2";

  cout << DoOperation(inputstring) << endl;
  return 0;
}
