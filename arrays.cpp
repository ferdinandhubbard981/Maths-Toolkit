
double** initializedouble2dpointerarray(int numarrays, int numelements) {
  double** arr = new double*[numarrays];
  for (int i = 0; i < numarrays; i++) {
    arr[i] = new double[numelements];
  }

  return arr;
}

double** copydouble2dpointerarray(double** m, int numarrays, int numelements) {
  double** temp = initializedouble2dpointerarray(numarrays, numelements);
  for(int x = 0; x < numarrays; x++) {
    for (int y = 0; y < numelements; y++) {
      temp[x][y] = m[x][y];
    }
  }
  return temp;
}

int** initializeint2dpointerarray(int numarrays, int numelements) {
  int** arr = new int*[numarrays];
  for (int i = 0; i < numarrays; i++) {
    arr[i] = new int[numelements];
  }

  return arr;
}
