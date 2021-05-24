// addon.cc
#include <node.h>
#include "dataparser.cpp"
using namespace std;

using v8::Exception;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;


void Main(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  String::Utf8Value str(isolate, args[0]);
  string cppStr(*str); //cppstr format: mat1rows mat1cols mat2rows mat2cols elements of mat1 elements of mat 2
  cout << endl << "original string: " << cppStr << endl;
  int mat1rows, mat1cols, mat2rows, mat2cols;
  double mat1, mat2;
  try
  {

    ParseStringTo2dArray(mat1rows, mat1cols, mat2rows, mat2cols, mat1, mat2, cppStr);
  }

  catch (const std::exception& e)
  {
    cout << e << endl;
  }
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
