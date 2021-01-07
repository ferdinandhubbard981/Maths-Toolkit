
#include <stdexcept>
#include <cmath>
#include "arrays.cpp"
void printmatrix(double** matrix, int height, int width) {

  for (int i = 0; i < height; i++) {
    std::cout << std::endl;
    for (int j = 0; j < width; j++) {
      std::cout << matrix[i][j] << "    ";
    }
  }
  std::cout << std::endl << std::endl << std::endl;
}

double** multiplybyconstant(double** m, int height, int width, double constant) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      m[i][j] = m[i][j] * constant;
    }
  }
  return m;
}

double** multiplymatrices(double** m1, double** m2, int m1height, int m1width, int m2height, int m2width) {

  if (m1width != m2height) {
    throw std::invalid_argument("The width of the first matrix is not equal to the height of the second");
  }
  double** result = initalizedouble2dpointerarray(m1height, m2width);
  //check that m1width == m2height
  for (int i = 0; i < m1height; i++) {
    for (int j = 0; j < m2width; j++) {
      int tempsum = 0;
      for (int k = 0; k < m2height; k++) {
        tempsum += m1[i][k] * m2[k][j];
      }
      result[i][j] = tempsum;
    }
  }
  return result;
}

double** findminor(double** m, int height, int width, int i, int j) { // i and j are indexes starting at 0, 0 for top left

  // make copy so original doesn't get changed;
  double** temp = copydouble2dpointerarray(m, height, width);


  for (int x = 0; x < width; x++) {
    for (int y = j; y < height - 1; y++) {
      temp[y][x] = temp[y+1][x];
    }
  }
  for (int x = 0; x < height; x++) {
    for(int y = i; y < width - 1; y++) {
      temp[x][y] = temp[x][y+1];
    }
  }
  height -= 1;
  width -= 1;
  return temp;
}
int finddeterminant(double** m, int height, int width) {
  if (width != height) {
    throw std::invalid_argument("Cannot find determinant of a non-square matrix");
  }
  if (height == 2) {
    return m[0][0] * m[1][1] - m[0][1] * m[1][0];
  }
  int det = 0;
  for (int i = 0; i < width; i++) {
    double** minor = findminor(m, height, width, i, 0);
    det += pow(-1, i) * m[0][i] * finddeterminant(minor, height-1, width-1);
  }
  return det;
}

double** transposematrix(double** m, int height, int width) {
  double** result = initalizedouble2dpointerarray(height, width);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < i+1; j++) {
      result[j][i] = m[i][j];
      result[i][j] = m[j][i];
    }
  }
  return result;
}

double** inversematrix(double** m, int height, int width) {
  double** result = initalizedouble2dpointerarray(height, width);
  //find determinant
  int det = finddeterminant(m, height,  width);
  std::cout << "determinant = " << det << std::endl;
  if (det == 0) {
    throw std::invalid_argument("Determinant is 0, no inverse matrix");
  }
  // find matrix of cofactors
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      double** minor = findminor(m, height, width, i, j);
      std::cout << "minor " << i << ", " << j << ":" << std::endl;
      printmatrix(minor, height-1, width-1);
      result[j][i] = pow(-1, i+j) * finddeterminant(minor, height-1, width-1);
    }
  }
  //transpose matrix
  std::cout << "pretranspose: " << std::endl;
  printmatrix(result, height, width);
  result = transposematrix(result, height, width);
  double constant = (double)1 / det;
  result = multiplybyconstant(result, height, width, constant);
  return result;
}
