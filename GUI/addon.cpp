// addon.cc
#include <node.h>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;
namespace demo {

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

// This is the implementation of the "add" method
// Input arguments are passed using the
// const FunctionCallbackInfo<Value>& args struct
string* split(const string& s, char seperator)
{
   string* output;

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

void Main(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  String::Utf8Value str(isolate, args[0]);
  string cppStr(*str); //cppstr format: mat1rows mat1cols mat2rows mat2cols elements of mat1 elements of mat 2
  cout << endl << "original string: " << cppStr << endl;
  int mat1rows, mat1cols, mat2rows, mat2cols;
  double mat1, mat2;
  ParseStringTo2dArray(mat1rows, mat1cols, mat2rows, mat2cols, mat1, mat2, cppStr);
  // Perform the operation
  //double value = args[0].As<Number>()->Value() + args[1].As<Number>()->Value();
  //Local<Number> num = Number::New(isolate, value);
  //Local<String> v8String = String::NewFromUtf8(isolate, cppStr.c_str(), String::kNormalString);
  // Set the return value (using the passed in
  // FunctionCallbackInfo<Value>&)
  //args.GetReturnValue().Set(v8String);
}

void Init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "main", Main);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

}  // namespace demo
