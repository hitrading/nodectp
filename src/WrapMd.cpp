/////////////////////////////////////////////////////////////////////////
///@system ctp 行情nodejs addon
///@company 慧网基金
///@file WrapMd.cpp
///@brief js回调接口
///@history
///20160326	dreamyzhang		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "WrapMd.h"

namespace md
{
using v8::HandleScope;
using v8::Exception;
using v8::Null;
using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Int32;
using v8::Boolean;
using v8::Handle;


set<string>         WrapMd::m_event;                //可以注册的回调事件
Persistent<Function> WrapMd::constructor;           //主动请求函数映射js name


WrapMd::WrapMd()
{

}

WrapMd::~WrapMd()
{

}


void WrapMd::Init(Isolate* isolate)
{
    //主动请求函数的映射
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "WrapMd"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "init", Init);
    NODE_SET_PROTOTYPE_METHOD(tpl, "release", Release);
    NODE_SET_PROTOTYPE_METHOD(tpl, "dispose", Dispose);
    NODE_SET_PROTOTYPE_METHOD(tpl, "createFtdcMdApi", CreateFtdcMdApi);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getApiVersion", GetApiVersion);
    NODE_SET_PROTOTYPE_METHOD(tpl, "getTradingDay", GetTradingDay);
    NODE_SET_PROTOTYPE_METHOD(tpl, "registerFront"       , RegisterFront       );
    NODE_SET_PROTOTYPE_METHOD(tpl, "registerNameServer"  , RegisterNameServer  );
    NODE_SET_PROTOTYPE_METHOD(tpl, "registerFensUserInfo", RegisterFensUserInfo);
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqUserLogin", ReqUserLogin);
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqUserLogout", ReqUserLogout);
    NODE_SET_PROTOTYPE_METHOD(tpl, "subscribeMarketData", SubscribeMarketData);
    NODE_SET_PROTOTYPE_METHOD(tpl, "unSubscribeMarketData", UnSubscribeMarketData);
    NODE_SET_PROTOTYPE_METHOD(tpl, "subscribeForQuoteRsp", SubscribeForQuoteRsp);
    NODE_SET_PROTOTYPE_METHOD(tpl, "unSubscribeForQuoteRsp", UnSubscribeForQuoteRsp);
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryMulticastInstrument", ReqQryMulticastInstrument);
    NODE_SET_PROTOTYPE_METHOD(tpl, "on", On);
    constructor.Reset(isolate, tpl->GetFunction());

    //注册回调函数的映射更新
    m_event.insert("onFrontConnected");
    m_event.insert("onFrontDisconnected");
    m_event.insert("onHeartBeatWarning");
    m_event.insert("onRspUserLogin");
    m_event.insert("onRspUserLogout");
    m_event.insert("onRspQryMulticastInstrument");
    m_event.insert("onRspError");
    m_event.insert("onRspSubMarketData");
    m_event.insert("onRspUnSubMarketData");
    m_event.insert("onRspSubForQuoteRsp");
    m_event.insert("onRspUnSubForQuoteRsp");
    m_event.insert("onRtnDepthMarketData");
    m_event.insert("onRtnForQuoteRsp");

}

void WrapMd::New(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    if(args.IsConstructCall())
    {
        // Invoked as constructor: `new MyObject(...)`
        WrapMd* obj = new WrapMd();
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
    }
    else
    {
        // Invoked as plain function `MyObject(...)`, turn into construct call
        Local<Function> cons = Local<Function>::New(isolate, constructor);
        Local<Context> context = isolate->GetCurrentContext();
        Local<Object> instance = cons->NewInstance(context, 0, NULL).ToLocalChecked();
        args.GetReturnValue().Set(instance);
    }
}

void WrapMd::NewInstance(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> instance  = cons->NewInstance(context, 0, NULL).ToLocalChecked();
    args.GetReturnValue().Set(instance);
}

