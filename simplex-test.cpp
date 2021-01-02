#include <iostream>
#include "simplex-method.cpp"

void onestage() {
  float tableau[7][4] = {{1, 0, 0, 0}, {-1, 1, 2, 3}, {-0.8, 1, 1, 2}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}, {0, 1000, 1500, 2400}};
  float** pointertableau = new float*[7];
  for (int i = 0; i < 7; i++) {
    pointertableau[i] = new float[4];
    for (int j = 0; j < 4; j++) {
      pointertableau[i][j] = tableau[i][j];
    }
  }

  std::string varnamestemp[6] = {"P", "X", "y", "s1", "s2", "s3"};
  std::string* varnames = new std::string[6];
  varnames = varnamestemp;
  pointertableau = apply_simplex(pointertableau, 5, 3, 0, 1, varnames);
}

void twostage() {
  float tableau[12][6] = {{1, 0, 0, 0, 0, 0}, {0, 1, 0, 0, 0, 0}, {2, -2, 1, 0, 0, 2}, {0, -3, 1, 2, 0, 0}, {2, -1, 1, 1, 1, 1}, {0, 0, 1, 0, 0, 0}, {0, 0, 0, 1, 0, 0}, {-1, 0, 0, 0, -1, 0}, {-1, 0, 0, 0, 0, -1}, {0, 0, 0, 0, 1, 0}, {0, 0, 0, 0, 0, 1}, {19, 0, 20, 22, 4, 15}};
  float** pointertableau = new float*[12];
  for (int i = 0; i <  12; i++) {
    pointertableau[i] = new float[6];
    for (int j = 0; j < 6; j++) {
      pointertableau[i][j] = tableau[i][j];
    }
  }

  std::string varnamestemp[8] = {"P", "X", "y", "Z", "s1", "s2", "s3", "s4"};
  std::string* varnames = new std::string[8];
  varnames = varnamestemp;
  pointertableau = apply_simplex(pointertableau, 10, 4, 2, 2, varnames);
}

int main() {
  //onestage();
  twostage();

  return 0;
}
