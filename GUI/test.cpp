#include "dataparser.cpp"

int main()
{
  cout << "test" << endl;
  string inputstring = "1 2 3";
  try
  {
    cout << "1" << endl;
    cout << split(inputstring, ' ')[0];
    cout << "2" << endl;
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
