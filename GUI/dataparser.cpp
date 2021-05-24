#include <sstream>
#include <iostream>
#include <vector>
using namespace std;


string* split(const string &s, char seperator)
{

  string* output;
   cout << "a" << endl;
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


void ParseStringTo2dArray(int &mat1rows, int &mat1cols, int &mat2rows, int &mat2cols, double mat1, double mat2, string inputstring)
{
  cout << "working" << endl;
  string* array = split(inputstring, ' ');
  cout << endl << "test: " << array[2] << endl;


}