void WrapMd::On(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());

    if (args[0]->IsUndefined() || args[1]->IsUndefined())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments->event name or function")));
        return;
    }

    //WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());

    Local<String> eventName = args[0]->ToString();
    Local<Function> cb = Local<Function>::Cast(args[1]);

    String::Utf8Value eNameUtf8(eventName);
    std::set<string>::iterator eit = m_event.find(*eNameUtf8);
    if (eit == m_event.end())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "System has no register this event")));
        return;
    }

    if(obj->CanCallback(*eit))
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Callback is defined before")));
        return;
    }

    obj->SetCallback(*eNameUtf8, cb, isolate);

    args.GetReturnValue().Set(Number::New(isolate, 0));
}

void WrapMd::Init(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    obj->GetMdApi()->Init();
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapMd::Release(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    obj->GetMdApi()->Release();
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapMd::Dispose(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    obj->dispose();
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapMd::CreateFtdcMdApi(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined())
    {
        args[0] = String::NewFromUtf8(isolate, "");
    }
    Local<String> flowpath = args[0]->ToString();
    String::Utf8Value p(flowpath);


    CThostFtdcMdApi* m_pApi = CThostFtdcMdApi::CreateFtdcMdApi((char*)*p);

    obj->setMdApi(m_pApi);
    obj->RegisterSpi();
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapMd::GetApiVersion(const FunctionCallbackInfo<Value>& args)
{
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    const char* v = obj->GetMdApi()->GetApiVersion();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, v));
}

void WrapMd::GetTradingDay(const FunctionCallbackInfo<Value>& args)
{
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    const char* t = obj->GetMdApi()->GetTradingDay();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, t));
}
void WrapMd::RegisterFront(const FunctionCallbackInfo<Value>& args)
{
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    Local<String> url = args[0]->ToString();
    String::Utf8Value u(url);

    obj->GetMdApi()->RegisterFront((char*)*u);
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapMd::RegisterNameServer(const FunctionCallbackInfo<Value>& args)
{
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    Local<String> url = args[0]->ToString();
    String::Utf8Value u(url);

    obj->GetMdApi()->RegisterNameServer((char*)*u);
    args.GetReturnValue().Set(Undefined(isolate));
}
void WrapMd::RegisterFensUserInfo(const FunctionCallbackInfo<Value>& args)
{
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined() || !args[0]->IsObject())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    Local<Object> objjs = args[0]->ToObject();
    CThostFtdcFensUserInfoField req;
    CSFunction::set_struct(objjs, &req);
    obj->GetMdApi()->RegisterFensUserInfo(&req);
    args.GetReturnValue().Set(Undefined(isolate));
}
#define REQ_WITH_REQID(req) \
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());\
    Isolate* isolate = args.GetIsolate();\
    if (args[0]->IsUndefined() || !args[0]->IsObject() || args[1]->IsUndefined())\
    {\
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));\
        return;\
    }\
    memset(&req, 0, sizeof(req));\
    Local<Object> objjs = args[0]->ToObject();\
    CSFunction::set_struct(objjs, &req);\
    int reqid = args[1]->Int32Value();

