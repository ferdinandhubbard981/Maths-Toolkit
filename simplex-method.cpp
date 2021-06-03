
using namespace std;

void printsolution(string* varnames, double* solutions, int nsolutions, stringstream &buffer) {

  buffer << endl;
  for (int i = 0; i < nsolutions; i++) {
    buffer << varnames[i] << " = " << solutions[i] << endl;
  }
}
double* read_simplex(double** tableau, int width, int height) {
  double* solutions = new double[width - 1];
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
    {
      solutions[i] = tableau[width - 1][basicvalindex];
    }

  }

  return solutions;
}
void printtableau(double** tableau, int width, int height) {
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      cout << tableau[j][i] << "              ";
    }
    cout << endl;
  }
  cout << endl << endl << endl;
}

int get_pivot_column(double** tableau, int width, bool maximise) {
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

int get_pivot_row(double** tableau, int pivotcolumnindex, int height, int rhscolumnindex, int startingrowindex) {
  //second row down must be constraints
  //only first row is objectiev function, therefore strip second stage when applicable
  int minratioindex;
  double minratio;
  bool minratiodefined = false;
  for (int i = startingrowindex; i < height; i++) {
    if (tableau[pivotcolumnindex][i] == 0) {
      continue;
    }
    double ratio = tableau[rhscolumnindex][i] / tableau[pivotcolumnindex][i];
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

double** divide_pivot_row(double** tableau, int pivotcolumnindex, int pivotrowindex, int width) {
  double multiplier = tableau[pivotcolumnindex][pivotrowindex];
  for (int i = 0; i < width; i++) {
    tableau[i][pivotrowindex] /= multiplier;
  }

  return tableau;
}

double** perform_iteration(double** tableau, int pivotcolumnindex, int pivotrowindex, int width, int height) {
  // i represents the i th row and j represents the j th column
  tableau = divide_pivot_row(tableau, pivotcolumnindex, pivotrowindex, width);
  for (int i = 0; i < height; i++) {
    if (i == pivotrowindex) {
      continue;
    }
    double multiplier = -1 * tableau[pivotcolumnindex][i] / tableau[pivotcolumnindex][pivotrowindex];
    for (int j = 0; j < width; j++) {
      tableau[j][i] += multiplier * tableau[j][pivotrowindex];
    }
  }
return tableau;
}


double** maximise_objective_function(double** tableau, int width, int height, int startingrowindex) {
  cout << "maximising:" << endl;
  bool maximised = false;
  while(maximised == false) {
    printtableau(tableau, width, height);
    int pivotcolumnindex = get_pivot_column(tableau, width, true);
    cout << "pivot column index: " << pivotcolumnindex << endl;
    if (pivotcolumnindex == -1) {
      maximised = true;
      continue;
      //maximised
    }
    int pivotrowindex = get_pivot_row(tableau, pivotcolumnindex, height, width - 1, startingrowindex);
    cout << "pivot row index: " << pivotrowindex << endl;
    tableau = perform_iteration(tableau, pivotcolumnindex, pivotrowindex, width, height);
  }
  return tableau;
}

double** minimise_objective_function(double** tableau, int width, int height, int startingrowindex) {
  cout << "minimising:" << endl;
  bool minimised = false;
  while(minimised == false) {
    printtableau(tableau, width, height);
    int pivotcolumnindex = get_pivot_column(tableau, width, false);
    cout << "pivot column index: " << pivotcolumnindex << endl;
    if (pivotcolumnindex == -1) {
      minimised = true;
      continue;
      //maximised
    }
    int pivotrowindex = get_pivot_row(tableau, pivotcolumnindex, height, width - 1, startingrowindex);
    cout << "pivot row index: " << pivotrowindex << endl;
    tableau = perform_iteration(tableau, pivotcolumnindex, pivotrowindex, width, height);
  }
  return tableau;
}

double** convert_to_standard_form(double** tableau,int &width, int &height, int nartificialvar) {
  cout << "width: " << width << endl;
  for (int i = 0; i < width; i++) {
    //delete &tableau[i][0];
    //cout << "works" << endl;
    for (int j = 0; j < height - 1; j++) {
      //cout << j << endl;
      //cout << tableau[i][j] << " " << tableau[i][j + 1] << endl;
      tableau[i][j] = tableau[i][j + 1];
    }
  }
  //cout << "works" << endl;
  height -= 1;
  for (int i = 0; i < height; i++) { // move RHS column to first art variable then change width index to effectively remove all art var
    tableau[width - 1 - nartificialvar][i] = tableau[width - 1][i];
  }
  width -= nartificialvar;
  for (int j = 0; j < height; j++) // remove art var "A" at beginning
  {
    for (int i = 0; i < width; i++)
    {
      tableau[i][j] = tableau[i+1][j]; //need to shift all var back by 1 along row (horizontally)
    }
  }
  width -= 1; // move index
  return tableau;
}
double** apply_simplex(double** tableau, int nvar, int nconstraints, int nslackvar, int nartificialvar, int startingrowindex, string* varnames, stringstream &buffer) {
  int height;
  int width = nvar + nslackvar + nartificialvar + 2;
  if (nartificialvar != 0) {
    width++;
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

  double* solutions = read_simplex(tableau, width, height);
  cout << endl << "solutions[2]: " << solutions[2] << endl;
  printsolution(varnames, solutions, width-1, buffer);
  return tableau;
}
