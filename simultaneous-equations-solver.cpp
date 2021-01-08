#include "matrix.cpp"

void printtable(std::string* varnames, double** coefficients, int numofvar) {
  std::cout << std::endl << "simultaneous equations: " << std::endl << std::endl;
  for (int j = 0; j < numofvar; j++) {
    for (int i = 0; i < numofvar; i++) {
      std::string sign = "+";
      if (numofvar - i == 1) {
        std::cout << coefficients[i][j] << varnames[i] << " = " << coefficients[i+1][j] << std::endl;
      }
      else
      {
        std::cout << coefficients[i][j] << varnames[i] << " " << sign << " ";
      }

    }
  }

}

void printresults(std::string* varnames, double* results, int numofvar) {

  for (int i = 0; i < numofvar; i++) {
    std::cout <<varnames[i] << " = " << results[i] << std::endl;
  }
}


double* solve(double** coefficients, int numofvariables) { //equations in coefficient form line by line, where there is no coefficient the entry is 0
  //the right most coefficient is the RHS (right hand side of the equation) value and all other values are the coefficients of the variables in order on the left hand side of the equation

  //create square matrix from variables (nom of variables = num of equations) and matrix of order (numofvar x 1) from the RHS

  double** rhs = initializedouble2dpointerarray(1, numofvariables);
  for (int j = 0; j < numofvariables; j++) {
    rhs[0][j] = coefficients[numofvariables][j];
  }
  double** inverse = inversematrix(coefficients, numofvariables, numofvariables);

  //std::cout << "rhs val" << std::endl;
  //printmatrix(rhs, numofvariables, 1);
  //std::cout << "inverse val" << std::endl;
  //printmatrix(inverse, numofvariables, numofvariables);
  //std::cout << "inverse 1, 0 = " << inverse[1][0] << std::endl;
  double** results = multiplymatrices(inverse, rhs, numofvariables, numofvariables, numofvariables, 1); // yields an order (numofvar x 1) matrix
  //std::cout << "result multiplication: " << std::endl;
  //printmatrix(results, numofvariables, 1);

  return results[0];

}
