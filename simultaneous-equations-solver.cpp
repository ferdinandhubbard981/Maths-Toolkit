//#include "matrix.cpp"
using namespace std;
string printtable(string* varnames, double** coefficients, int numofvar) {
  stringstream buffer;
  cout << endl << "simultaneous equations: " << endl << endl;
  for (int j = 0; j < numofvar; j++) {
    for (int i = 0; i < numofvar; i++) {
      string sign = "+";
      if (numofvar - i == 1) {
        buffer << coefficients[i][j] << varnames[i] << " = " << coefficients[i+1][j] << endl;
      }
      else
      {
        buffer << coefficients[i][j] << varnames[i] << " " << sign << " ";
      }

    }
  }
  return buffer.str();
}

string printresults(string* varnames, double* results, int numofvar) {

  stringstream buffer;
  buffer << endl;
  for (int i = 0; i < numofvar; i++) {
    buffer << varnames[i] << " = " << results[i] << endl;
  }
  return buffer.str();
}


double* SimulSolve(double** coefficients, int numofvariables) { //equations in coefficient form line by line, where there is no coefficient the entry is 0
  //the right most coefficient is the RHS (right hand side of the equation) value and all other values are the coefficients of the variables in order on the left hand side of the equation

  //create square matrix from variables (nom of variables = num of equations) and matrix of order (numofvar x 1) from the RHS

  double** rhs = initializedouble2dpointerarray(1, numofvariables);
  double** inverse;
  for (int j = 0; j < numofvariables; j++) {
    rhs[0][j] = coefficients[numofvariables][j];
  }
  try
  {
    inverse = inversematrix(coefficients, numofvariables, numofvariables);

  }
  catch (invalid_argument &exc)
  {
    throw invalid_argument("this system of simultaneous equations does not have a unique solution");
  }

  //cout << "rhs val" << endl;
  //printmatrix(rhs, numofvariables, 1);
  //cout << "inverse val" << endl;
  //printmatrix(inverse, numofvariables, numofvariables);
  //cout << "inverse 1, 0 = " << inverse[1][0] << endl;
  double** results = multiplymatrices(inverse, rhs, numofvariables, numofvariables, numofvariables, 1); // yields an order (numofvar x 1) matrix
  //cout << "result multiplication: " << endl;
  //printmatrix(results, numofvariables, 1);

  return results[0];

}