void WrapMd::ReqUserLogin(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcReqUserLoginField req;
    REQ_WITH_REQID(req);
    int r = obj->GetMdApi()->ReqUserLogin(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapMd::ReqUserLogout(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcUserLogoutField req;
    REQ_WITH_REQID(req);
    int r = obj->GetMdApi()->ReqUserLogout(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapMd::ReqQryMulticastInstrument(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcQryMulticastInstrumentField req;
    REQ_WITH_REQID(req);
    int r = obj->GetMdApi()->ReqQryMulticastInstrument(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapMd::SubscribeMarketData(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    if (args[0]->IsUndefined() || !args[0]->IsArray())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    Local<v8::Array> instrumentIDs = Local<v8::Array>::Cast(args[0]);
    char** idArray = new char*[instrumentIDs->Length()];
    for (uint32_t i = 0; i < instrumentIDs->Length(); i++)
    {
        Local<String> instrumentId = instrumentIDs->Get(i)->ToString();
        String::Utf8Value idUtf8(instrumentId);
        idArray[i] = new char[instrumentId->Length() + 1];
        memset(idArray[i], 0, instrumentId->Length()+1);
        strncpy(idArray[i], (char*)*idUtf8, instrumentId->Length());
    }

    int r = obj->GetMdApi()->SubscribeMarketData(idArray, instrumentIDs->Length());
    delete idArray;
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapMd::UnSubscribeMarketData(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    if (args[0]->IsUndefined() || !args[0]->IsArray())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    Local<v8::Array> instrumentIDs = Local<v8::Array>::Cast(args[0]);
    char** idArray = new char*[instrumentIDs->Length()];

    for (uint32_t i = 0; i < instrumentIDs->Length(); i++)
    {
        Local<String> instrumentId = instrumentIDs->Get(i)->ToString();
        String::Utf8Value idUtf8(instrumentId);
        char* id = new char[instrumentId->Length() + 1];
        strcpy(id, (char*)*idUtf8);
        idArray[i] = id;
    }
    int r = obj->GetMdApi()->UnSubscribeMarketData(idArray, instrumentIDs->Length());
    delete idArray;
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapMd::SubscribeForQuoteRsp(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    if (args[0]->IsUndefined() || !args[0]->IsArray())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    Local<v8::Array> instrumentIDs = Local<v8::Array>::Cast(args[0]);
    char** idArray = new char*[instrumentIDs->Length()];
    for (uint32_t i = 0; i < instrumentIDs->Length(); i++)
    {
        Local<String> instrumentId = instrumentIDs->Get(i)->ToString();
        String::Utf8Value idUtf8(instrumentId);
        idArray[i] = new char[instrumentId->Length() + 1];
        memset(idArray[i], 0, instrumentId->Length()+1);
        strncpy(idArray[i], (char*)*idUtf8, instrumentId->Length());
    }

    int r = obj->GetMdApi()->SubscribeForQuoteRsp(idArray, instrumentIDs->Length());
    delete idArray;
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapMd::UnSubscribeForQuoteRsp(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    WrapMd* obj = node::ObjectWrap::Unwrap<WrapMd>(args.Holder());
    if (args[0]->IsUndefined() || !args[0]->IsArray())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }

    Local<v8::Array> instrumentIDs = Local<v8::Array>::Cast(args[0]);
    char** idArray = new char*[instrumentIDs->Length()];

    for (uint32_t i = 0; i < instrumentIDs->Length(); i++)
    {
        Local<String> instrumentId = instrumentIDs->Get(i)->ToString();
        String::Utf8Value idUtf8(instrumentId);
        char* id = new char[instrumentId->Length() + 1];
        strcpy(id, (char*)*idUtf8);
        idArray[i] = id;
    }
    int r = obj->GetMdApi()->UnSubscribeForQuoteRsp(idArray, instrumentIDs->Length());
    delete idArray;
    args.GetReturnValue().Set(Int32::New(isolate, r));
}


/////////////////////////////on回调函数///////////////////////////////////////////////////////////
void WrapMd::MainOnFrontConnected()
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onFrontConnected");
    if(it == callback_map.end()) return;

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 0, NULL);
}

void WrapMd::MainOnFrontDisconnected(int nReason)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

   __callback_iter_type it = callback_map.find("onFrontDisconnected");
    if(it == callback_map.end()) return;

    Local<Value> argv[1] = { Local<Value>::New(isolate, Int32::New(isolate, nReason)) };

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 1, argv);
}

void WrapMd::MainOnHeartBeatWarning(int nTimeLapse)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onHeartBeatWarning");
    if(it == callback_map.end()) return;

    Local<Value> argv[1] = { Local<Value>::New(isolate, Int32::New(isolate, nTimeLapse)) };

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 1, argv);
}

void WrapMd::MainOnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onRspUserLogin");
    if(it == callback_map.end()) return;

    Local<Value> argv[4];
    if(pRspUserLogin != NULL)
    {
        Local<Object> jsonRtn = Object::New(isolate);
        jsonRtn->Set(String::NewFromUtf8(isolate, "tradingDay"), String::NewFromUtf8(isolate, pRspUserLogin->TradingDay));
        jsonRtn->Set(String::NewFromUtf8(isolate, "loginTime"), String::NewFromUtf8(isolate, pRspUserLogin->LoginTime));
        jsonRtn->Set(String::NewFromUtf8(isolate, "brokerId"), String::NewFromUtf8(isolate, pRspUserLogin->BrokerID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "userId"), String::NewFromUtf8(isolate, pRspUserLogin->UserID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "systemName"), String::NewFromUtf8(isolate, pRspUserLogin->SystemName));
        jsonRtn->Set(String::NewFromUtf8(isolate, "frontId"), Int32::New(isolate, pRspUserLogin->FrontID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "sessionId"), Int32::New(isolate, pRspUserLogin->SessionID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "maxOrderRef"), String::NewFromUtf8(isolate, pRspUserLogin->MaxOrderRef));
        jsonRtn->Set(String::NewFromUtf8(isolate, "shfeTime"), String::NewFromUtf8(isolate, pRspUserLogin->SHFETime));
        jsonRtn->Set(String::NewFromUtf8(isolate, "dceTime"), String::NewFromUtf8(isolate, pRspUserLogin->DCETime));
        jsonRtn->Set(String::NewFromUtf8(isolate, "czceTime"), String::NewFromUtf8(isolate, pRspUserLogin->CZCETime));
        jsonRtn->Set(String::NewFromUtf8(isolate, "ffexTime"), String::NewFromUtf8(isolate, pRspUserLogin->FFEXTime));
        jsonRtn->Set(String::NewFromUtf8(isolate, "ineTime"), String::NewFromUtf8(isolate, pRspUserLogin->INETime));
        argv[0] = jsonRtn;
    }
    else
    {
        argv[0] = Local<Value>::New(isolate, Undefined(isolate));
    }
    argv[1] = PkgRspInfo(pRspInfo);
    argv[2] = Local<Value>::New(isolate, Int32::New(isolate, nRequestID));

    argv[3] = Boolean::New(isolate, bIsLast)->ToBoolean();

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 4, argv);
}

