#include <sstream>
#include <iostream>
#include <vector>
#include "../arrays.cpp"
using namespace std;

string* SliceAlphabet(string alphabet[24], int numOfElements)
{
  string* outputstring = new string[numOfElements];
  for (int i = 0; i < numOfElements; i++)
  {
    outputstring[i] = alphabet[i];
  }
  return outputstring;

}

bool IsInteger(const std::string &s)
{
   if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

   char * p;
   strtol(s.c_str(), &p, 10);

   return (*p == 0);
}


bool IsDouble(string str)
{
    const char* c = str.c_str();
    char* endptr = 0;
    strtod(c, &endptr);

    if(*endptr != '\0' || endptr == c)
        return false;
    return true;
}


string ConvertMatToString(double** mat, int* order)
{
  string outputstring = "";
  outputstring += to_string(order[0]) + " " + to_string(order[1]) + " ";
  for (int i = 0; i < order[1]; i++)
  {
    for (int j = 0; j < order[0]; j++)
    {
      outputstring += to_string(mat[i][j]) + " ";
    }
  }
  return outputstring;
}
string* split(const string &s, char seperator)
{

  string* output = new string[s.length()];
  string::size_type prev_pos = 0, pos = 0;
  int x = 0;


  while((pos = s.find(seperator, pos)) != string::npos)
    {

      string substring( s.substr(prev_pos, pos-prev_pos) );

      output[x] = substring;
      prev_pos = ++pos;
      x++;
    }

    output[x] = s.substr(prev_pos, pos-prev_pos); // Last word

    return output;
}

void MakeMatrix(double** &mat, int &matrows, int &matcols, string* array, int &index)
{
  matrows = stoi(array[index]);
  index++;
  matcols = stoi(array[index]);
  index++;

  mat = initializedouble2dpointerarray(matcols, matrows);

  for (int i = 0; i < matcols; i++)
  {
    for (int j = 0; j < matrows; j++)
    {
      try {
        mat[i][j] = stod(array[index]);
      }
      catch (invalid_argument &e) {
        throw invalid_argument("Matrix contains invalid characters");
      }
      index++;
    }
  }
}

void parseSimulString(string &optype, double** &coeff, int &width, int &height, string* inputarray, int &index)
{
  optype = inputarray[index];
  index++;
  try
  {
    MakeMatrix(coeff, height, width, inputarray, index);
  }
  catch (invalid_argument &e) {
    throw invalid_argument("simultaneous equations contain invalid characters");
  }


}
void ParseStringTo2dArray(string &optype, int &mat1rows, int &mat1cols, int &mat2rows, int &mat2cols, double** &mat1, double** &mat2, string* inputarray, int index, string &constant, string &i, string &j)

  {
  //inputarray format: mat1rows, mat1cols, elements of mat1, mat2rows, mat2cols, elements of mat 2

  optype = inputarray[index];
  index++;

  MakeMatrix(mat1, mat1rows, mat1cols, inputarray, index);
  MakeMatrix(mat2, mat2rows, mat2cols, inputarray, index);
  constant = inputarray[index];
  index++;
  i = inputarray[index];
  index++;
  j = inputarray[index];
  index++;
  }

  void parseTableau(double** &tableau, int &numOfVar, int &numOfConstraints, int &numOfSlackVar, int &numOfArtificialVar, int &startingRowIndex, string &opType, string* &varnames, string* array, int index)
  {
    string variablenames[8] = {"P", "X", "Y", "Z", "W", "V", "U", "T"};
    opType = array[index];
    index++;

    numOfVar = stoi(array[index]);
    index++;

    numOfSlackVar = stoi(array[index]);
    index++;

    numOfArtificialVar = stoi(array[index]);
    index++;

    if (numOfArtificialVar == 0)
    {
      startingRowIndex = 1;
    }
    else
    {
      startingRowIndex = 2;
    }
    int matrows, matcols;
    MakeMatrix(tableau, matrows, matcols, array, index);

    varnames = new string[matcols - startingRowIndex];
    int temp = 0;
    for (int i = 0; i < numOfVar+1; i++)
    {
      varnames[i] = variablenames[i];
      temp++;
    }
    for (int i = 0; i < numOfSlackVar; i++)
    {
      varnames[temp] = "s" + to_string(i+1);
      temp++;
    }
    for (int i = 0; i < numOfArtificialVar; i++)
    {
      varnames[temp] = "a" + to_string(i+1);
      temp++;
    }
    numOfConstraints = matrows - startingRowIndex;

  }
