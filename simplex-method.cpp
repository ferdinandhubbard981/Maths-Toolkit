
void printsolution(std::string* varnames, float* solutions, int width) {

  for (int i = 0; i < width - 1; i++) {
    std::cout <<varnames[i] << " = " << solutions[i] << std::endl;
  }
}
float* read_simplex(float** tableau, int width, int height) {
  float* solutions = new float[width - 1];
  int test = 0;
  for(int i = 0; i < width - 1; i++) {
    bool foundnonzeroval = false;
    bool nonbasic = false;
    int basicvalindex;
    for (int j = 0; j < height; j++) {
      if (tableau[i][j] != 0) {
        if (tableau[i][j] == 1 && foundnonzeroval == false) {
          foundnonzeroval = true;
          basicvalindex = j;
        }
        else {
          solutions[i] = 0;
          nonbasic = true;
          break;
        }

      }
    }
    if (nonbasic == false)
      solutions[i] = tableau[width - 1][basicvalindex];
    }

  return solutions;
}
void printtableau(float** tableau, int width, int height) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      std::cout << tableau[j][i] << "              ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl << std::endl << std::endl;
}

int get_pivot_column(float** tableau, int width, bool maximise) {
  int val = 0;
  int valindex = -1;
  for (int i = 1; i < width - 1; i++) {
    if (tableau[i][0] < val && maximise  == true) {
      val = tableau[i][0];
      valindex = i;
    }

    if (tableau[i][0] > val && maximise == false) {
      val = tableau[i][0];
      valindex = i;
    }
  }
  return valindex;
}

int get_pivot_row(float** tableau, int pivotcolumnindex, int height, int rhscolumnindex, int startingrowindex) {
  //second row down must be constraints
  //only first row is objectiev function, therefore strip second stage when applicable
  int minratioindex;
  float minratio;
  bool minratiodefined = false;
  for (int i = startingrowindex; i < height; i++) {
    if (tableau[pivotcolumnindex][i] == 0) {
      continue;
    }
    float ratio = tableau[rhscolumnindex][i] / tableau[pivotcolumnindex][i];
    if (ratio < 0) {
      continue;
    }
    if (minratiodefined == false) {
      minratio = ratio;
      minratioindex = i;
      minratiodefined = true;
    }

    if (ratio < minratio) {
      minratio = ratio;
      minratioindex = i;
    }
  }
  return minratioindex; //minratioindex == minpivotrowindex is true
}

float** divide_pivot_row(float** tableau, int pivotcolumnindex, int pivotrowindex, int width) {
  float multiplier = tableau[pivotcolumnindex][pivotrowindex];
  for (int i = 0; i < width; i++) {
    tableau[i][pivotrowindex] /= multiplier;
  }

  return tableau;
}

float** perform_iteration(float** tableau, int pivotcolumnindex, int pivotrowindex, int width, int height) {
  // i represents the i th row and j represents the j th column
  tableau = divide_pivot_row(tableau, pivotcolumnindex, pivotrowindex, width);
  for (int i = 0; i < height; i++) {
    if (i == pivotrowindex) {
      continue;
    }
    float multiplier = -1 * tableau[pivotcolumnindex][i] / tableau[pivotcolumnindex][pivotrowindex];
    for (int j = 0; j < width; j++) {
      tableau[j][i] += multiplier * tableau[j][pivotrowindex];
    }
  }
return tableau;
}


float** maximise_objective_function(float** tableau, int width, int height, int startingrowindex) {
  std::cout << "maximising:" << std::endl;
  bool maximised = false;
  while(maximised == false) {
    printtableau(tableau, width, height);
    int pivotcolumnindex = get_pivot_column(tableau, width, true);
    std::cout << "pivot column index: " << pivotcolumnindex << std::endl;
    if (pivotcolumnindex == -1) {
      maximised = true;
      continue;
      //maximised
    }
    int pivotrowindex = get_pivot_row(tableau, pivotcolumnindex, height, width - 1, startingrowindex);
    std::cout << "pivot row index: " << pivotrowindex << std::endl;
    tableau = perform_iteration(tableau, pivotcolumnindex, pivotrowindex, width, height);
  }
  return tableau;
}

float** minimise_objective_function(float** tableau, int width, int height, int startingrowindex) {
  std::cout << "minimising:" << std::endl;
  bool minimised = false;
  while(minimised == false) {
    printtableau(tableau, width, height);
    int pivotcolumnindex = get_pivot_column(tableau, width, false);
    std::cout << "pivot column index: " << pivotcolumnindex << std::endl;
    if (pivotcolumnindex == -1) {
      minimised = true;
      continue;
      //maximised
    }
    int pivotrowindex = get_pivot_row(tableau, pivotcolumnindex, height, width - 1, startingrowindex);
    std::cout << "pivot row index: " << pivotrowindex << std::endl;
    tableau = perform_iteration(tableau, pivotcolumnindex, pivotrowindex, width, height);
  }
  return tableau;
}

float** convert_to_standard_form(float** tableau,int &width, int &height, int nartificialvar) {
  std::cout << "width: " << width << std::endl;
  for (int i = 0; i < width; i++) {
    //delete &tableau[i][0];
    //std::cout << "works" << std::endl;
    for (int j = 0; j < height - 1; j++) {
      //std::cout << j << std::endl;
      //std::cout << tableau[i][j] << " " << tableau[i][j + 1] << std::endl;
      tableau[i][j] = tableau[i][j + 1];
    }
  }
  //std::cout << "works" << std::endl;
  height -= 1;
  for (int i = 0; i < height; i++) {
    tableau[width - 1 - nartificialvar][i] = tableau[width - 1][i];
  }
  width -= nartificialvar;
  return tableau;
}
float** apply_simplex(float** tableau, int nvar, int nconstraints, int nartificialvar, int startingrowindex, std::string* varnames) {
  int height;
  int width = nvar + 2;
  if (nartificialvar != 0) {
    height = nconstraints + 2;
    tableau = minimise_objective_function(tableau, width, height, startingrowindex);
    //delete first row and  artificial variable columns
    tableau = convert_to_standard_form(tableau, width, height, nartificialvar);
    tableau = maximise_objective_function(tableau, width, height, 1);
  }
  else {
    height = nconstraints + 1;
    tableau = maximise_objective_function(tableau, width, height, startingrowindex);
  }

  float* solutions = read_simplex(tableau + 1, width - 1, height);
  printsolution(varnames, solutions, width - 1);
  return tableau;
}
