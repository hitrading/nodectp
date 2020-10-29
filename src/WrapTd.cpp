/////////////////////////////////////////////////////////////////////////
///@system ctp trader addon
///@company 慧网基金
///@file WrapTd.cpp
///@brief 定义js接口
///@history
///20160326	dreamyzhang		创建该文件
/////////////////////////////////////////////////////////////////////////

#include "WrapTd.h"

namespace td
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


set<string>         WrapTd::m_event;                //可以注册的回调事件
Persistent<Function> WrapTd::constructor;           //主动请求函数映射js name

WrapTd::WrapTd()
{

}

WrapTd::~WrapTd()
{

}
void WrapTd::Init(v8::Isolate* isolate)
{
	//主动请求函数的映射
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
    tpl->SetClassName(String::NewFromUtf8(isolate, "WrapTd"));
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    NODE_SET_PROTOTYPE_METHOD(tpl, "getApiVersion"                   , GetApiVersion                      );
    NODE_SET_PROTOTYPE_METHOD(tpl, "init"                            , Init                               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "release"                         , Release                            );
    NODE_SET_PROTOTYPE_METHOD(tpl, "dispose"                         , Dispose                            );
    NODE_SET_PROTOTYPE_METHOD(tpl, "createFtdcTraderApi"             , CreateFtdcTraderApi                );
    NODE_SET_PROTOTYPE_METHOD(tpl, "getTradingDay"                   , GetTradingDay                      );
    NODE_SET_PROTOTYPE_METHOD(tpl, "registerFront"                   , RegisterFront                      );
    NODE_SET_PROTOTYPE_METHOD(tpl, "registerNameServer"              , RegisterNameServer                 );
    NODE_SET_PROTOTYPE_METHOD(tpl, "registerFensUserInfo"            , RegisterFensUserInfo               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "subscribePrivateTopic"           , SubscribePrivateTopic              );
    NODE_SET_PROTOTYPE_METHOD(tpl, "subscribePublicTopic"            , SubscribePublicTopic               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqAuthenticate"                 , ReqAuthenticate                    );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqUserLogin"                    , ReqUserLogin                       );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqUserLogout"                   , ReqUserLogout                      );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqUserPasswordUpdate"           , ReqUserPasswordUpdate              );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqTradingAccountPasswordUpdate" , ReqTradingAccountPasswordUpdate    );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqOrderInsert"                  , ReqOrderInsert                     );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqParkedOrderInsert"            , ReqParkedOrderInsert               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqParkedOrderAction"            , ReqParkedOrderAction               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqOrderAction"                  , ReqOrderAction                     );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQueryMaxOrderVolume"          , ReqQueryMaxOrderVolume             );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqSettlementInfoConfirm"        , ReqSettlementInfoConfirm           );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqRemoveParkedOrder"            , ReqRemoveParkedOrder               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqRemoveParkedOrderAction"      , ReqRemoveParkedOrderAction         );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqExecOrderInsert"              , ReqExecOrderInsert                 );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqExecOrderAction"              , ReqExecOrderAction                 );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqForQuoteInsert"               , ReqForQuoteInsert                  );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQuoteInsert"                  , ReqQuoteInsert                     );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQuoteAction"                  , ReqQuoteAction                     );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqBatchOrderAction"             , ReqBatchOrderAction                );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqCombActionInsert"             , ReqCombActionInsert                );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryOrder"                     , ReqQryOrder                        );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryTrade"                     , ReqQryTrade                        );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryInvestorPosition"          , ReqQryInvestorPosition             );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryTradingAccount"            , ReqQryTradingAccount               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryInvestor"                  , ReqQryInvestor                     );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryTradingCode"               , ReqQryTradingCode                  );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryInstrumentMarginRate"      , ReqQryInstrumentMarginRate         );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryInstrumentCommissionRate"  , ReqQryInstrumentCommissionRate     );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryExchange"                  , ReqQryExchange                     );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryProduct"                   , ReqQryProduct                      );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryInstrument"                , ReqQryInstrument                   );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryDepthMarketData"           , ReqQryDepthMarketData              );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQrySettlementInfo"            , ReqQrySettlementInfo               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryTransferBank"              , ReqQryTransferBank                 );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryInvestorPositionDetail"    , ReqQryInvestorPositionDetail       );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryNotice"                    , ReqQryNotice                       );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQrySettlementInfoConfirm"     , ReqQrySettlementInfoConfirm        );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryCFMMCTradingAccountKey"    , ReqQryCFMMCTradingAccountKey       );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryEWarrantOffset"            , ReqQryEWarrantOffset               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryInvestorProductGroupMargin", ReqQryInvestorProductGroupMargin   );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryExchangeMarginRate"        , ReqQryExchangeMarginRate           );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryExchangeMarginRateAdjust"  , ReqQryExchangeMarginRateAdjust     );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryExchangeRate"              , ReqQryExchangeRate                 );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQrySecAgentACIDMap"           , ReqQrySecAgentACIDMap              );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryProductExchRate"           , ReqQryProductExchRate              );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryProductGroup"              , ReqQryProductGroup                 );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryMMInstrumentCommissionRate", ReqQryMMInstrumentCommissionRate   );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryMMOptionInstrCommRate"     , ReqQryMMOptionInstrCommRate        );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryInstrumentOrderCommRate"   , ReqQryInstrumentOrderCommRate      );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryOptionInstrTradeCost"      , ReqQryOptionInstrTradeCost         );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryOptionInstrCommRate"       , ReqQryOptionInstrCommRate          );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryExecOrder"                 , ReqQryExecOrder                    );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryForQuote"                  , ReqQryForQuote                     );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryQuote"                     , ReqQryQuote                        );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryCombInstrumentGuard"       , ReqQryCombInstrumentGuard          );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryCombAction"                , ReqQryCombAction                   );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryTransferSerial"            , ReqQryTransferSerial               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryAccountregister"           , ReqQryAccountregister              );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryContractBank"              , ReqQryContractBank                 );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryParkedOrder"               , ReqQryParkedOrder                  );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryParkedOrderAction"         , ReqQryParkedOrderAction            );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryTradingNotice"             , ReqQryTradingNotice                );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryBrokerTradingParams"       , ReqQryBrokerTradingParams          );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryBrokerTradingAlgos"        , ReqQryBrokerTradingAlgos           );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQueryCFMMCTradingAccountToken", ReqQueryCFMMCTradingAccountToken   );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqFromBankToFutureByFuture"     , ReqFromBankToFutureByFuture        );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqFromFutureToBankByFuture"     , ReqFromFutureToBankByFuture        );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQueryBankAccountMoneyByFuture", ReqQueryBankAccountMoneyByFuture   );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQryInvestorPositionCombineDetail",ReqQryInvestorPositionCombineDetail);
    // TODO 穿透式监管新增主动请求接口
    NODE_SET_PROTOTYPE_METHOD(tpl, "registerUserSystemInfo"          , RegisterUserSystemInfo             );
    NODE_SET_PROTOTYPE_METHOD(tpl, "submitUserSystemInfo"            , SubmitUserSystemInfo               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqUserAuthMethod"               , ReqUserAuthMethod                  );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqGenUserCaptcha"               , ReqGenUserCaptcha                  );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqGenUserText"                  , ReqGenUserText                     );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqUserLoginWithCaptcha"         , ReqUserLoginWithCaptcha            );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqUserLoginWithText"            , ReqUserLoginWithText               );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqUserLoginWithOTP"             , ReqUserLoginWithOTP                );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQrySecAgentTradeInfo"         , ReqQrySecAgentTradeInfo            );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQrySecAgentTradingAccount"    , ReqQrySecAgentTradingAccount       );
    NODE_SET_PROTOTYPE_METHOD(tpl, "reqQrySecAgentCheckMode"         , ReqQrySecAgentCheckMode            );
    NODE_SET_PROTOTYPE_METHOD(tpl, "on", On);
    constructor.Reset(isolate, tpl->GetFunction());

    m_event.insert("FrontConnected")                          ;
    m_event.insert("FrontDisconnected")                       ;
    m_event.insert("HeartBeatWarning")                        ;
    m_event.insert("RspAuthenticate")                         ;
    m_event.insert("RspUserLogin")                            ;
    m_event.insert("RspUserLogout")                           ;
    m_event.insert("RspUserPasswordUpdate")                   ;
    m_event.insert("RspTradingAccountPasswordUpdate")         ;
    m_event.insert("RspOrderInsert")                          ;
    m_event.insert("RspParkedOrderInsert")                    ;
    m_event.insert("RspParkedOrderAction")                    ;
    m_event.insert("RspOrderAction")                          ;
    m_event.insert("RspQueryMaxOrderVolume")                  ;
    m_event.insert("RspSettlementInfoConfirm")                ;
    m_event.insert("RspRemoveParkedOrder")                    ;
    m_event.insert("RspRemoveParkedOrderAction")              ;
    m_event.insert("RspExecOrderInsert")                      ;
    m_event.insert("RspExecOrderAction")                      ;
    m_event.insert("RspForQuoteInsert")                       ;
    m_event.insert("RspQuoteInsert")                          ;
    m_event.insert("RspQuoteAction")                          ;
    m_event.insert("RspBatchOrderAction")                     ;
    m_event.insert("RspCombActionInsert")                     ;
    m_event.insert("RspQryOrder")                             ;
    m_event.insert("RspQryTrade")                             ;
    m_event.insert("RspQryInvestorPosition")                  ;
    m_event.insert("RspQryTradingAccount")                    ;
    m_event.insert("RspQryInvestor")                          ;
    m_event.insert("RspQryTradingCode")                       ;
    m_event.insert("RspQryInstrumentMarginRate")              ;
    m_event.insert("RspQryInstrumentCommissionRate")          ;
    m_event.insert("RspQryExchange")                          ;
    m_event.insert("RspQryProduct")                           ;
    m_event.insert("RspQryInstrument")                        ;
    m_event.insert("RspQryDepthMarketData")                   ;
    m_event.insert("RspQrySettlementInfo")                    ;
    m_event.insert("RspQryTransferBank")                      ;
    m_event.insert("RspQryInvestorPositionDetail")            ;
    m_event.insert("RspQryNotice")                            ;
    m_event.insert("RspQrySettlementInfoConfirm")             ;
    m_event.insert("RspQryInvestorPositionCombineDetail")     ;
    m_event.insert("RspQryCFMMCTradingAccountKey")            ;
    m_event.insert("RspQryEWarrantOffset")                    ;
    m_event.insert("RspQryInvestorProductGroupMargin")        ;
    m_event.insert("RspQryExchangeMarginRate")                ;
    m_event.insert("RspQryExchangeMarginRateAdjust")          ;
    m_event.insert("RspQryExchangeRate")                      ;
    m_event.insert("RspQrySecAgentACIDMap")                   ;
    m_event.insert("RspQryProductExchRate")                   ;
    m_event.insert("RspQryProductGroup")                      ;
    m_event.insert("RspQryMMInstrumentCommissionRate")        ;
    m_event.insert("RspQryMMOptionInstrCommRate")             ;
    m_event.insert("RspQryInstrumentOrderCommRate")           ;
    m_event.insert("RspQryOptionInstrTradeCost")              ;
    m_event.insert("RspQryOptionInstrCommRate")               ;
    m_event.insert("RspQryExecOrder")                         ;
    m_event.insert("RspQryForQuote")                          ;
    m_event.insert("RspQryQuote")                             ;
    m_event.insert("RspQryCombInstrumentGuard")               ;
    m_event.insert("RspQryCombAction")                        ;
    m_event.insert("RspQryTransferSerial")                    ;
    m_event.insert("RspQryAccountregister")                   ;
    m_event.insert("RspError")                                ;
    m_event.insert("RtnOrder")                                ;
    m_event.insert("RtnTrade")                                ;
    m_event.insert("ErrRtnOrderInsert")                       ;
    m_event.insert("ErrRtnOrderAction")                       ;
    m_event.insert("RtnInstrumentStatus")                     ;
    m_event.insert("RtnBulletin")                             ;
    m_event.insert("RtnTradingNotice")                        ;
    m_event.insert("RtnErrorConditionalOrder")                ;
    m_event.insert("RtnExecOrder")                            ;
    m_event.insert("ErrRtnExecOrderInsert")                   ;
    m_event.insert("ErrRtnExecOrderAction")                   ;
    m_event.insert("ErrRtnForQuoteInsert")                    ;
    m_event.insert("RtnQuote")                                ;
    m_event.insert("ErrRtnQuoteInsert")                       ;
    m_event.insert("ErrRtnQuoteAction")                       ;
    m_event.insert("RtnForQuoteRsp")                          ;
    m_event.insert("RtnCFMMCTradingAccountToken")             ;
    m_event.insert("ErrRtnBatchOrderAction")                  ;
    m_event.insert("RtnCombAction")                           ;
    m_event.insert("ErrRtnCombActionInsert")                  ;
    m_event.insert("RspQryContractBank")                      ;
    m_event.insert("RspQryParkedOrder")                       ;
    m_event.insert("RspQryParkedOrderAction")                 ;
    m_event.insert("RspQryTradingNotice")                     ;
    m_event.insert("RspQryBrokerTradingParams")               ;
    m_event.insert("RspQryBrokerTradingAlgos")                ;
    m_event.insert("RspQueryCFMMCTradingAccountToken")        ;
    m_event.insert("RtnFromBankToFutureByBank")               ;
    m_event.insert("RtnFromFutureToBankByBank")               ;
    m_event.insert("RtnRepealFromBankToFutureByBank")         ;
    m_event.insert("RtnRepealFromFutureToBankByBank")         ;
    m_event.insert("RtnFromBankToFutureByFuture")             ;
    m_event.insert("RtnFromFutureToBankByFuture")             ;
    m_event.insert("RtnRepealFromBankToFutureByFutureManual") ;
    m_event.insert("RtnRepealFromFutureToBankByFutureManual") ;
    m_event.insert("RtnQueryBankBalanceByFuture")             ;
    m_event.insert("ErrRtnBankToFutureByFuture")              ;
    m_event.insert("ErrRtnFutureToBankByFuture")              ;
    m_event.insert("ErrRtnRepealBankToFutureByFutureManual")  ;
    m_event.insert("ErrRtnRepealFutureToBankByFutureManual")  ;
    m_event.insert("ErrRtnQueryBankBalanceByFuture")          ;
    m_event.insert("RtnRepealFromBankToFutureByFuture")       ;
    m_event.insert("RtnRepealFromFutureToBankByFuture")       ;
    m_event.insert("RspFromBankToFutureByFuture")             ;
    m_event.insert("RspFromFutureToBankByFuture")             ;
    m_event.insert("RspQueryBankAccountMoneyByFuture")        ;
    m_event.insert("RtnOpenAccountByBank")                    ;
    m_event.insert("RtnCancelAccountByBank")                  ;
    m_event.insert("RtnChangeAccountByBank")                  ;
    // TODO 穿透式监管新增响应接口
    m_event.insert("RspUserAuthMethod")                       ;
    m_event.insert("RspGenUserCaptcha")                       ;
    m_event.insert("RspGenUserText")                          ;
    m_event.insert("RspQrySecAgentTradeInfo")                 ;
    m_event.insert("RspQrySecAgentTradingAccount")            ;
    m_event.insert("RspQrySecAgentCheckMode")                 ;
}