void WrapMd::MainOnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onRspUserLogout");
    if(it == callback_map.end()) return;

    Local<Value> argv[4];
    if(pUserLogout != NULL)
    {
        Local<Object> jsonRtn = Object::New(isolate);
        jsonRtn->Set(String::NewFromUtf8(isolate, "brokerId"), String::NewFromUtf8(isolate, pUserLogout->BrokerID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "userId"), String::NewFromUtf8(isolate, pUserLogout->UserID));
        argv[0] = jsonRtn;
    }
    else
    {
        argv[0] = Local<Value>::New(isolate, Undefined(isolate));
    }
    argv[1] = PkgRspInfo(pRspInfo);
    argv[2] = Local<Value>::New(isolate, Int32::New(isolate, nRequestID));

    argv[3] = Boolean::New(isolate, bIsLast)->ToBoolean();

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 4, argv);
}

void WrapMd::MainOnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onRspError");
    if(it == callback_map.end()) return;

    Local<Value> argv[3];
    argv[0] = PkgRspInfo(pRspInfo);
    argv[1] = Local<Value>::New(isolate, Int32::New(isolate, nRequestID));
    argv[2] = Boolean::New(isolate, bIsLast)->ToBoolean();

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 3, argv);
}

void WrapMd::MainOnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onRspSubMarketData");
    if(it == callback_map.end()) return;

    Local<Value> argv[4];
    if(pSpecificInstrument != NULL)
    {
        Local<Object> jsonRtn = Object::New(isolate);
        jsonRtn->Set(String::NewFromUtf8(isolate, "instrumentId"), String::NewFromUtf8(isolate, pSpecificInstrument->InstrumentID));
        argv[0] = jsonRtn;
    }
    else
    {
        argv[0] = Local<Value>::New(isolate, Undefined(isolate));
    }
    argv[1] = PkgRspInfo(pRspInfo);
    argv[2] = Local<Value>::New(isolate, Int32::New(isolate, nRequestID));

    argv[3] = Boolean::New(isolate, bIsLast)->ToBoolean();

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 4, argv);
}

