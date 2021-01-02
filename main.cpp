#include <iostream>
#include "simplex-method.cpp"

int main() {

  int arr = apply_simplex({{1}, {1}});
  std::cout << arr;
  return 0;
}
