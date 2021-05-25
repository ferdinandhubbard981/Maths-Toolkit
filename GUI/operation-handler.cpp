

#include "dataparser.cpp"
#include "../matrix.cpp"
string DoOperation(string inputstring)
{
  string outputstring;
  string optype;
  int mat1rows, mat1cols, mat2rows, mat2cols;
  double** mat1;
  double** mat2;
  double** result;

  ParseStringTo2dArray(optype, mat1rows, mat1cols, mat2rows, mat2cols, mat1, mat2, inputstring);

  if (optype == "Mult")
  {

    result = multiplymatrices(mat1, mat2, mat1rows, mat1cols, mat2rows, mat2cols);
    printmatrix(result, 2, 2);

  }


  return outputstring;
}