void WrapMd::MainOnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onRspUnSubMarketData");
    if(it == callback_map.end()) return;

    Local<Value> argv[4];
    if(pSpecificInstrument != NULL)
    {
        Local<Object> jsonRtn = Object::New(isolate);
        jsonRtn->Set(String::NewFromUtf8(isolate, "instrumentId"), String::NewFromUtf8(isolate, pSpecificInstrument->InstrumentID));
        argv[0] = jsonRtn;
    }
    else
    {
        argv[0] = Local<Value>::New(isolate, Undefined(isolate));
    }
    argv[1] = PkgRspInfo(pRspInfo);
    argv[2] = Local<Value>::New(isolate, Int32::New(isolate, nRequestID));
    argv[3] = Boolean::New(isolate, bIsLast)->ToBoolean();

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 4, argv);
}

void WrapMd::MainOnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onRspSubForQuoteRsp");
    if(it == callback_map.end()) return;

    Local<Value> argv[4];
    if(pSpecificInstrument != NULL)
    {
        Local<Object> jsonRtn = Object::New(isolate);
        jsonRtn->Set(String::NewFromUtf8(isolate, "instrumentId"), String::NewFromUtf8(isolate, pSpecificInstrument->InstrumentID));
        argv[0] = jsonRtn;
    }
    else
    {
        argv[0] = Local<Value>::New(isolate, Undefined(isolate));
    }
    argv[1] = PkgRspInfo(pRspInfo);
    argv[2] = Local<Value>::New(isolate, Int32::New(isolate, nRequestID));
    argv[3] = Boolean::New(isolate, bIsLast)->ToBoolean();

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 4, argv);
}

void WrapMd::MainOnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onRspUnSubForQuoteRsp");
    if(it == callback_map.end()) return;

    Local<Value> argv[4];
    if(pSpecificInstrument != NULL)
    {
        Local<Object> jsonRtn = Object::New(isolate);
        jsonRtn->Set(String::NewFromUtf8(isolate, "instrumentId"), String::NewFromUtf8(isolate, pSpecificInstrument->InstrumentID));
        argv[0] = jsonRtn;
    }
    else
    {
        argv[0] = Local<Value>::New(isolate, Undefined(isolate));
    }
    argv[1] = PkgRspInfo(pRspInfo);
    argv[2] = Local<Value>::New(isolate, Int32::New(isolate, nRequestID));
    argv[3] = Boolean::New(isolate, bIsLast)->ToBoolean();

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 4, argv);
}


