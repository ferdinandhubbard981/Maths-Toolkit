
#include "matrix.cpp"

double** getmatrixinput(int &height, int &width) {
  std::cout << "enter matrix height: ";
  std::cin >> height;
  std::cout << std::endl << "enter matrix width: ";
  std::cin >> width;
  std::cout << std::endl << "enter all values of the matrix row by row going from left to right starting from the top" << std::endl;
  double** m = initializedouble2dpointerarray(width, height);
  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      std::cout << std::endl << "enter value for index " << i << "," << j << ": ";
      std::cin >> m[i][j];
    }
  }
  return m;
}
void multiplicationtest() {
  int m1height, m1width, m2height, m2width;
  double** m1 = getmatrixinput(m1height, m1width);
  double** m2 = getmatrixinput(m2height, m2width);


  std::cout << "matrix 1:" << std::endl;
  printmatrix(m1, m1height, m1width);
  std::cout << "matrix 2:" << std::endl;
  printmatrix(m2, m2height, m2width);
  double** result = multiplymatrices(m1, m2, m1height, m1width, m2height, m2width);
  std::cout << "result: " << std::endl;
  printmatrix(result, m1height, m2width);
}
void determinanttest() {
  int height, width;
  double** matrix = getmatrixinput(height, width);
  std::cout << "matrix: " << std::endl;
  printmatrix(matrix, height, width);
  int det = finddeterminant(matrix, height, width);
  std::cout << "determinant = " << det << std::endl;
}

void minortest() {

  int height, width, i, j;
  double** matrix = getmatrixinput(height, width);
  printmatrix(matrix, height, width);
  std::cout << "please enter i: ";
  std::cin >> i;
  std::cout << std::endl << "please enter j: ";
  std::cin >> j;
  double** minor = findminor(matrix, height, width, i, j);
  printmatrix(minor, height-1, width-1);

}

void inversetest() {

  int height, width;
  double** matrix = getmatrixinput(height, width);
  std::cout << "input matrix: " << std::endl;
  printmatrix(matrix, height, width);
  double** inverse = inversematrix(matrix, height, width);
  std::cout << "inverse matrix: " << std::endl;
  printmatrix(inverse, height, width);

}

void multiplybyconstanttest() {

  int height, width;
  double constant;
  double** matrix = getmatrixinput(height, width);
  std::cout << "input matrix: " << std::endl;
  printmatrix(matrix, height, width);
  std::cout << "enter constant to multiply matrix: " << std::endl;
  std::cin >> constant;
  matrix = multiplybyconstant(matrix, height, width, constant);
  std::cout << "output matrix: " << std::endl;
  printmatrix(matrix, height, width);
}

int main() {
  std::cout << "Enter: 1 to test matrix multiplication \n 2 to test determinants \n 3 to test minors \n 4 to test inverse \n 5 to test multiplication by constant"
  int choice << std::cin;
  switch choice
  {
    case 1:
      multiplicationtest();
      break;
    case 2:
      determinanttest();
      break;
    case 3:
      minortest();
      break;
    case 4:
      inversetest();
      break;
    case 5:
      multiplybyconstanttest();
      break;
  }

}
