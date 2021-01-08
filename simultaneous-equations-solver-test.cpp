#include "simultaneous-equations-solver.cpp"
#include <iostream>




void testsolver() {

  int numofvar;
  std::cout << "Input the number of variables that you have. Note that the number of variables should be equal to the number of equations (not including the rhs value): ";
  std::cin >> numofvar;
  std::cout << std::endl << "Enter in order the coefficients of the variables in each equation and treat the rhs value as a coefficient that you will add last" << std::endl;
  double** coefficients = initializedouble2dpointerarray(numofvar+1, numofvar);
  //get coefficients
  for (int j = 0; j < numofvar; j++) {
    for (int i = 0; i < numofvar + 1; i++) {
      std::cout << "Enter the coefficient number " << i+1 << " for the equation number " << j+1 << ": ";
      std::cin >> coefficients[i][j];
    }
  }

  //get var varnames
  std::string* varnames= new std::string[numofvar];
  std::cout << "Enter the names of each variable" << std::endl;
  for (int i = 0; i < numofvar; i++) {
    std::cout << std::endl << "variable number " << i+1 << ": ";
    std::cin >> varnames[i];
  }
  printtable(varnames, coefficients, numofvar);
  double* results = solve(coefficients, numofvar);
  std::cout << std::endl << std::endl;
  printresults(varnames, results, numofvar);

}




int main() {
  testsolver();


}