void WrapTd::New(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    if(args.IsConstructCall())
    {
        // Invoked as constructor: `new MyObject(...)`
        WrapTd* obj = new WrapTd();
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

void WrapTd::NewInstance(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    Local<Context> context = isolate->GetCurrentContext();
    Local<Object> instance  = cons->NewInstance(context, 0, NULL).ToLocalChecked();
    args.GetReturnValue().Set(instance);
}

void WrapTd::On(const FunctionCallbackInfo<Value>& args)
{
    Isolate* isolate = args.GetIsolate();
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());

    if (args[0]->IsUndefined() || args[1]->IsUndefined())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments->event name or function")));
        return;
    }

    //WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());

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

void WrapTd::GetApiVersion(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    const char* v = obj->GetTdApi()->GetApiVersion();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, v));
}

void WrapTd::GetTradingDay(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    const char* t = obj->GetTdApi()->GetTradingDay();
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, t));
}

void WrapTd::Init(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    obj->GetTdApi()->Init();
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapTd::Release(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    obj->GetTdApi()->Release();
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapTd::Dispose(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    obj->dispose();
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapTd::CreateFtdcTraderApi(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined())
    {
        args[0] = String::NewFromUtf8(isolate, "");
    }
    Local<String> flowpath = args[0]->ToString();
    String::Utf8Value p(flowpath);

    CThostFtdcTraderApi* m_pApi = CThostFtdcTraderApi::CreateFtdcTraderApi((char*)*p);

    obj->setTdApi(m_pApi);
    obj->RegisterSpi();
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapTd::RegisterFront(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    Local<String> url = args[0]->ToString();
    String::Utf8Value u(url);

    obj->GetTdApi()->RegisterFront((char*)*u);
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapTd::RegisterNameServer(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    Local<String> url = args[0]->ToString();
    String::Utf8Value u(url);

    obj->GetTdApi()->RegisterNameServer((char*)*u);
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapTd::RegisterFensUserInfo(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined() || !args[0]->IsObject())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    Local<Object> objjs = args[0]->ToObject();
    CThostFtdcFensUserInfoField req;
    CSFunction::set_struct(objjs, &req);
    obj->GetTdApi()->RegisterFensUserInfo(&req);
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapTd::SubscribePrivateTopic(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    obj->GetTdApi()->SubscribePrivateTopic((THOST_TE_RESUME_TYPE)args[0]->Int32Value());
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapTd::SubscribePublicTopic(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    obj->GetTdApi()->SubscribePublicTopic((THOST_TE_RESUME_TYPE)args[0]->Int32Value());
    args.GetReturnValue().Set(Undefined(isolate));
}

#define REQ_WITH_REQID(req) \
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());\
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

void WrapTd::ReqAuthenticate(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcReqAuthenticateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqAuthenticate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqUserLogin(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcReqUserLoginField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqUserLogin(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqUserLogout(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcUserLogoutField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqUserLogout(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqUserPasswordUpdate(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcUserPasswordUpdateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqUserPasswordUpdate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqTradingAccountPasswordUpdate(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcTradingAccountPasswordUpdateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqTradingAccountPasswordUpdate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryTradingAccount(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcQryTradingAccountField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryTradingAccount(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

//查询持仓信息
void WrapTd::ReqQryInvestorPosition(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcQryInvestorPositionField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryInvestorPosition(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

//查询成交流水
void WrapTd::ReqQryTrade(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryTradeField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryTrade(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

//查询订单流水
void WrapTd::ReqQryOrder(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryOrderField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryOrder(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

//持仓明细
void WrapTd::ReqQryInvestorPositionDetail(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryInvestorPositionDetailField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryInvestorPositionDetail(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

//查询合约
void  WrapTd::ReqQryInstrument(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryInstrumentField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryInstrument(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

//查询产品
void  WrapTd::ReqQryProduct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryProductField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryProduct(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void	WrapTd::ReqSettlementInfoConfirm(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcSettlementInfoConfirmField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqSettlementInfoConfirm(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqOrderInsert(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcInputOrderField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqOrderInsert(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqOrderAction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcInputOrderActionField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqOrderAction(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqParkedOrderInsert(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcParkedOrderField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqParkedOrderInsert(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqParkedOrderAction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcParkedOrderActionField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqParkedOrderAction(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQueryMaxOrderVolume(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQueryMaxOrderVolumeField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQueryMaxOrderVolume(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqRemoveParkedOrder(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcRemoveParkedOrderField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqRemoveParkedOrder(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}
void WrapTd::ReqRemoveParkedOrderAction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcRemoveParkedOrderActionField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqRemoveParkedOrderAction(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}
void WrapTd::ReqExecOrderInsert(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcInputExecOrderField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqExecOrderInsert(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}
void WrapTd::ReqExecOrderAction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcInputExecOrderActionField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqExecOrderAction(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}
void WrapTd::ReqForQuoteInsert(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcInputForQuoteField  req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqForQuoteInsert(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}
void WrapTd::ReqQuoteInsert(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcInputQuoteField  req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQuoteInsert(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}
void WrapTd::ReqQuoteAction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcInputQuoteActionField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQuoteAction(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}
void WrapTd::ReqBatchOrderAction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
   CThostFtdcInputBatchOrderActionField req;
   REQ_WITH_REQID(req);
   int r = obj->GetTdApi()->ReqBatchOrderAction(&req, reqid);
   args.GetReturnValue().Set(Int32::New(isolate, r));
}
void WrapTd::ReqCombActionInsert(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcInputCombActionField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqCombActionInsert(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryInvestor(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryInvestorField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryInvestor(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryTradingCode(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryTradingCodeField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryTradingCode(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryInstrumentMarginRate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryInstrumentMarginRateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryInstrumentMarginRate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryInstrumentCommissionRate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryInstrumentCommissionRateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryInstrumentCommissionRate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryExchange(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryExchangeField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryExchange(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryDepthMarketData(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryDepthMarketDataField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryDepthMarketData(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQrySettlementInfo(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQrySettlementInfoField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQrySettlementInfo(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryTransferBank(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryTransferBankField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryTransferBank(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryNotice(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryNoticeField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryNotice(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQrySettlementInfoConfirm(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQrySettlementInfoConfirmField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQrySettlementInfoConfirm(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryInvestorPositionCombineDetail(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryInvestorPositionCombineDetailField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryInvestorPositionCombineDetail(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryCFMMCTradingAccountKey(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryCFMMCTradingAccountKeyField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryCFMMCTradingAccountKey(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryEWarrantOffset(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryEWarrantOffsetField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryEWarrantOffset(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryInvestorProductGroupMargin(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryInvestorProductGroupMarginField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryInvestorProductGroupMargin(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryExchangeMarginRate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryExchangeMarginRateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryExchangeMarginRate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryExchangeMarginRateAdjust(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryExchangeMarginRateAdjustField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryExchangeMarginRateAdjust(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryExchangeRate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryExchangeRateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryExchangeRate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQrySecAgentACIDMap(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQrySecAgentACIDMapField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQrySecAgentACIDMap(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryProductExchRate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryProductExchRateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryProductExchRate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryProductGroup(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryProductGroupField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryProductGroup(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryMMInstrumentCommissionRate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryMMInstrumentCommissionRateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryMMInstrumentCommissionRate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryMMOptionInstrCommRate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryMMOptionInstrCommRateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryMMOptionInstrCommRate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryInstrumentOrderCommRate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryInstrumentOrderCommRateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryInstrumentOrderCommRate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryOptionInstrTradeCost(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryOptionInstrTradeCostField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryOptionInstrTradeCost(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryOptionInstrCommRate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryOptionInstrCommRateField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryOptionInstrCommRate(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryExecOrder(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryExecOrderField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryExecOrder(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryForQuote(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryForQuoteField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryForQuote(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryQuote(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryQuoteField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryQuote(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryCombInstrumentGuard(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryCombInstrumentGuardField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryCombInstrumentGuard(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryCombAction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryCombActionField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryCombAction(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryTransferSerial(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryTransferSerialField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryTransferSerial(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryAccountregister(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryAccountregisterField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryAccountregister(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryContractBank(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryContractBankField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryContractBank(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryParkedOrder(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryParkedOrderField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryParkedOrder(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryParkedOrderAction(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryParkedOrderActionField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryParkedOrderAction(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryTradingNotice(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryTradingNoticeField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryTradingNotice(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryBrokerTradingParams(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryBrokerTradingParamsField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryBrokerTradingParams(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQryBrokerTradingAlgos(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQryBrokerTradingAlgosField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQryBrokerTradingAlgos(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQueryCFMMCTradingAccountToken(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcQueryCFMMCTradingAccountTokenField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQueryCFMMCTradingAccountToken(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqFromBankToFutureByFuture(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcReqTransferField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqFromBankToFutureByFuture(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqFromFutureToBankByFuture(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcReqTransferField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqFromFutureToBankByFuture(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQueryBankAccountMoneyByFuture(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    CThostFtdcReqQueryAccountField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQueryBankAccountMoneyByFuture(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

// TODO 穿透式监管新增主动请求接口
void WrapTd::RegisterUserSystemInfo(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined() || !args[0]->IsObject())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    Local<Object> objjs = args[0]->ToObject();
    CThostFtdcUserSystemInfoField req;
    CSFunction::set_struct(objjs, &req);
    obj->GetTdApi()->RegisterUserSystemInfo(&req);
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapTd::SubmitUserSystemInfo(const FunctionCallbackInfo<Value>& args)
{
    WrapTd* obj = node::ObjectWrap::Unwrap<WrapTd>(args.Holder());
    Isolate* isolate = args.GetIsolate();
    if (args[0]->IsUndefined() || !args[0]->IsObject())
    {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
        return;
    }
    Local<Object> objjs = args[0]->ToObject();
    CThostFtdcUserSystemInfoField req;
    CSFunction::set_struct(objjs, &req);
    obj->GetTdApi()->SubmitUserSystemInfo(&req);
    args.GetReturnValue().Set(Undefined(isolate));
}

void WrapTd::ReqUserAuthMethod(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcReqUserAuthMethodField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqUserAuthMethod(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqGenUserCaptcha(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcReqGenUserCaptchaField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqGenUserCaptcha(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqGenUserText(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcReqGenUserTextField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqGenUserText(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqUserLoginWithCaptcha(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcReqUserLoginWithCaptchaField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqUserLoginWithCaptcha(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqUserLoginWithText(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcReqUserLoginWithTextField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqUserLoginWithText(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqUserLoginWithOTP(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcReqUserLoginWithOTPField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqUserLoginWithOTP(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQrySecAgentTradeInfo(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcQrySecAgentTradeInfoField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQrySecAgentTradeInfo(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQrySecAgentTradingAccount(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcQryTradingAccountField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQrySecAgentTradingAccount(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

void WrapTd::ReqQrySecAgentCheckMode(const FunctionCallbackInfo<Value>& args)
{
    CThostFtdcQrySecAgentCheckModeField req;
    REQ_WITH_REQID(req);
    int r = obj->GetTdApi()->ReqQrySecAgentCheckMode(&req, reqid);
    args.GetReturnValue().Set(Int32::New(isolate, r));
}

////////////////////////////////ctp on 回调////////////////////////////////////////////////
#define CONTEXT() \
Isolate* isolate = Isolate::GetCurrent();\
HandleScope scope(isolate);\
string k = string(_FUNCTION_).substr(6);\
__callback_iter_type it = callback_map.find(k);\
if(it == callback_map.end()) return;

void WrapTd::MainOnFrontConnected()
{
    CONTEXT()
    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 0, NULL);
}

void WrapTd::MainOnFrontDisconnected(int nReason)
{
    CONTEXT()
    Local<Value> argv[1] = { Local<Value>::New(isolate, Int32::New(isolate, nReason)) };
    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 1, argv);
}

void WrapTd::MainOnHeartBeatWarning(int nTimeLapse)
{
    CONTEXT()
    Local<Value> argv[1] = { Local<Value>::New(isolate, Int32::New(isolate, nTimeLapse)) };
    Local<Function> cb = Local<Function>::New(isolate, it->second);
    cb->Call(Null(isolate), 1, argv);
}

#define CONTEXT_WITH_1(rsp) \
Isolate* isolate = Isolate::GetCurrent();\
HandleScope scope(isolate);\
string k = string(_FUNCTION_).substr(6);\
__callback_iter_type it = callback_map.find(k);\
if(it == callback_map.end()) return;\
Local<Value> argv[1];\
if(rsp != NULL)\
{\
    Local<Object> obj = Object::New(isolate);\
    CSFunction::set_obj(obj, rsp);\
    argv[0] = obj;\
}\
else\
{\
    argv[0] = Local<Value>::New(isolate, Undefined(isolate));\
}\
Local<Function> cb = Local<Function>::New(isolate, it->second);\
cb->Call(Null(isolate), 1, argv);

#define CONTEXT_WITH_2(rsp) \
Isolate* isolate = Isolate::GetCurrent();\
HandleScope scope(isolate);\
string k = string(_FUNCTION_).substr(6);\
__callback_iter_type it = callback_map.find(k);\
if(it == callback_map.end()) return;\
Local<Value> argv[2];\
if(rsp != NULL)\
{\
    Local<Object> obj = Object::New(isolate);\
    CSFunction::set_obj(obj, rsp);\
    argv[0] = obj;\
}\
else\
{\
    argv[0] = Local<Value>::New(isolate, Undefined(isolate));\
}\
argv[1] = PkgRspInfo(pRspInfo);\
Local<Function> cb = Local<Function>::New(isolate, it->second);\
cb->Call(Null(isolate), 2, argv);


#define CONTEXT_WITH_4(rsp) do{\
Isolate* isolate = Isolate::GetCurrent();\
HandleScope scope(isolate);\
string k = string(_FUNCTION_).substr(6);\
__callback_iter_type it = callback_map.find(k);\
if(it == callback_map.end()) return;\
Local<Value> argv[4];\
if(rsp != NULL)\
{\
    Local<Object> obj = Object::New(isolate);\
    CSFunction::set_obj(obj, rsp);\
    argv[0] = obj;\
}\
else\
{\
    argv[0] = Local<Value>::New(isolate, Undefined(isolate));\
}\
argv[1] = PkgRspInfo(pRspInfo);\
argv[2] = Local<Value>::New(isolate, Int32::New(isolate, nRequestID));\
argv[3] = Boolean::New(isolate, bIsLast)->ToBoolean();\
Local<Function> cb = Local<Function>::New(isolate, it->second);\
cb->Call(Null(isolate), 4, argv);\
}while(0);

#define CONTEXT_WITH_LAST_3() \
Isolate* isolate = Isolate::GetCurrent();\
HandleScope scope(isolate);\
string k = string(_FUNCTION_).substr(6);\
__callback_iter_type it = callback_map.find(k);\
if(it == callback_map.end()) return;\
Local<Value> argv[3];\
argv[0] = PkgRspInfo(pRspInfo);\
argv[1] = Local<Value>::New(isolate, Int32::New(isolate, nRequestID));\
argv[2] = Boolean::New(isolate, bIsLast)->ToBoolean();\
Local<Function> cb = Local<Function>::New(isolate, it->second);\
cb->Call(Null(isolate), 3, argv);


//客户认证 认证失败重新登录
void WrapTd::MainOnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pRspAuthenticateField);
}

void WrapTd::MainOnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pRspUserLogin);
}

void WrapTd::MainOnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pUserLogout);
}


void WrapTd::MainOnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pUserPasswordUpdate);
}


void WrapTd::MainOnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pTradingAccountPasswordUpdate);
}

void WrapTd::MainOnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pInputOrder);
}

void WrapTd::MainOnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///预埋单录入请求响应
    CONTEXT_WITH_4(pParkedOrder);
}

void WrapTd::MainOnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///预埋撤单录入请求响应
    CONTEXT_WITH_4(pParkedOrderAction);
}

void WrapTd::MainOnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pInputOrderAction);
}


void WrapTd::MainOnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///查询最大报单数量响应
    CONTEXT_WITH_4(pQueryMaxOrderVolume);
}

void WrapTd::MainOnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pSettlementInfoConfirm);
}


void WrapTd::MainOnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///删除预埋单响应
    CONTEXT_WITH_4(pRemoveParkedOrder);
}

void WrapTd::MainOnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///删除预埋撤单响应
    CONTEXT_WITH_4(pRemoveParkedOrderAction);
}

void WrapTd::MainOnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///执行宣告录入请求响应
    CONTEXT_WITH_4(pInputExecOrder);
}

void WrapTd::MainOnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///执行宣告操作请求响应
    CONTEXT_WITH_4(pInputExecOrderAction);
}

void WrapTd::MainOnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///询价录入请求响应
    CONTEXT_WITH_4(pInputForQuote);
}

void WrapTd::MainOnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///报价录入请求响应
    CONTEXT_WITH_4(pInputQuote);
}

void WrapTd::MainOnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///报价操作请求响应
    CONTEXT_WITH_4(pInputQuoteAction);
}

void WrapTd::MainOnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///批量报单操作请求响应
    CONTEXT_WITH_4(pInputBatchOrderAction);
}
void WrapTd::MainOnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///申请组合录入请求响应
    CONTEXT_WITH_4(pInputCombAction);
}

void WrapTd::MainOnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pOrder);
}

void WrapTd::MainOnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pTrade);
}


void WrapTd::MainOnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pInvestorPosition);
}


void WrapTd::MainOnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pTradingAccount);
}

void WrapTd::MainOnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询投资者响应
    CONTEXT_WITH_4(pInvestor);

}

void WrapTd::MainOnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询交易编码响应
    CONTEXT_WITH_4(pTradingCode);
}

void WrapTd::MainOnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询合约保证金率响应
    CONTEXT_WITH_4(pInstrumentMarginRate);
}

void WrapTd::MainOnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询合约手续费率响应
    CONTEXT_WITH_4(pInstrumentCommissionRate);
}

void WrapTd::MainOnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询交易所响应
    CONTEXT_WITH_4(pExchange);
}

void WrapTd::MainOnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pProduct);
}


void WrapTd::MainOnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    CONTEXT_WITH_4(pInstrument);
}

void WrapTd::MainOnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询行情响应
    CONTEXT_WITH_4(pDepthMarketData);

}

void WrapTd::MainOnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询投资者结算结果响应
    CONTEXT_WITH_4(pSettlementInfo);
}

void WrapTd::MainOnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询转帐银行响应
    CONTEXT_WITH_4(pTransferBank);

}

void WrapTd::MainOnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

    CONTEXT_WITH_4(pInvestorPositionDetail);
}

void WrapTd::MainOnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询客户通知响应
    CONTEXT_WITH_4(pNotice);
}

void WrapTd::MainOnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询结算信息确认响应
    CONTEXT_WITH_4(pSettlementInfoConfirm);
}

void WrapTd::MainOnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询投资者持仓明细响应
    CONTEXT_WITH_4(pInvestorPositionCombineDetail);
}

void WrapTd::MainOnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///查询保证金监管系统经纪公司资金账户密钥响应
    CONTEXT_WITH_4(pCFMMCTradingAccountKey);
}

void WrapTd::MainOnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询仓单折抵信息响应
    CONTEXT_WITH_4(pEWarrantOffset);
}

void WrapTd::MainOnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询投资者品种/跨品种保证金响应
    CONTEXT_WITH_4(pInvestorProductGroupMargin);
}

void WrapTd::MainOnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询交易所保证金率响应
    CONTEXT_WITH_4(pExchangeMarginRate);
}

void WrapTd::MainOnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询交易所调整保证金率响应
    CONTEXT_WITH_4(pExchangeMarginRateAdjust);
}

void WrapTd::MainOnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询汇率响应
    CONTEXT_WITH_4(pExchangeRate);
}

void WrapTd::MainOnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询二级代理操作员银期权限响应
    CONTEXT_WITH_4(pSecAgentACIDMap);
}

void WrapTd::MainOnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询产品报价汇率
    CONTEXT_WITH_4(pProductExchRate);
}

void WrapTd::MainOnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询产品组
    CONTEXT_WITH_4(pProductGroup);
}

void WrapTd::MainOnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询做市商合约手续费率响应
    CONTEXT_WITH_4(pMMInstrumentCommissionRate);
}

void WrapTd::MainOnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询做市商期权合约手续费响应
    CONTEXT_WITH_4(pMMOptionInstrCommRate);
}

void WrapTd::MainOnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询报单手续费响应
    CONTEXT_WITH_4(pInstrumentOrderCommRate);
}

void WrapTd::MainOnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询期权交易成本响应
    CONTEXT_WITH_4(pOptionInstrTradeCost);
}

void WrapTd::MainOnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询期权合约手续费响应
    CONTEXT_WITH_4(pOptionInstrCommRate);
}

void WrapTd::MainOnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询执行宣告响应
    CONTEXT_WITH_4(pExecOrder);
}

void WrapTd::MainOnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询询价响应
    CONTEXT_WITH_4(pForQuote);
}

void WrapTd::MainOnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询报价响应
    CONTEXT_WITH_4(pQuote);
}

void WrapTd::MainOnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询组合合约安全系数响应
    CONTEXT_WITH_4(pCombInstrumentGuard);
}

void WrapTd::MainOnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询申请组合响应
    CONTEXT_WITH_4(pCombAction);
}

void WrapTd::MainOnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询转帐流水响应
    CONTEXT_WITH_4(pTransferSerial);
}

void WrapTd::MainOnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询银期签约关系响应
    CONTEXT_WITH_4(pAccountregister);
}

void WrapTd::MainOnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///错误应答
    CONTEXT_WITH_LAST_3();
}

void WrapTd::MainOnRtnOrder(CThostFtdcOrderField *pOrder)
{
    CONTEXT_WITH_1(pOrder);
}

void WrapTd::MainOnRtnTrade(CThostFtdcTradeField *pTrade)
{
    CONTEXT_WITH_1(pTrade);
}

void WrapTd::MainOnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
    CONTEXT_WITH_2(pInputOrder);
}


void WrapTd::MainOnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    CONTEXT_WITH_2(pOrderAction);
}


void WrapTd::MainOnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
    ///合约交易状态通知
    CONTEXT_WITH_1(pInstrumentStatus);
}

void WrapTd::MainOnRtnBulletin(CThostFtdcBulletinField *pBulletin)
{
    ///交易所公告通知
    CONTEXT_WITH_1(pBulletin);
}

void WrapTd::MainOnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
    ///交易通知
    CONTEXT_WITH_1(pTradingNoticeInfo);
}

void WrapTd::MainOnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder)
{
    ///提示条件单校验错误
    CONTEXT_WITH_1(pErrorConditionalOrder);
}

void WrapTd::MainOnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)
{
    ///执行宣告通知
    CONTEXT_WITH_1(pExecOrder);
}

void WrapTd::MainOnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo)
{
    ///执行宣告录入错误回报
    CONTEXT_WITH_2(pInputExecOrder);
}

void WrapTd::MainOnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    ///执行宣告操作错误回报
    CONTEXT_WITH_2(pExecOrderAction);
}

void WrapTd::MainOnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo)
{
    ///询价录入错误回报
    CONTEXT_WITH_2(pInputForQuote);
}

void WrapTd::MainOnRtnQuote(CThostFtdcQuoteField *pQuote)
{
    ///报价通知
    CONTEXT_WITH_1(pQuote);
}

void WrapTd::MainOnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)
{
    ///报价录入错误回报
    CONTEXT_WITH_2(pInputQuote);
}

void WrapTd::MainOnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)
{
    ///报价操作错误回报
    CONTEXT_WITH_2(pQuoteAction);
}

void WrapTd::MainOnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
    ///询价通知
    CONTEXT_WITH_1(pForQuoteRsp);
}

void WrapTd::MainOnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken)
{
    ///保证金监控中心用户令牌
    CONTEXT_WITH_1(pCFMMCTradingAccountToken);
}
void WrapTd::MainOnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
    ///批量报单操作错误回报
    CONTEXT_WITH_2(pBatchOrderAction);
}
void WrapTd::MainOnRtnCombAction(CThostFtdcCombActionField *pCombAction)
{
    ///申请组合通知
    CONTEXT_WITH_1(pCombAction);
}

void WrapTd::MainOnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo)
{
    ///申请组合录入错误回报
    CONTEXT_WITH_2(pInputCombAction);
}

void WrapTd::MainOnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询签约银行响应
    CONTEXT_WITH_4(pContractBank);
}

void WrapTd::MainOnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询预埋单响应
    CONTEXT_WITH_4(pParkedOrder);
}

void WrapTd::MainOnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询预埋撤单响应
    CONTEXT_WITH_4(pParkedOrderAction);
}

void WrapTd::MainOnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询交易通知响应
    CONTEXT_WITH_4(pTradingNotice);
}

void WrapTd::MainOnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询经纪公司交易参数响应
    CONTEXT_WITH_4(pBrokerTradingParams);
}

void WrapTd::MainOnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询经纪公司交易算法响应
    CONTEXT_WITH_4(pBrokerTradingAlgos);
}

void WrapTd::MainOnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询监控中心用户令牌
    CONTEXT_WITH_4(pQueryCFMMCTradingAccountToken);
}

void WrapTd::MainOnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer)
{
    ///银行发起银行资金转期货通知
    CONTEXT_WITH_1(pRspTransfer);
}

void WrapTd::MainOnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer)
{
    ///银行发起期货资金转银行通知
    CONTEXT_WITH_1(pRspTransfer);
}

void WrapTd::MainOnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal)
{
    ///银行发起冲正银行转期货通知
    CONTEXT_WITH_1(pRspRepeal);
}

void WrapTd::MainOnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal)
{
    ///银行发起冲正期货转银行通知
    CONTEXT_WITH_1(pRspRepeal);
}

void WrapTd::MainOnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
    ///期货发起银行资金转期货通知
    CONTEXT_WITH_1(pRspTransfer);
}

void WrapTd::MainOnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
    ///期货发起期货资金转银行通知
    CONTEXT_WITH_1(pRspTransfer);
}

void WrapTd::MainOnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal)
{
    ///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
    CONTEXT_WITH_1(pRspRepeal);
}

void WrapTd::MainOnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal)
{
    ///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
    CONTEXT_WITH_1(pRspRepeal);
}

void WrapTd::MainOnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount)
{
    ///期货发起查询银行余额通知
    CONTEXT_WITH_1(pNotifyQueryAccount);
}

void WrapTd::MainOnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)
{
    ///期货发起银行资金转期货错误回报
    CONTEXT_WITH_2(pReqTransfer);
}

void WrapTd::MainOnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)
{
    ///期货发起期货资金转银行错误回报
    CONTEXT_WITH_2(pReqTransfer);
}

void WrapTd::MainOnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)
{
    ///系统运行时期货端手工发起冲正银行转期货错误回报
    CONTEXT_WITH_2(pReqRepeal);
}

void WrapTd::MainOnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)
{
    ///系统运行时期货端手工发起冲正期货转银行错误回报
    CONTEXT_WITH_2(pReqRepeal);
}

void WrapTd::MainOnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo)
{
    ///期货发起查询银行余额错误回报
    CONTEXT_WITH_2(pReqQueryAccount);
}

void WrapTd::MainOnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal)
{
    ///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
    CONTEXT_WITH_1(pRspRepeal);
}

void WrapTd::MainOnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal)
{
    ///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
    CONTEXT_WITH_1(pRspRepeal);
}

void WrapTd::MainOnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///期货发起银行资金转期货应答
    CONTEXT_WITH_4(pReqTransfer);
}

void WrapTd::MainOnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///期货发起期货资金转银行应答
    CONTEXT_WITH_4(pReqTransfer);
}

void WrapTd::MainOnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///期货发起查询银行余额应答
    CONTEXT_WITH_4(pReqQueryAccount);
}

void WrapTd::MainOnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount)
{
    ///银行发起银期开户通知
    CONTEXT_WITH_1(pOpenAccount);
}

void WrapTd::MainOnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount)
{
    ///银行发起银期销户通知
    CONTEXT_WITH_1(pCancelAccount);
}

void WrapTd::MainOnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount)
{
    ///银行发起变更银行账号通知
    CONTEXT_WITH_1(pChangeAccount);
}

// TODO 穿透式监管新增响应接口
void WrapTd::MainOnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///查询用户当前支持的认证模式的回复
    CONTEXT_WITH_4(pRspUserAuthMethod);
}

void WrapTd::MainOnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///获取图形验证码请求的回复
    CONTEXT_WITH_4(pRspGenUserCaptcha);
}

void WrapTd::MainOnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///获取短信验证码请求的回复
    CONTEXT_WITH_4(pRspGenUserText);
}

void WrapTd::MainOnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询二级代理商信息响应
    CONTEXT_WITH_4(pSecAgentTradeInfo);
}

void WrapTd::MainOnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询资金账户响应
    CONTEXT_WITH_4(pTradingAccount);
}

void WrapTd::MainOnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    ///请求查询二级代理商资金校验模式响应
    CONTEXT_WITH_4(pSecAgentCheckMode);
}

}




