#include <sstream>
#include <iostream>
#include <vector>
#include "../arrays.cpp"
using namespace std;

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
      mat[i][j] = stod(array[index]);
      index++;
    }
  }
}
void ParseStringTo2dArray(string &optype, int &mat1rows, int &mat1cols, int &mat2rows, int &mat2cols, double** &mat1, double** &mat2, string inputstring)
{
  int index = 0;
  string* array = split(inputstring, ' ');
  //array format: mat1rows, mat1cols, elements of mat1, mat2rows, mat2cols, elements of mat 2

  optype = array[index];
  index++;

  MakeMatrix(mat1, mat1rows, mat1cols, array, index);
  MakeMatrix(mat2, mat2rows, mat2cols, array, index);



}
