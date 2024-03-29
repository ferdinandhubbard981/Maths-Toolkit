//#include <iostream>
#include <stdexcept>
#include <cmath>
//#include "arrays.cpp"
using namespace std;
void printmatrix(double** matrix, int height, int width) {

  for (int j = 0; j < height; j++) {
    cout << endl;
    for (int i = 0; i < width; i++) {
      cout << matrix[i][j] << "    ";
    }
  }
  cout << endl << endl << endl;
}

double** addmatrices(double** m1, double** m2, int m1rows, int m1cols, int m2rows, int m2cols)
{
  if (m1rows != m2rows || m1cols != m2cols)
  {
    throw invalid_argument("MatrixAOrder != MatrixBOrder. Therefore matrix addition/subtraction for A and B is not defined");
  }
  double** result = initializedouble2dpointerarray(m1rows, m1cols);
  for (int i = 0; i < m1cols; i++)
  {
    for (int j = 0; j < m1rows; j++)
    {
      result[i][j] = m1[i][j] + m2[i][j];
    }
  }

  return result;
}

double** multiplybyconstant(double** m, int height, int width, double constant) {
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      m[i][j] = m[i][j] * constant;
    }
  }
  return m;
}

double** multiplymatrices(double** m1, double** m2, int m1height, int m1width, int m2height, int m2width) {

  if (m1width != m2height) {
    throw invalid_argument("MatrixA width != MatrixB height. Therefore matrix multiplication for A and B is not defined");
  }
  double** result = initializedouble2dpointerarray(m2width, m1height);
  //check that m1width == m2height
  for (int j = 0; j < m1height; j++) {
    for (int i = 0; i < m2width; i++) {
      double resultsum = 0;
      for (int k = 0; k < m2height; k++) {
        resultsum += m1[k][j] * m2[i][k];
      }
      result[i][j] = resultsum;
    }
  }
  return result;
}

double** findminor(double** m, int height, int width, int i, int j) { // i and j are indexes starting at 0, 0 for top left

  // make copy so original doesn't get changed;
  if (i >= width || j >= height)
  {
    throw invalid_argument("The indexes of i and/or j are out of the range of the matrix");
  }
  if (width != height) {
    throw invalid_argument("non-square matrix does not have a minor");
  }

  if (height == 1) {
    throw invalid_argument("matrix with order 1x1 does not have a minor");
  }

  double** result = copydouble2dpointerarray(m, width, height);

  // delete row
  for (int x = 0; x < width; x++) {
    for (int y = j; y < height - 1; y++) {
      result[x][y] = result[x][y+1];
    }
  }
  // delete column
  for (int y = 0; y < height; y++) {
    for(int x = i; x < width - 1; x++) {
      result[x][y] = result[x+1][y];
    }
  }
  height -= 1;
  width -= 1;
  return result;
}
double finddeterminant(double** m, int height, int width) {
  if (width != height) {
    throw invalid_argument("non-square matrix does not have a determinant");
  }
  if (height == 2) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
  }
  if (height == 1) {
    return m[0][0];
  }
  double det = 0;
  for (int i = 0; i < width; i++) {
    double** minor = findminor(m, height, width, i, 0);
    det += pow(-1, i) * m[i][0] * finddeterminant(minor, height-1, width-1);
  }
  return det;
}

double** transposematrix(double** m, int height, int width) {
  if (width != height) {
    throw invalid_argument("non-square matrix cannot be transposed");
  }
  double** result = initializedouble2dpointerarray(width, height);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < i+1; j++) {
      result[j][i] = m[i][j];
      result[i][j] = m[j][i];
    }
  }
  return result;
}

double** matrixofcofactors(double** m, int height, int width)
{
  double** result = initializedouble2dpointerarray(width, height);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      double** minor = findminor(m, height, width, i, j);
      //cout << "minor " << i << ", " << j << ":" << endl;
      //printmatrix(minor, height-1, width-1);
      result[i][j] = pow(-1, i+j) * finddeterminant(minor, height-1, width-1);
    }
  }
  return result;
}

double** inversematrix(double** m, int height, int width) {
  if (width != height) {
    throw invalid_argument("non-square matrix has no inverse");
  }
  double** result = initializedouble2dpointerarray(width, height);
  //find determinant
  double det = finddeterminant(m, height,  width);
  double constant = (double)1 / det;
  //cout << "determinant = " << det << endl;
  if (det == 0) {
    throw invalid_argument("matrix with determinant = 0 does not have an inverse");
  }
  if (height == 1) {
    result[0][0] = 1/m[0][0];
    return result;
  }
  /*if (height == 2) {
    result[0][0] = m[1][1];
    result[1][1] = m[0][0];
    result[0][1] = m[0][1] * -1;
    result[1][0] = m[1][0] * -1;
    result = multiplybyconstant(result, 2, 2, constant);
    return result;
  }*/
  // find matrix of cofactors
  /*
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      double** minor = findminor(m, height, width, i, j);
      //cout << "minor " << i << ", " << j << ":" << endl;
      //printmatrix(minor, height-1, width-1);
      result[i][j] = pow(-1, i+j) * finddeterminant(minor, height-1, width-1);
    }
  }
  */
  result = matrixofcofactors(m, height, width);
  //transpose matrix
  //cout << "pretranspose: " << endl;
  //printmatrix(result, height, width);
  result = transposematrix(result, height, width);
  result = multiplybyconstant(result, height, width, constant);
  //printmatrix(result, height, width);
  return result;
}
