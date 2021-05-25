#include "dataparser.cpp"

int main()
{

  string inputstring = "2 2 1 3 2 4 2 2 5 7 6 8";
  try
  {
    string optype;
    int mat1rows, mat1cols, mat2rows, mat2cols;
    double** mat1;
    double** mat2;
    ParseStringTo2dArray(optype, mat1rows, mat1cols, mat2rows, mat2cols, mat1, mat2, inputstring);
    cout << mat2[1][1];
  }
/*  catch(const exception &exc)
  {
    cerr << exc.what();
  }*/
  catch(...)
  {
    cout << "uknown error" << endl;
  }
}