void WrapMd::MainOnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onRtnDepthMarketData");
    if(it == callback_map.end()) return;

    Local<Value> argv[1];
    if(pDepthMarketData != NULL)
    {
        Local<Object> jsonRtn = Object::New(isolate);
        jsonRtn->Set(String::NewFromUtf8(isolate, "tradingDay"), String::NewFromUtf8(isolate, pDepthMarketData->TradingDay));
        jsonRtn->Set(String::NewFromUtf8(isolate, "instrumentId"), String::NewFromUtf8(isolate, pDepthMarketData->InstrumentID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "exchangeId"), String::NewFromUtf8(isolate, pDepthMarketData->ExchangeID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "exchangeInstId"), String::NewFromUtf8(isolate, pDepthMarketData->ExchangeInstID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "lastPrice"), Number::New(isolate, pDepthMarketData->LastPrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "preSettlementPrice"), Number::New(isolate, pDepthMarketData->PreSettlementPrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "preClosePrice"), Number::New(isolate, pDepthMarketData->PreClosePrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "preOpenInterest"), Number::New(isolate, pDepthMarketData->PreOpenInterest));
        jsonRtn->Set(String::NewFromUtf8(isolate, "openPrice"), Number::New(isolate, pDepthMarketData->OpenPrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "highestPrice"), Number::New(isolate, pDepthMarketData->HighestPrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "lowestPrice"), Number::New(isolate, pDepthMarketData->LowestPrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "volume"), Int32::New(isolate, pDepthMarketData->Volume));
        jsonRtn->Set(String::NewFromUtf8(isolate, "turnover"), Number::New(isolate, pDepthMarketData->Turnover));
        jsonRtn->Set(String::NewFromUtf8(isolate, "openInterest"), Number::New(isolate, pDepthMarketData->OpenInterest));
        jsonRtn->Set(String::NewFromUtf8(isolate, "closePrice"), Number::New(isolate, pDepthMarketData->ClosePrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "settlementPrice"), Number::New(isolate, pDepthMarketData->SettlementPrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "upperLimitPrice"), Number::New(isolate, pDepthMarketData->UpperLimitPrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "lowerLimitPrice"), Number::New(isolate, pDepthMarketData->LowerLimitPrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "preDelta"), Number::New(isolate, pDepthMarketData->PreDelta));
        jsonRtn->Set(String::NewFromUtf8(isolate, "currDelta"), Number::New(isolate, pDepthMarketData->CurrDelta));
        jsonRtn->Set(String::NewFromUtf8(isolate, "updateTime"), String::NewFromUtf8(isolate, pDepthMarketData->UpdateTime));
        jsonRtn->Set(String::NewFromUtf8(isolate, "updateMillisec"), Int32::New(isolate, pDepthMarketData->UpdateMillisec));
        jsonRtn->Set(String::NewFromUtf8(isolate, "bidPrice1"), Number::New(isolate, pDepthMarketData->BidPrice1));
        jsonRtn->Set(String::NewFromUtf8(isolate, "bidVolume1"), Number::New(isolate, pDepthMarketData->BidVolume1));
        jsonRtn->Set(String::NewFromUtf8(isolate, "askPrice1"), Number::New(isolate, pDepthMarketData->AskPrice1));
        jsonRtn->Set(String::NewFromUtf8(isolate, "askVolume1"), Number::New(isolate, pDepthMarketData->AskVolume1));
        jsonRtn->Set(String::NewFromUtf8(isolate, "bidPrice2"), Number::New(isolate, pDepthMarketData->BidPrice2));
        jsonRtn->Set(String::NewFromUtf8(isolate, "bidVolume2"), Number::New(isolate, pDepthMarketData->BidVolume2));
        jsonRtn->Set(String::NewFromUtf8(isolate, "askPrice2"), Number::New(isolate, pDepthMarketData->AskPrice2));
        jsonRtn->Set(String::NewFromUtf8(isolate, "askVolume2"), Number::New(isolate, pDepthMarketData->AskVolume2));
        jsonRtn->Set(String::NewFromUtf8(isolate, "bidPrice3"), Number::New(isolate, pDepthMarketData->BidPrice3));
        jsonRtn->Set(String::NewFromUtf8(isolate, "bidVolume3"), Number::New(isolate, pDepthMarketData->BidVolume3));
        jsonRtn->Set(String::NewFromUtf8(isolate, "askPrice3"), Number::New(isolate, pDepthMarketData->AskPrice3));
        jsonRtn->Set(String::NewFromUtf8(isolate, "askVolume3"), Number::New(isolate, pDepthMarketData->AskVolume3));
        jsonRtn->Set(String::NewFromUtf8(isolate, "bidPrice4"), Number::New(isolate, pDepthMarketData->BidPrice4));
        jsonRtn->Set(String::NewFromUtf8(isolate, "bidVolume4"), Number::New(isolate, pDepthMarketData->BidVolume4));
        jsonRtn->Set(String::NewFromUtf8(isolate, "askPrice4"), Number::New(isolate, pDepthMarketData->AskPrice4));
        jsonRtn->Set(String::NewFromUtf8(isolate, "askVolume4"), Number::New(isolate, pDepthMarketData->AskVolume4));
        jsonRtn->Set(String::NewFromUtf8(isolate, "bidPrice5"), Number::New(isolate, pDepthMarketData->BidPrice5));
        jsonRtn->Set(String::NewFromUtf8(isolate, "bidVolume5"), Number::New(isolate, pDepthMarketData->BidVolume5));
        jsonRtn->Set(String::NewFromUtf8(isolate, "askPrice5"), Number::New(isolate, pDepthMarketData->AskPrice5));
        jsonRtn->Set(String::NewFromUtf8(isolate, "askVolume5"), Number::New(isolate, pDepthMarketData->AskVolume5));
        jsonRtn->Set(String::NewFromUtf8(isolate, "averagePrice"), Number::New(isolate, pDepthMarketData->AveragePrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "actionDay"), String::NewFromUtf8(isolate, pDepthMarketData->ActionDay));
        argv[0] = jsonRtn;
    }
    else
    {
        argv[0] = Local<Value>::New(isolate, Undefined(isolate));
    }

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 1, argv);
}

