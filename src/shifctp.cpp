#include <signal.h>
#include <node.h>
#include "WrapMd.h"
#include "WrapTd.h"
#include <nan.h>


namespace ctp
{
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::Value;
using v8::Value;

void signal_segv(int sig)
{
    printf("catch SIGSEGV\n");
}

void CreateMd(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
    // args.GetReturnValue().Set(md::WrapMd::NewInstance(args));
    md::WrapMd::NewInstance(args);
}

void CreateTd(const Nan::FunctionCallbackInfo<v8::Value>& args)
{
    // args.GetReturnValue().Set(td::WrapTd::NewInstance(args));
    td::WrapTd::NewInstance(args);
}


void Init(Local<Object> exports)
{
  //signal(SIGSEGV, signal_segv);
  v8::Local<v8::Context> context = exports->CreationContext();

  md::WrapMd::Init();
  td::WrapTd::Init();

  exports->Set(
    context,
    Nan::New("crmd").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(CreateMd)->GetFunction(context).ToLocalChecked()
  );

  exports->Set(
    context,
    Nan::New("crtd").ToLocalChecked(),
    Nan::New<v8::FunctionTemplate>(CreateTd)->GetFunction(context).ToLocalChecked()
  );
}

NODE_MODULE(shifctp, Init)

};



