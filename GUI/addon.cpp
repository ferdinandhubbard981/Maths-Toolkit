// addon.cc
#include <node.h>
#include "operation-handler.cpp"
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
  string cppStr(*str);

  string returnstring = DoOperation(cppStr);
  //cout << returnstring;
  const char * returnchararray = returnstring.c_str();
  args.GetReturnValue().Set(String::NewFromUtf8(
      isolate, returnchararray).ToLocalChecked());

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