void WrapMd::MainOnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onRtnForQuoteRsp");
    if(it == callback_map.end()) return;

    Local<Value> argv[1];
    if(pForQuoteRsp != NULL)
    {
        Local<Object> jsonRtn = Object::New(isolate);
        jsonRtn->Set(String::NewFromUtf8(isolate, "tradingDay"), String::NewFromUtf8(isolate, pForQuoteRsp->TradingDay));
        jsonRtn->Set(String::NewFromUtf8(isolate, "instrumentId"), String::NewFromUtf8(isolate, pForQuoteRsp->InstrumentID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "forQuoteSysId"), String::NewFromUtf8(isolate, pForQuoteRsp->ForQuoteSysID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "forQuoteTime"), String::NewFromUtf8(isolate, pForQuoteRsp->ForQuoteTime));
        jsonRtn->Set(String::NewFromUtf8(isolate, "actionDay"), String::NewFromUtf8(isolate, pForQuoteRsp->ActionDay));
        jsonRtn->Set(String::NewFromUtf8(isolate, "exchangeId"), String::NewFromUtf8(isolate, pForQuoteRsp->ExchangeID));
        argv[0] = jsonRtn;
    }
    else
    {
        argv[0] = Local<Value>::New(isolate, Undefined(isolate));
    }

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 1, argv);
}

void WrapMd::MainOnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope(isolate);

    __callback_iter_type it = callback_map.find("onRspQryMulticastInstrument");
    if(it == callback_map.end()) return;

    Local<Value> argv[4];
    if(pMulticastInstrument != NULL)
    {
        Local<Object> jsonRtn = Object::New(isolate);
        jsonRtn->Set(String::NewFromUtf8(isolate, "topicId"), Int32::New(isolate, pMulticastInstrument->TopicID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "instrumentId"), String::NewFromUtf8(isolate, pMulticastInstrument->InstrumentID));
        jsonRtn->Set(String::NewFromUtf8(isolate, "instrumentNo"), Int32::New(isolate, pMulticastInstrument->InstrumentNo));
        jsonRtn->Set(String::NewFromUtf8(isolate, "codePrice"), Number::New(isolate, pMulticastInstrument->CodePrice));
        jsonRtn->Set(String::NewFromUtf8(isolate, "volumeMultiple"), Int32::New(isolate, pMulticastInstrument->VolumeMultiple));
        jsonRtn->Set(String::NewFromUtf8(isolate, "priceTick"), Number::New(isolate, pMulticastInstrument->PriceTick));
        argv[0] = jsonRtn;
    }
    else
    {
        argv[0] = Local<Value>::New(isolate, Undefined(isolate));
    }
    argv[1] = PkgRspInfo(pRspInfo);
    argv[2] = Local<Value>::New(isolate, Int32::New(isolate, nRequestID));

    argv[3] = Boolean::New(isolate, bIsLast)->ToBoolean();

    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 4, argv);
}

}





