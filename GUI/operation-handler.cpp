

#include "dataparser.cpp"
#include "../matrix.cpp"
#include "../simultaneous-equations-solver.cpp"
#include "../simplex-method.cpp"
using namespace std;

string DoMatrixOperation(string* inputarray, int index)
{
  bool resultismatrix = true;
  string outputstring;
  string optype;
  int matArows, matAcols, matBrows, matBcols;
  double** matA;
  double** matB;
  int* resultorder = new int[2];
  double** result;
  string constant;
  string i, j; //index of minor
  ParseStringTo2dArray(optype, matArows, matAcols, matBrows, matBcols, matA, matB, inputarray, index, constant, i, j);

  if (optype == "Add")
  {

    result = addmatrices(matA, matB, matArows, matAcols, matBrows, matBcols);
    resultorder[0] = matArows;
    resultorder[1] = matAcols;

  }

  if (optype == "Sub")
  {

    matB =  multiplybyconstant(matB, matBrows, matBcols, -1);
    result = addmatrices(matA, matB, matArows, matAcols, matBrows, matBcols);
    resultorder[0] = matArows;
    resultorder[1] = matAcols;

  }

  if (optype == "Mult")
  {

    result = multiplymatrices(matA, matB, matArows, matAcols, matBrows, matBcols);
    resultorder[0] = matArows;
    resultorder[1] = matBcols;
    //printmatrix(result, 2, 2);

  }

  if (optype == "DetA")
  {
    outputstring = "Det: " + to_string(finddeterminant(matA, matArows, matAcols));
    resultismatrix = false;
  }

  if (optype == "DetB")
  {
    outputstring = "Det: " + to_string(finddeterminant(matB, matBrows, matBcols));
    resultismatrix = false;
  }

  if (optype == "InvA")
  {
    result = inversematrix(matA, matArows, matAcols);
    resultorder[0] = matArows;
    resultorder[1] = matAcols;
  }

  if (optype == "InvB")
  {
    result = inversematrix(matB, matBrows, matBcols);
    resultorder[0] = matBrows;
    resultorder[1] = matBcols;
  }

  if (optype == "SquareA")
  {
    result = multiplymatrices(matA, matA, matArows, matAcols, matArows, matAcols);
    resultorder[0] = matArows;
    resultorder[1] = matAcols;
  }

  if (optype == "SquareB")
  {
    result = multiplymatrices(matB, matB, matBrows, matBcols, matBrows, matBcols);
    resultorder[0] = matBrows;
    resultorder[1] = matBcols;
  }

  if (optype == "TransA")
  {
    result = transposematrix(matA, matArows, matAcols);
    resultorder[0] = matArows;
    resultorder[1] = matAcols;
  }

  if (optype == "TransB")
  {
    result = transposematrix(matB, matBrows, matBcols);
    resultorder[0] = matBrows;
    resultorder[1] = matBcols;
  }

  if (optype == "MinA")
  {
    if (!IsInteger(i))
    {
      throw invalid_argument("minor index i must be an integer");
    }

    if (!IsInteger(j))
    {
      throw invalid_argument("minor index j must be an integer");
    }

    result = findminor(matA, matArows, matAcols, stoi(i), stoi(j));
    resultorder[0] = matArows - 1;
    resultorder[1] = matAcols - 1;
  }

  if (optype == "MinB")
  {

    if (!IsInteger(i))
    {
      throw invalid_argument("minor index i must be an integer");
    }

    if (!IsInteger(j))
    {
      throw invalid_argument("minor index j must be an integer");
    }

    result = findminor(matB, matBrows, matBcols, stoi(i), stoi(j));
    resultorder[0] = matBrows - 1;
    resultorder[1] = matBcols - 1;
  }

  if (optype == "MultconstA")
  {
    if (!IsDouble(constant))
    {
      throw invalid_argument("constant must be a real number");
    }
    result = multiplybyconstant(matA, matArows, matAcols, stod(constant));
    resultorder[0] = matArows;
    resultorder[1] = matAcols;
  }

  if (optype == "MultconstB")
  {
    if (!IsDouble(constant))
    {
      throw invalid_argument("constant must be a real number");
    }
    result = multiplybyconstant(matB, matBrows, matBcols, stod(constant));
    resultorder[0] = matBrows;
    resultorder[1] = matBcols;
  }

  if (resultismatrix)
  {
    outputstring = ConvertMatToString(result, resultorder);
  }
  //cout << outputstring;
  return outputstring;
}


string DoSimul(string* array, int index)
{
  string alphabet[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
  double* result;
  double** coefficients;
  int numOfVariables;
  string optype;
  int width, height;

  parseSimulString(optype, coefficients, width, height, array, index);
  //cout << "width: " << width << endl << "height: " << height << endl;
  if (width != height + 1)
  {
    throw invalid_argument("number of equations must be equal to number of variables");
  }
  numOfVariables = height;
  if (numOfVariables > 24) {
    throw invalid_argument("too many variables entered");
  }
  result = SimulSolve(coefficients, numOfVariables);
  string* variables = SliceAlphabet(alphabet, numOfVariables);
  return printresults(variables, result, numOfVariables);
}

string DoSimplex(string* array, int index)
{
  stringstream buffer;
  string* varnames;
  double** result;
  double** tableau;
  int numOfVar, numOfConstraints, numOfSlackVar, numOfArtificialVar, startingRowIndex;
  string opType;
  parseTableau(tableau, numOfVar, numOfConstraints, numOfSlackVar, numOfArtificialVar, startingRowIndex, opType, varnames, array, index);
  cout << "numOfVar: " << numOfVar << endl << "nconstraints: " << numOfConstraints << endl << "numOfSlackVar: " << numOfSlackVar << endl << "numOfArtificialVar: " << numOfArtificialVar << endl << "starting row index: " << startingRowIndex << endl;
  int width =  numOfVar + numOfSlackVar + numOfArtificialVar + 1 + startingRowIndex;
  int height = numOfConstraints + startingRowIndex;
  printtableau(tableau, width, height);
  result = apply_simplex(tableau, numOfVar, numOfConstraints, numOfSlackVar, numOfArtificialVar, startingRowIndex, varnames, buffer);
  return buffer.str();


}
string DoOperation(string inputstring)
{
  int index = 0;
  string* array = split(inputstring, ' ');
  string opsource = array[index];
  index++;

  if (opsource == "Matrix")
  {
    return DoMatrixOperation(array, index);
  }

  if (opsource == "Simul")
  {
    return DoSimul(array, index);

  }

  else if (opsource == "Simplex")
  {
    return DoSimplex(array, index);
  }

}
