#ifndef __NODE_CTP__
#define __NODE_CTP__

#include <v8.h>
#include <string>
#include "ThostFtdcUserApiStruct.h"

using  v8::Local;
using  v8::Isolate;
using  v8::Object;
using  v8::String;
using  v8::Exception;
using  v8::Value;

class CSFunction
{

public:

#ifdef WIN32
#include <windows.h>
static string GBK2UTF8(string strGBK)
{
    string strOutUTF8 = "";
    WCHAR * str1;
    int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
    str1 = new WCHAR[n];
    MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
    char * str2 = new char[n];
    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
    strOutUTF8 = str2;
    delete[]str1;
    str1 = NULL;
    delete[]str2;
    str2 = NULL;
    return strOutUTF8;
}
#else
static string GBK2UTF8(string src)
{
    if(src.length() < 1) return "";
    size_t outlen = 4*src.length()+1;
    char* pout = new char[outlen];
    memset(pout, 0,  outlen);
    char* dest = pout;

    char * pin = (char*)src.c_str();
    size_t inlen = src.length();

    iconv_t conv = iconv_open("UTF-8", "GB2312"); // iconv_t conv = iconv_open("UTF-8", "GB2312");
    if(conv == 0) return "";
    iconv(conv, &pin, &inlen, &pout, &outlen);
    iconv_close(conv);

    string tmp = dest;
    delete dest;
    return tmp;
}
#endif

// set_struct是从js对象往ctp定义的结构赋值
// set_obj是从ctp定义的结构往js对象赋值

static void set_struct(Local<Object>& obj, const char* key, void* dest, int len)
{
    v8::Isolate* isolate  = v8::Isolate::GetCurrent();
    Local<Value> v = obj->Get(v8::String::NewFromUtf8(isolate, key));
    if (v->IsUndefined())
    {
        memset(dest, 0, len);
        //isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, string("Wrong arguments->") + key)));
        return ;
    }
    String::Utf8Value t(v);
    strncpy((char*)dest, (char*)*t, len);
    if(len>1) ((char*)dest)[len-1] = '0';
}

static void set_struct(Local<Object>& obj, const char* key, char* dest, int len)
{
    v8::Isolate* isolate  = v8::Isolate::GetCurrent();
    Local<Value> v = obj->Get(v8::String::NewFromUtf8(isolate, key));
    if (v->IsUndefined())
    {
        memset(dest, 0, len);
        //isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, string("Wrong arguments->") + key)));
        return ;
    }
    String::Utf8Value t(v);
    strncpy(dest, (char*)*t, len);
    if(len>1) dest[len-1] = '0';
}

static void set_struct(Local<Object>& obj, const char* key, int* dest, int len=0)
{
    v8::Isolate* isolate  = v8::Isolate::GetCurrent();
    Local<Value> v = obj->Get(v8::String::NewFromUtf8(isolate, key));
    if (v->IsUndefined())
    {
        dest = 0;
        //isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, string("Wrong arguments->") + key)));
        return ;
    }
    *dest = v->Int32Value();
}

static void set_struct(Local<Object>& obj, const char* key, double* dest, int len=0)
{
    v8::Isolate* isolate  = v8::Isolate::GetCurrent();
    Local<Value> v = obj->Get(v8::String::NewFromUtf8(isolate, key));
    if (v->IsUndefined() || !v->IsNumber())
    {
        dest = 0;
        //isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, string("Wrong arguments->") + key)));
        return ;
    }
    *dest = v->NumberValue();
}

static void set_struct(Local<Object>& obj, const char* key, float* dest, int len=0)
{
    v8::Isolate* isolate  = v8::Isolate::GetCurrent();
    Local<Value> v = obj->Get(v8::String::NewFromUtf8(isolate, key));
    if (v->IsUndefined() || !v->IsNumber())
    {
        dest = 0;
        //isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, string("Wrong arguments->") + key)));
        return ;
    }
    *dest = (float)v->NumberValue();
}


//处理ctp定义的字符数组指针类型
static void set_obj(v8::Local<v8::Object>& obj, const char* key, void* v)
{
    string u = GBK2UTF8((char*)v);
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), u.c_str()));
}


static void set_obj(v8::Local<v8::Object>& obj, const char* key, char* v)
{
    char s[2]= {0};
    s[0] = *v;
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), s));
}

static void set_obj(v8::Local<v8::Object>& obj, const char* key, int* v)
{
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::Int32::New(v8::Isolate::GetCurrent(), *v));
}

static void set_obj(v8::Local<v8::Object>& obj, const char* key, short int* v)
{
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::Int32::New(v8::Isolate::GetCurrent(), (int)*v));
}

static void set_obj(v8::Local<v8::Object>& obj, const char* key, float* v)
{
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::Number::New(v8::Isolate::GetCurrent(), *v));
}

static void set_obj(v8::Local<v8::Object>& obj, const char* key, double* v)
{
    obj->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), key), v8::Number::New(v8::Isolate::GetCurrent(), *v));
}
static void set_obj(Local<Object>& obj, CThostFtdcDisseminationField *p)
{
    set_obj(obj, "sequenceSeries", &p->SequenceSeries);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqUserLoginField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "interfaceProductInfo", &p->InterfaceProductInfo);
    set_obj(obj, "protocolInfo", &p->ProtocolInfo);
    set_obj(obj, "macAddress", &p->MacAddress);
    set_obj(obj, "oneTimePassword", &p->OneTimePassword);
    set_obj(obj, "clientIpAddress", &p->ClientIPAddress);
    set_obj(obj, "loginRemark", &p->LoginRemark);
    set_obj(obj, "clientIpPort", &p->ClientIPPort);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspUserLoginField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "loginTime", &p->LoginTime);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "systemName", &p->SystemName);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "maxOrderRef", &p->MaxOrderRef);
    set_obj(obj, "shfeTime", &p->SHFETime);
    set_obj(obj, "dceTime", &p->DCETime);
    set_obj(obj, "czceTime", &p->CZCETime);
    set_obj(obj, "ffexTime", &p->FFEXTime);
    set_obj(obj, "ineTime", &p->INETime);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserLogoutField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcForceUserLogoutField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqAuthenticateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "authCode", &p->AuthCode);
    set_obj(obj, "appId", &p->AppID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspAuthenticateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "appId", &p->AppID);
    set_obj(obj, "appType", &p->AppType);
}
static void set_obj(Local<Object>& obj, CThostFtdcAuthenticationInfoField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "authInfo", &p->AuthInfo);
    set_obj(obj, "isResult", &p->IsResult);
    set_obj(obj, "appId", &p->AppID);
    set_obj(obj, "appType", &p->AppType);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferHeaderField *p)
{
    set_obj(obj, "version", &p->Version);
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "tradeSerial", &p->TradeSerial);
    set_obj(obj, "futureId", &p->FutureID);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBrchId", &p->BankBrchID);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "recordNum", &p->RecordNum);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "requestId", &p->RequestID);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferBankToFutureReqField *p)
{
    set_obj(obj, "futureAccount", &p->FutureAccount);
    set_obj(obj, "futurePwdFlag", &p->FuturePwdFlag);
    set_obj(obj, "futureAccPwd", &p->FutureAccPwd);
    set_obj(obj, "tradeAmt", &p->TradeAmt);
    set_obj(obj, "custFee", &p->CustFee);
    set_obj(obj, "currencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferBankToFutureRspField *p)
{
    set_obj(obj, "retCode", &p->RetCode);
    set_obj(obj, "retInfo", &p->RetInfo);
    set_obj(obj, "futureAccount", &p->FutureAccount);
    set_obj(obj, "tradeAmt", &p->TradeAmt);
    set_obj(obj, "custFee", &p->CustFee);
    set_obj(obj, "currencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferFutureToBankReqField *p)
{
    set_obj(obj, "futureAccount", &p->FutureAccount);
    set_obj(obj, "futurePwdFlag", &p->FuturePwdFlag);
    set_obj(obj, "futureAccPwd", &p->FutureAccPwd);
    set_obj(obj, "tradeAmt", &p->TradeAmt);
    set_obj(obj, "custFee", &p->CustFee);
    set_obj(obj, "currencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferFutureToBankRspField *p)
{
    set_obj(obj, "retCode", &p->RetCode);
    set_obj(obj, "retInfo", &p->RetInfo);
    set_obj(obj, "futureAccount", &p->FutureAccount);
    set_obj(obj, "tradeAmt", &p->TradeAmt);
    set_obj(obj, "custFee", &p->CustFee);
    set_obj(obj, "currencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferQryBankReqField *p)
{
    set_obj(obj, "futureAccount", &p->FutureAccount);
    set_obj(obj, "futurePwdFlag", &p->FuturePwdFlag);
    set_obj(obj, "futureAccPwd", &p->FutureAccPwd);
    set_obj(obj, "currencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferQryBankRspField *p)
{
    set_obj(obj, "retCode", &p->RetCode);
    set_obj(obj, "retInfo", &p->RetInfo);
    set_obj(obj, "futureAccount", &p->FutureAccount);
    set_obj(obj, "tradeAmt", &p->TradeAmt);
    set_obj(obj, "useAmt", &p->UseAmt);
    set_obj(obj, "fetchAmt", &p->FetchAmt);
    set_obj(obj, "currencyCode", &p->CurrencyCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferQryDetailReqField *p)
{
    set_obj(obj, "futureAccount", &p->FutureAccount);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferQryDetailRspField *p)
{
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "futureSerial", &p->FutureSerial);
    set_obj(obj, "futureId", &p->FutureID);
    set_obj(obj, "futureAccount", &p->FutureAccount);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBrchId", &p->BankBrchID);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "certCode", &p->CertCode);
    set_obj(obj, "currencyCode", &p->CurrencyCode);
    set_obj(obj, "txAmount", &p->TxAmount);
    set_obj(obj, "flag", &p->Flag);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspInfoField *p)
{
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "exchangeName", &p->ExchangeName);
    set_obj(obj, "exchangeProperty", &p->ExchangeProperty);
}
static void set_obj(Local<Object>& obj, CThostFtdcProductField *p)
{
    set_obj(obj, "productId", &p->ProductID);
    set_obj(obj, "productName", &p->ProductName);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "productClass", &p->ProductClass);
    set_obj(obj, "volumeMultiple", &p->VolumeMultiple);
    set_obj(obj, "priceTick", &p->PriceTick);
    set_obj(obj, "maxMarketOrderVolume", &p->MaxMarketOrderVolume);
    set_obj(obj, "minMarketOrderVolume", &p->MinMarketOrderVolume);
    set_obj(obj, "maxLimitOrderVolume", &p->MaxLimitOrderVolume);
    set_obj(obj, "minLimitOrderVolume", &p->MinLimitOrderVolume);
    set_obj(obj, "positionType", &p->PositionType);
    set_obj(obj, "positionDateType", &p->PositionDateType);
    set_obj(obj, "closeDealType", &p->CloseDealType);
    set_obj(obj, "tradeCurrencyId", &p->TradeCurrencyID);
    set_obj(obj, "mortgageFundUseRange", &p->MortgageFundUseRange);
    set_obj(obj, "exchangeProductId", &p->ExchangeProductID);
    set_obj(obj, "underlyingMultiple", &p->UnderlyingMultiple);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "instrumentName", &p->InstrumentName);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "productId", &p->ProductID);
    set_obj(obj, "productClass", &p->ProductClass);
    set_obj(obj, "deliveryYear", &p->DeliveryYear);
    set_obj(obj, "deliveryMonth", &p->DeliveryMonth);
    set_obj(obj, "maxMarketOrderVolume", &p->MaxMarketOrderVolume);
    set_obj(obj, "minMarketOrderVolume", &p->MinMarketOrderVolume);
    set_obj(obj, "maxLimitOrderVolume", &p->MaxLimitOrderVolume);
    set_obj(obj, "minLimitOrderVolume", &p->MinLimitOrderVolume);
    set_obj(obj, "volumeMultiple", &p->VolumeMultiple);
    set_obj(obj, "priceTick", &p->PriceTick);
    set_obj(obj, "createDate", &p->CreateDate);
    set_obj(obj, "openDate", &p->OpenDate);
    set_obj(obj, "expireDate", &p->ExpireDate);
    set_obj(obj, "startDelivDate", &p->StartDelivDate);
    set_obj(obj, "endDelivDate", &p->EndDelivDate);
    set_obj(obj, "instLifePhase", &p->InstLifePhase);
    set_obj(obj, "isTrading", &p->IsTrading);
    set_obj(obj, "positionType", &p->PositionType);
    set_obj(obj, "positionDateType", &p->PositionDateType);
    set_obj(obj, "longMarginRatio", &p->LongMarginRatio);
    set_obj(obj, "shortMarginRatio", &p->ShortMarginRatio);
    set_obj(obj, "maxMarginSideAlgorithm", &p->MaxMarginSideAlgorithm);
    set_obj(obj, "underlyingInstrId", &p->UnderlyingInstrID);
    set_obj(obj, "strikePrice", &p->StrikePrice);
    set_obj(obj, "optionsType", &p->OptionsType);
    set_obj(obj, "underlyingMultiple", &p->UnderlyingMultiple);
    set_obj(obj, "combinationType", &p->CombinationType);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerAbbr", &p->BrokerAbbr);
    set_obj(obj, "brokerName", &p->BrokerName);
    set_obj(obj, "isActive", &p->IsActive);
}
static void set_obj(Local<Object>& obj, CThostFtdcTraderField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installCount", &p->InstallCount);
    set_obj(obj, "brokerId", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorField *p)
{
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorGroupId", &p->InvestorGroupID);
    set_obj(obj, "investorName", &p->InvestorName);
    set_obj(obj, "identifiedCardType", &p->IdentifiedCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "isActive", &p->IsActive);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "openDate", &p->OpenDate);
    set_obj(obj, "mobile", &p->Mobile);
    set_obj(obj, "commModelId", &p->CommModelID);
    set_obj(obj, "marginModelId", &p->MarginModelID);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingCodeField *p)
{
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "isActive", &p->IsActive);
    set_obj(obj, "clientIDType", &p->ClientIDType);
}
static void set_obj(Local<Object>& obj, CThostFtdcPartBrokerField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "isActive", &p->IsActive);
}
static void set_obj(Local<Object>& obj, CThostFtdcSuperUserField *p)
{
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "userName", &p->UserName);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "isActive", &p->IsActive);
}
static void set_obj(Local<Object>& obj, CThostFtdcSuperUserFunctionField *p)
{
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "functionCode", &p->FunctionCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorGroupField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorGroupId", &p->InvestorGroupID);
    set_obj(obj, "investorGroupName", &p->InvestorGroupName);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingAccountField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "preMortgage", &p->PreMortgage);
    set_obj(obj, "preCredit", &p->PreCredit);
    set_obj(obj, "preDeposit", &p->PreDeposit);
    set_obj(obj, "preBalance", &p->PreBalance);
    set_obj(obj, "preMargin", &p->PreMargin);
    set_obj(obj, "interestBase", &p->InterestBase);
    set_obj(obj, "interest", &p->Interest);
    set_obj(obj, "deposit", &p->Deposit);
    set_obj(obj, "withdraw", &p->Withdraw);
    set_obj(obj, "frozenMargin", &p->FrozenMargin);
    set_obj(obj, "frozenCash", &p->FrozenCash);
    set_obj(obj, "frozenCommission", &p->FrozenCommission);
    set_obj(obj, "currMargin", &p->CurrMargin);
    set_obj(obj, "cashIn", &p->CashIn);
    set_obj(obj, "commission", &p->Commission);
    set_obj(obj, "closeProfit", &p->CloseProfit);
    set_obj(obj, "positionProfit", &p->PositionProfit);
    set_obj(obj, "balance", &p->Balance);
    set_obj(obj, "available", &p->Available);
    set_obj(obj, "withdrawQuota", &p->WithdrawQuota);
    set_obj(obj, "reserve", &p->Reserve);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "credit", &p->Credit);
    set_obj(obj, "mortgage", &p->Mortgage);
    set_obj(obj, "exchangeMargin", &p->ExchangeMargin);
    set_obj(obj, "deliveryMargin", &p->DeliveryMargin);
    set_obj(obj, "exchangeDeliveryMargin", &p->ExchangeDeliveryMargin);
    set_obj(obj, "reserveBalance", &p->ReserveBalance);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "preFundMortgageIn", &p->PreFundMortgageIn);
    set_obj(obj, "preFundMortgageOut", &p->PreFundMortgageOut);
    set_obj(obj, "fundMortgageIn", &p->FundMortgageIn);
    set_obj(obj, "fundMortgageOut", &p->FundMortgageOut);
    set_obj(obj, "fundMortgageAvailable", &p->FundMortgageAvailable);
    set_obj(obj, "mortgageableFund", &p->MortgageableFund);
    set_obj(obj, "specProductMargin", &p->SpecProductMargin);
    set_obj(obj, "specProductFrozenMargin", &p->SpecProductFrozenMargin);
    set_obj(obj, "specProductCommission", &p->SpecProductCommission);
    set_obj(obj, "specProductFrozenCommission", &p->SpecProductFrozenCommission);
    set_obj(obj, "specProductPositionProfit", &p->SpecProductPositionProfit);
    set_obj(obj, "specProductCloseProfit", &p->SpecProductCloseProfit);
    set_obj(obj, "specProductPositionProfitByAlg", &p->SpecProductPositionProfitByAlg);
    set_obj(obj, "specProductExchangeMargin", &p->SpecProductExchangeMargin);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorPositionField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "posiDirection", &p->PosiDirection);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "positionDate", &p->PositionDate);
    set_obj(obj, "ydPosition", &p->YdPosition);
    set_obj(obj, "position", &p->Position);
    set_obj(obj, "longFrozen", &p->LongFrozen);
    set_obj(obj, "shortFrozen", &p->ShortFrozen);
    set_obj(obj, "longFrozenAmount", &p->LongFrozenAmount);
    set_obj(obj, "shortFrozenAmount", &p->ShortFrozenAmount);
    set_obj(obj, "openVolume", &p->OpenVolume);
    set_obj(obj, "closeVolume", &p->CloseVolume);
    set_obj(obj, "openAmount", &p->OpenAmount);
    set_obj(obj, "closeAmount", &p->CloseAmount);
    set_obj(obj, "positionCost", &p->PositionCost);
    set_obj(obj, "preMargin", &p->PreMargin);
    set_obj(obj, "useMargin", &p->UseMargin);
    set_obj(obj, "frozenMargin", &p->FrozenMargin);
    set_obj(obj, "frozenCash", &p->FrozenCash);
    set_obj(obj, "frozenCommission", &p->FrozenCommission);
    set_obj(obj, "cashIn", &p->CashIn);
    set_obj(obj, "commission", &p->Commission);
    set_obj(obj, "closeProfit", &p->CloseProfit);
    set_obj(obj, "positionProfit", &p->PositionProfit);
    set_obj(obj, "preSettlementPrice", &p->PreSettlementPrice);
    set_obj(obj, "settlementPrice", &p->SettlementPrice);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "openCost", &p->OpenCost);
    set_obj(obj, "exchangeMargin", &p->ExchangeMargin);
    set_obj(obj, "combPosition", &p->CombPosition);
    set_obj(obj, "combLongFrozen", &p->CombLongFrozen);
    set_obj(obj, "combShortFrozen", &p->CombShortFrozen);
    set_obj(obj, "closeProfitByDate", &p->CloseProfitByDate);
    set_obj(obj, "closeProfitByTrade", &p->CloseProfitByTrade);
    set_obj(obj, "todayPosition", &p->TodayPosition);
    set_obj(obj, "marginRateByMoney", &p->MarginRateByMoney);
    set_obj(obj, "marginRateByVolume", &p->MarginRateByVolume);
    set_obj(obj, "strikeFrozen", &p->StrikeFrozen);
    set_obj(obj, "strikeFrozenAmount", &p->StrikeFrozenAmount);
    set_obj(obj, "abandonFrozen", &p->AbandonFrozen);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentMarginRateField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "longMarginRatioByMoney", &p->LongMarginRatioByMoney);
    set_obj(obj, "longMarginRatioByVolume", &p->LongMarginRatioByVolume);
    set_obj(obj, "shortMarginRatioByMoney", &p->ShortMarginRatioByMoney);
    set_obj(obj, "shortMarginRatioByVolume", &p->ShortMarginRatioByVolume);
    set_obj(obj, "isRelative", &p->IsRelative);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentCommissionRateField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "openRatioByMoney", &p->OpenRatioByMoney);
    set_obj(obj, "openRatioByVolume", &p->OpenRatioByVolume);
    set_obj(obj, "closeRatioByMoney", &p->CloseRatioByMoney);
    set_obj(obj, "closeRatioByVolume", &p->CloseRatioByVolume);
    set_obj(obj, "closeTodayRatioByMoney", &p->CloseTodayRatioByMoney);
    set_obj(obj, "closeTodayRatioByVolume", &p->CloseTodayRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcDepthMarketDataField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "lastPrice", &p->LastPrice);
    set_obj(obj, "preSettlementPrice", &p->PreSettlementPrice);
    set_obj(obj, "preClosePrice", &p->PreClosePrice);
    set_obj(obj, "preOpenInterest", &p->PreOpenInterest);
    set_obj(obj, "openPrice", &p->OpenPrice);
    set_obj(obj, "highestPrice", &p->HighestPrice);
    set_obj(obj, "lowestPrice", &p->LowestPrice);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "turnover", &p->Turnover);
    set_obj(obj, "openInterest", &p->OpenInterest);
    set_obj(obj, "closePrice", &p->ClosePrice);
    set_obj(obj, "settlementPrice", &p->SettlementPrice);
    set_obj(obj, "upperLimitPrice", &p->UpperLimitPrice);
    set_obj(obj, "lowerLimitPrice", &p->LowerLimitPrice);
    set_obj(obj, "preDelta", &p->PreDelta);
    set_obj(obj, "currDelta", &p->CurrDelta);
    set_obj(obj, "updateTime", &p->UpdateTime);
    set_obj(obj, "updateMillisec", &p->UpdateMillisec);
    set_obj(obj, "bidPrice1", &p->BidPrice1);
    set_obj(obj, "bidVolume1", &p->BidVolume1);
    set_obj(obj, "askPrice1", &p->AskPrice1);
    set_obj(obj, "askVolume1", &p->AskVolume1);
    set_obj(obj, "bidPrice2", &p->BidPrice2);
    set_obj(obj, "bidVolume2", &p->BidVolume2);
    set_obj(obj, "askPrice2", &p->AskPrice2);
    set_obj(obj, "askVolume2", &p->AskVolume2);
    set_obj(obj, "bidPrice3", &p->BidPrice3);
    set_obj(obj, "bidVolume3", &p->BidVolume3);
    set_obj(obj, "askPrice3", &p->AskPrice3);
    set_obj(obj, "askVolume3", &p->AskVolume3);
    set_obj(obj, "bidPrice4", &p->BidPrice4);
    set_obj(obj, "bidVolume4", &p->BidVolume4);
    set_obj(obj, "askPrice4", &p->AskPrice4);
    set_obj(obj, "askVolume4", &p->AskVolume4);
    set_obj(obj, "bidPrice5", &p->BidPrice5);
    set_obj(obj, "bidVolume5", &p->BidVolume5);
    set_obj(obj, "askPrice5", &p->AskPrice5);
    set_obj(obj, "askVolume5", &p->AskVolume5);
    set_obj(obj, "averagePrice", &p->AveragePrice);
    set_obj(obj, "actionDay", &p->ActionDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentTradingRightField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "tradingRight", &p->TradingRight);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "userName", &p->UserName);
    set_obj(obj, "userType", &p->UserType);
    set_obj(obj, "isActive", &p->IsActive);
    set_obj(obj, "isUsingOtp", &p->IsUsingOTP);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserPasswordField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "password", &p->Password);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserFunctionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "brokerFunctionCode", &p->BrokerFunctionCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcTraderOfferField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "traderConnectStatus", &p->TraderConnectStatus);
    set_obj(obj, "connectRequestDate", &p->ConnectRequestDate);
    set_obj(obj, "connectRequestTime", &p->ConnectRequestTime);
    set_obj(obj, "lastReportDate", &p->LastReportDate);
    set_obj(obj, "lastReportTime", &p->LastReportTime);
    set_obj(obj, "connectDate", &p->ConnectDate);
    set_obj(obj, "connectTime", &p->ConnectTime);
    set_obj(obj, "startDate", &p->StartDate);
    set_obj(obj, "startTime", &p->StartTime);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "maxTradeId", &p->MaxTradeID);
    set_obj(obj, "maxOrderMessageReference", &p->MaxOrderMessageReference);
}
static void set_obj(Local<Object>& obj, CThostFtdcSettlementInfoField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "content", &p->Content);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentMarginRateAdjustField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "longMarginRatioByMoney", &p->LongMarginRatioByMoney);
    set_obj(obj, "longMarginRatioByVolume", &p->LongMarginRatioByVolume);
    set_obj(obj, "shortMarginRatioByMoney", &p->ShortMarginRatioByMoney);
    set_obj(obj, "shortMarginRatioByVolume", &p->ShortMarginRatioByVolume);
    set_obj(obj, "isRelative", &p->IsRelative);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeMarginRateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "longMarginRatioByMoney", &p->LongMarginRatioByMoney);
    set_obj(obj, "longMarginRatioByVolume", &p->LongMarginRatioByVolume);
    set_obj(obj, "shortMarginRatioByMoney", &p->ShortMarginRatioByMoney);
    set_obj(obj, "shortMarginRatioByVolume", &p->ShortMarginRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeMarginRateAdjustField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "longMarginRatioByMoney", &p->LongMarginRatioByMoney);
    set_obj(obj, "longMarginRatioByVolume", &p->LongMarginRatioByVolume);
    set_obj(obj, "shortMarginRatioByMoney", &p->ShortMarginRatioByMoney);
    set_obj(obj, "shortMarginRatioByVolume", &p->ShortMarginRatioByVolume);
    set_obj(obj, "exchLongMarginRatioByMoney", &p->ExchLongMarginRatioByMoney);
    set_obj(obj, "exchLongMarginRatioByVolume", &p->ExchLongMarginRatioByVolume);
    set_obj(obj, "exchShortMarginRatioByMoney", &p->ExchShortMarginRatioByMoney);
    set_obj(obj, "exchShortMarginRatioByVolume", &p->ExchShortMarginRatioByVolume);
    set_obj(obj, "noLongMarginRatioByMoney", &p->NoLongMarginRatioByMoney);
    set_obj(obj, "noLongMarginRatioByVolume", &p->NoLongMarginRatioByVolume);
    set_obj(obj, "noShortMarginRatioByMoney", &p->NoShortMarginRatioByMoney);
    set_obj(obj, "noShortMarginRatioByVolume", &p->NoShortMarginRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeRateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "fromCurrencyId", &p->FromCurrencyID);
    set_obj(obj, "fromCurrencyUnit", &p->FromCurrencyUnit);
    set_obj(obj, "toCurrencyId", &p->ToCurrencyID);
    set_obj(obj, "exchangeRate", &p->ExchangeRate);
}
static void set_obj(Local<Object>& obj, CThostFtdcSettlementRefField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
}
static void set_obj(Local<Object>& obj, CThostFtdcCurrentTimeField *p)
{
    set_obj(obj, "currDate", &p->CurrDate);
    set_obj(obj, "currTime", &p->CurrTime);
    set_obj(obj, "currMillisec", &p->CurrMillisec);
    set_obj(obj, "actionDay", &p->ActionDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcCommPhaseField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "commPhaseNo", &p->CommPhaseNo);
    set_obj(obj, "systemId", &p->SystemID);
}
static void set_obj(Local<Object>& obj, CThostFtdcLoginInfoField *p)
{
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "loginDate", &p->LoginDate);
    set_obj(obj, "loginTime", &p->LoginTime);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "interfaceProductInfo", &p->InterfaceProductInfo);
    set_obj(obj, "protocolInfo", &p->ProtocolInfo);
    set_obj(obj, "systemName", &p->SystemName);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "maxOrderRef", &p->MaxOrderRef);
    set_obj(obj, "shfeTime", &p->SHFETime);
    set_obj(obj, "dceTime", &p->DCETime);
    set_obj(obj, "czceTime", &p->CZCETime);
    set_obj(obj, "ffexTime", &p->FFEXTime);
    set_obj(obj, "macAddress", &p->MacAddress);
    set_obj(obj, "oneTimePassword", &p->OneTimePassword);
    set_obj(obj, "ineTime", &p->INETime);
    set_obj(obj, "isQryControl", &p->IsQryControl);
    set_obj(obj, "loginRemark", &p->LoginRemark);
}
static void set_obj(Local<Object>& obj, CThostFtdcLogoutAllField *p)
{
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "systemName", &p->SystemName);
}
static void set_obj(Local<Object>& obj, CThostFtdcFrontStatusField *p)
{
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "lastReportDate", &p->LastReportDate);
    set_obj(obj, "lastReportTime", &p->LastReportTime);
    set_obj(obj, "isActive", &p->IsActive);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserPasswordUpdateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "oldPassword", &p->OldPassword);
    set_obj(obj, "newPassword", &p->NewPassword);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "orderRef", &p->OrderRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "orderPriceType", &p->OrderPriceType);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "combOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "combHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "timeCondition", &p->TimeCondition);
    set_obj(obj, "gtdDate", &p->GTDDate);
    set_obj(obj, "volumeCondition", &p->VolumeCondition);
    set_obj(obj, "minVolume", &p->MinVolume);
    set_obj(obj, "contingentCondition", &p->ContingentCondition);
    set_obj(obj, "stopPrice", &p->StopPrice);
    set_obj(obj, "forceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "isAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "userForceClose", &p->UserForceClose);
    set_obj(obj, "isSwapOrder", &p->IsSwapOrder);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "orderRef", &p->OrderRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "orderPriceType", &p->OrderPriceType);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "combOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "combHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "timeCondition", &p->TimeCondition);
    set_obj(obj, "gtdDate", &p->GTDDate);
    set_obj(obj, "volumeCondition", &p->VolumeCondition);
    set_obj(obj, "minVolume", &p->MinVolume);
    set_obj(obj, "contingentCondition", &p->ContingentCondition);
    set_obj(obj, "stopPrice", &p->StopPrice);
    set_obj(obj, "forceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "isAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "notifySequence", &p->NotifySequence);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "orderSource", &p->OrderSource);
    set_obj(obj, "orderStatus", &p->OrderStatus);
    set_obj(obj, "orderType", &p->OrderType);
    set_obj(obj, "volumeTraded", &p->VolumeTraded);
    set_obj(obj, "volumeTotal", &p->VolumeTotal);
    set_obj(obj, "insertDate", &p->InsertDate);
    set_obj(obj, "insertTime", &p->InsertTime);
    set_obj(obj, "activeTime", &p->ActiveTime);
    set_obj(obj, "suspendTime", &p->SuspendTime);
    set_obj(obj, "updateTime", &p->UpdateTime);
    set_obj(obj, "cancelTime", &p->CancelTime);
    set_obj(obj, "activeTraderId", &p->ActiveTraderID);
    set_obj(obj, "clearingPartId", &p->ClearingPartID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "userForceClose", &p->UserForceClose);
    set_obj(obj, "activeUserId", &p->ActiveUserID);
    set_obj(obj, "brokerOrderSeq", &p->BrokerOrderSeq);
    set_obj(obj, "relativeOrderSysId", &p->RelativeOrderSysID);
    set_obj(obj, "zceTotalTradedVolume", &p->ZCETotalTradedVolume);
    set_obj(obj, "isSwapOrder", &p->IsSwapOrder);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeOrderField *p)
{
    set_obj(obj, "orderPriceType", &p->OrderPriceType);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "combOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "combHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "timeCondition", &p->TimeCondition);
    set_obj(obj, "gtdDate", &p->GTDDate);
    set_obj(obj, "volumeCondition", &p->VolumeCondition);
    set_obj(obj, "minVolume", &p->MinVolume);
    set_obj(obj, "contingentCondition", &p->ContingentCondition);
    set_obj(obj, "stopPrice", &p->StopPrice);
    set_obj(obj, "forceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "isAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "notifySequence", &p->NotifySequence);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "orderSource", &p->OrderSource);
    set_obj(obj, "orderStatus", &p->OrderStatus);
    set_obj(obj, "orderType", &p->OrderType);
    set_obj(obj, "volumeTraded", &p->VolumeTraded);
    set_obj(obj, "volumeTotal", &p->VolumeTotal);
    set_obj(obj, "insertDate", &p->InsertDate);
    set_obj(obj, "insertTime", &p->InsertTime);
    set_obj(obj, "activeTime", &p->ActiveTime);
    set_obj(obj, "suspendTime", &p->SuspendTime);
    set_obj(obj, "updateTime", &p->UpdateTime);
    set_obj(obj, "cancelTime", &p->CancelTime);
    set_obj(obj, "activeTraderId", &p->ActiveTraderID);
    set_obj(obj, "clearingPartId", &p->ClearingPartID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeOrderInsertErrorField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "orderActionRef", &p->OrderActionRef);
    set_obj(obj, "orderRef", &p->OrderRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeChange", &p->VolumeChange);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "orderActionRef", &p->OrderActionRef);
    set_obj(obj, "orderRef", &p->OrderRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeChange", &p->VolumeChange);
    set_obj(obj, "actionDate", &p->ActionDate);
    set_obj(obj, "actionTime", &p->ActionTime);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "orderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeOrderActionField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeChange", &p->VolumeChange);
    set_obj(obj, "actionDate", &p->ActionDate);
    set_obj(obj, "actionTime", &p->ActionTime);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "orderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeOrderActionErrorField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeTradeField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "tradeId", &p->TradeID);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "tradingRole", &p->TradingRole);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "offsetFlag", &p->OffsetFlag);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "price", &p->Price);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "tradeType", &p->TradeType);
    set_obj(obj, "priceSource", &p->PriceSource);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "clearingPartId", &p->ClearingPartID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "tradeSource", &p->TradeSource);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradeField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "orderRef", &p->OrderRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "tradeId", &p->TradeID);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "tradingRole", &p->TradingRole);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "offsetFlag", &p->OffsetFlag);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "price", &p->Price);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "tradeType", &p->TradeType);
    set_obj(obj, "priceSource", &p->PriceSource);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "clearingPartId", &p->ClearingPartID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "brokerOrderSeq", &p->BrokerOrderSeq);
    set_obj(obj, "tradeSource", &p->TradeSource);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserSessionField *p)
{
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "loginDate", &p->LoginDate);
    set_obj(obj, "loginTime", &p->LoginTime);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "interfaceProductInfo", &p->InterfaceProductInfo);
    set_obj(obj, "protocolInfo", &p->ProtocolInfo);
    set_obj(obj, "macAddress", &p->MacAddress);
    set_obj(obj, "loginRemark", &p->LoginRemark);
}
static void set_obj(Local<Object>& obj, CThostFtdcQueryMaxOrderVolumeField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "offsetFlag", &p->OffsetFlag);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "maxVolume", &p->MaxVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcSettlementInfoConfirmField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "confirmDate", &p->ConfirmDate);
    set_obj(obj, "confirmTime", &p->ConfirmTime);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncDepositField *p)
{
    set_obj(obj, "depositSeqNo", &p->DepositSeqNo);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "deposit", &p->Deposit);
    set_obj(obj, "isForce", &p->IsForce);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncFundMortgageField *p)
{
    set_obj(obj, "mortgageSeqNo", &p->MortgageSeqNo);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "fromCurrencyId", &p->FromCurrencyID);
    set_obj(obj, "mortgageAmount", &p->MortgageAmount);
    set_obj(obj, "toCurrencyId", &p->ToCurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerSyncField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInvestorField *p)
{
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorGroupId", &p->InvestorGroupID);
    set_obj(obj, "investorName", &p->InvestorName);
    set_obj(obj, "identifiedCardType", &p->IdentifiedCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "isActive", &p->IsActive);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "openDate", &p->OpenDate);
    set_obj(obj, "mobile", &p->Mobile);
    set_obj(obj, "commModelId", &p->CommModelID);
    set_obj(obj, "marginModelId", &p->MarginModelID);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingTradingCodeField *p)
{
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "isActive", &p->IsActive);
    set_obj(obj, "clientIDType", &p->ClientIDType);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInvestorGroupField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorGroupId", &p->InvestorGroupID);
    set_obj(obj, "investorGroupName", &p->InvestorGroupName);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingTradingAccountField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "preMortgage", &p->PreMortgage);
    set_obj(obj, "preCredit", &p->PreCredit);
    set_obj(obj, "preDeposit", &p->PreDeposit);
    set_obj(obj, "preBalance", &p->PreBalance);
    set_obj(obj, "preMargin", &p->PreMargin);
    set_obj(obj, "interestBase", &p->InterestBase);
    set_obj(obj, "interest", &p->Interest);
    set_obj(obj, "deposit", &p->Deposit);
    set_obj(obj, "withdraw", &p->Withdraw);
    set_obj(obj, "frozenMargin", &p->FrozenMargin);
    set_obj(obj, "frozenCash", &p->FrozenCash);
    set_obj(obj, "frozenCommission", &p->FrozenCommission);
    set_obj(obj, "currMargin", &p->CurrMargin);
    set_obj(obj, "cashIn", &p->CashIn);
    set_obj(obj, "commission", &p->Commission);
    set_obj(obj, "closeProfit", &p->CloseProfit);
    set_obj(obj, "positionProfit", &p->PositionProfit);
    set_obj(obj, "balance", &p->Balance);
    set_obj(obj, "available", &p->Available);
    set_obj(obj, "withdrawQuota", &p->WithdrawQuota);
    set_obj(obj, "reserve", &p->Reserve);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "credit", &p->Credit);
    set_obj(obj, "mortgage", &p->Mortgage);
    set_obj(obj, "exchangeMargin", &p->ExchangeMargin);
    set_obj(obj, "deliveryMargin", &p->DeliveryMargin);
    set_obj(obj, "exchangeDeliveryMargin", &p->ExchangeDeliveryMargin);
    set_obj(obj, "reserveBalance", &p->ReserveBalance);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "preFundMortgageIn", &p->PreFundMortgageIn);
    set_obj(obj, "preFundMortgageOut", &p->PreFundMortgageOut);
    set_obj(obj, "fundMortgageIn", &p->FundMortgageIn);
    set_obj(obj, "fundMortgageOut", &p->FundMortgageOut);
    set_obj(obj, "fundMortgageAvailable", &p->FundMortgageAvailable);
    set_obj(obj, "mortgageableFund", &p->MortgageableFund);
    set_obj(obj, "specProductMargin", &p->SpecProductMargin);
    set_obj(obj, "specProductFrozenMargin", &p->SpecProductFrozenMargin);
    set_obj(obj, "specProductCommission", &p->SpecProductCommission);
    set_obj(obj, "specProductFrozenCommission", &p->SpecProductFrozenCommission);
    set_obj(obj, "specProductPositionProfit", &p->SpecProductPositionProfit);
    set_obj(obj, "specProductCloseProfit", &p->SpecProductCloseProfit);
    set_obj(obj, "specProductPositionProfitByAlg", &p->SpecProductPositionProfitByAlg);
    set_obj(obj, "specProductExchangeMargin", &p->SpecProductExchangeMargin);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInvestorPositionField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "posiDirection", &p->PosiDirection);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "positionDate", &p->PositionDate);
    set_obj(obj, "ydPosition", &p->YdPosition);
    set_obj(obj, "position", &p->Position);
    set_obj(obj, "longFrozen", &p->LongFrozen);
    set_obj(obj, "shortFrozen", &p->ShortFrozen);
    set_obj(obj, "longFrozenAmount", &p->LongFrozenAmount);
    set_obj(obj, "shortFrozenAmount", &p->ShortFrozenAmount);
    set_obj(obj, "openVolume", &p->OpenVolume);
    set_obj(obj, "closeVolume", &p->CloseVolume);
    set_obj(obj, "openAmount", &p->OpenAmount);
    set_obj(obj, "closeAmount", &p->CloseAmount);
    set_obj(obj, "positionCost", &p->PositionCost);
    set_obj(obj, "preMargin", &p->PreMargin);
    set_obj(obj, "useMargin", &p->UseMargin);
    set_obj(obj, "frozenMargin", &p->FrozenMargin);
    set_obj(obj, "frozenCash", &p->FrozenCash);
    set_obj(obj, "frozenCommission", &p->FrozenCommission);
    set_obj(obj, "cashIn", &p->CashIn);
    set_obj(obj, "commission", &p->Commission);
    set_obj(obj, "closeProfit", &p->CloseProfit);
    set_obj(obj, "positionProfit", &p->PositionProfit);
    set_obj(obj, "preSettlementPrice", &p->PreSettlementPrice);
    set_obj(obj, "settlementPrice", &p->SettlementPrice);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "openCost", &p->OpenCost);
    set_obj(obj, "exchangeMargin", &p->ExchangeMargin);
    set_obj(obj, "combPosition", &p->CombPosition);
    set_obj(obj, "combLongFrozen", &p->CombLongFrozen);
    set_obj(obj, "combShortFrozen", &p->CombShortFrozen);
    set_obj(obj, "closeProfitByDate", &p->CloseProfitByDate);
    set_obj(obj, "closeProfitByTrade", &p->CloseProfitByTrade);
    set_obj(obj, "todayPosition", &p->TodayPosition);
    set_obj(obj, "marginRateByMoney", &p->MarginRateByMoney);
    set_obj(obj, "marginRateByVolume", &p->MarginRateByVolume);
    set_obj(obj, "strikeFrozen", &p->StrikeFrozen);
    set_obj(obj, "strikeFrozenAmount", &p->StrikeFrozenAmount);
    set_obj(obj, "abandonFrozen", &p->AbandonFrozen);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInstrumentMarginRateField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "longMarginRatioByMoney", &p->LongMarginRatioByMoney);
    set_obj(obj, "longMarginRatioByVolume", &p->LongMarginRatioByVolume);
    set_obj(obj, "shortMarginRatioByMoney", &p->ShortMarginRatioByMoney);
    set_obj(obj, "shortMarginRatioByVolume", &p->ShortMarginRatioByVolume);
    set_obj(obj, "isRelative", &p->IsRelative);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInstrumentCommissionRateField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "openRatioByMoney", &p->OpenRatioByMoney);
    set_obj(obj, "openRatioByVolume", &p->OpenRatioByVolume);
    set_obj(obj, "closeRatioByMoney", &p->CloseRatioByMoney);
    set_obj(obj, "closeRatioByVolume", &p->CloseRatioByVolume);
    set_obj(obj, "closeTodayRatioByMoney", &p->CloseTodayRatioByMoney);
    set_obj(obj, "closeTodayRatioByVolume", &p->CloseTodayRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncingInstrumentTradingRightField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "tradingRight", &p->TradingRight);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "insertTimeStart", &p->InsertTimeStart);
    set_obj(obj, "insertTimeEnd", &p->InsertTimeEnd);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTradeField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "tradeId", &p->TradeID);
    set_obj(obj, "tradeTimeStart", &p->TradeTimeStart);
    set_obj(obj, "tradeTimeEnd", &p->TradeTimeEnd);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorPositionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTradingAccountField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTradingCodeField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "clientIDType", &p->ClientIDType);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorGroupField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentMarginRateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentCommissionRateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentTradingRightField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTraderField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySuperUserFunctionField *p)
{
    set_obj(obj, "userId", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryUserSessionField *p)
{
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryPartBrokerField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "participantId", &p->ParticipantID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryFrontStatusField *p)
{
    set_obj(obj, "frontId", &p->FrontID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeOrderField *p)
{
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeOrderActionField *p)
{
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySuperUserField *p)
{
    set_obj(obj, "userId", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryProductField *p)
{
    set_obj(obj, "productId", &p->ProductID);
    set_obj(obj, "productClass", &p->ProductClass);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "productId", &p->ProductID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryDepthMarketDataField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerUserField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerUserFunctionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTraderOfferField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySyncDepositField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "depositSeqNo", &p->DepositSeqNo);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySettlementInfoField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "tradingDay", &p->TradingDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeMarginRateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeMarginRateAdjustField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeRateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "fromCurrencyId", &p->FromCurrencyID);
    set_obj(obj, "toCurrencyId", &p->ToCurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySyncFundMortgageField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "mortgageSeqNo", &p->MortgageSeqNo);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryHisOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "insertTimeStart", &p->InsertTimeStart);
    set_obj(obj, "insertTimeEnd", &p->InsertTimeEnd);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrMiniMarginField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "minMargin", &p->MinMargin);
    set_obj(obj, "valueMethod", &p->ValueMethod);
    set_obj(obj, "isRelative", &p->IsRelative);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrMarginAdjustField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "sShortMarginRatioByMoney", &p->SShortMarginRatioByMoney);
    set_obj(obj, "sShortMarginRatioByVolume", &p->SShortMarginRatioByVolume);
    set_obj(obj, "hShortMarginRatioByMoney", &p->HShortMarginRatioByMoney);
    set_obj(obj, "hShortMarginRatioByVolume", &p->HShortMarginRatioByVolume);
    set_obj(obj, "aShortMarginRatioByMoney", &p->AShortMarginRatioByMoney);
    set_obj(obj, "aShortMarginRatioByVolume", &p->AShortMarginRatioByVolume);
    set_obj(obj, "isRelative", &p->IsRelative);
    set_obj(obj, "mShortMarginRatioByMoney", &p->MShortMarginRatioByMoney);
    set_obj(obj, "mShortMarginRatioByVolume", &p->MShortMarginRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrCommRateField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "openRatioByMoney", &p->OpenRatioByMoney);
    set_obj(obj, "openRatioByVolume", &p->OpenRatioByVolume);
    set_obj(obj, "closeRatioByMoney", &p->CloseRatioByMoney);
    set_obj(obj, "closeRatioByVolume", &p->CloseRatioByVolume);
    set_obj(obj, "closeTodayRatioByMoney", &p->CloseTodayRatioByMoney);
    set_obj(obj, "closeTodayRatioByVolume", &p->CloseTodayRatioByVolume);
    set_obj(obj, "strikeRatioByMoney", &p->StrikeRatioByMoney);
    set_obj(obj, "strikeRatioByVolume", &p->StrikeRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrTradeCostField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "fixedMargin", &p->FixedMargin);
    set_obj(obj, "miniMargin", &p->MiniMargin);
    set_obj(obj, "royalty", &p->Royalty);
    set_obj(obj, "exchFixedMargin", &p->ExchFixedMargin);
    set_obj(obj, "exchMiniMargin", &p->ExchMiniMargin);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryOptionInstrTradeCostField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "inputPrice", &p->InputPrice);
    set_obj(obj, "underlyingPrice", &p->UnderlyingPrice);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryOptionInstrCommRateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcIndexPriceField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "closePrice", &p->ClosePrice);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputExecOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "execOrderRef", &p->ExecOrderRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "offsetFlag", &p->OffsetFlag);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "actionType", &p->ActionType);
    set_obj(obj, "posiDirection", &p->PosiDirection);
    set_obj(obj, "reservePositionFlag", &p->ReservePositionFlag);
    set_obj(obj, "closeFlag", &p->CloseFlag);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputExecOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "execOrderActionRef", &p->ExecOrderActionRef);
    set_obj(obj, "execOrderRef", &p->ExecOrderRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "execOrderSysId", &p->ExecOrderSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExecOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "execOrderRef", &p->ExecOrderRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "offsetFlag", &p->OffsetFlag);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "actionType", &p->ActionType);
    set_obj(obj, "posiDirection", &p->PosiDirection);
    set_obj(obj, "reservePositionFlag", &p->ReservePositionFlag);
    set_obj(obj, "closeFlag", &p->CloseFlag);
    set_obj(obj, "execOrderLocalId", &p->ExecOrderLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "notifySequence", &p->NotifySequence);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "execOrderSysId", &p->ExecOrderSysID);
    set_obj(obj, "insertDate", &p->InsertDate);
    set_obj(obj, "insertTime", &p->InsertTime);
    set_obj(obj, "cancelTime", &p->CancelTime);
    set_obj(obj, "execResult", &p->ExecResult);
    set_obj(obj, "clearingPartId", &p->ClearingPartID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "activeUserId", &p->ActiveUserID);
    set_obj(obj, "brokerExecOrderSeq", &p->BrokerExecOrderSeq);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExecOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "execOrderActionRef", &p->ExecOrderActionRef);
    set_obj(obj, "execOrderRef", &p->ExecOrderRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "execOrderSysId", &p->ExecOrderSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "actionDate", &p->ActionDate);
    set_obj(obj, "actionTime", &p->ActionTime);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "execOrderLocalId", &p->ExecOrderLocalID);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "orderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "actionType", &p->ActionType);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExecOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "execOrderSysId", &p->ExecOrderSysID);
    set_obj(obj, "insertTimeStart", &p->InsertTimeStart);
    set_obj(obj, "insertTimeEnd", &p->InsertTimeEnd);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeExecOrderField *p)
{
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "offsetFlag", &p->OffsetFlag);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "actionType", &p->ActionType);
    set_obj(obj, "posiDirection", &p->PosiDirection);
    set_obj(obj, "reservePositionFlag", &p->ReservePositionFlag);
    set_obj(obj, "closeFlag", &p->CloseFlag);
    set_obj(obj, "execOrderLocalId", &p->ExecOrderLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "notifySequence", &p->NotifySequence);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "execOrderSysId", &p->ExecOrderSysID);
    set_obj(obj, "insertDate", &p->InsertDate);
    set_obj(obj, "insertTime", &p->InsertTime);
    set_obj(obj, "cancelTime", &p->CancelTime);
    set_obj(obj, "execResult", &p->ExecResult);
    set_obj(obj, "clearingPartId", &p->ClearingPartID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeExecOrderField *p)
{
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExecOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeExecOrderActionField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "execOrderSysId", &p->ExecOrderSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "actionDate", &p->ActionDate);
    set_obj(obj, "actionTime", &p->ActionTime);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "execOrderLocalId", &p->ExecOrderLocalID);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "orderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "actionType", &p->ActionType);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeExecOrderActionField *p)
{
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcErrExecOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "execOrderRef", &p->ExecOrderRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "offsetFlag", &p->OffsetFlag);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "actionType", &p->ActionType);
    set_obj(obj, "posiDirection", &p->PosiDirection);
    set_obj(obj, "reservePositionFlag", &p->ReservePositionFlag);
    set_obj(obj, "closeFlag", &p->CloseFlag);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryErrExecOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcErrExecOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "execOrderActionRef", &p->ExecOrderActionRef);
    set_obj(obj, "execOrderRef", &p->ExecOrderRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "execOrderSysId", &p->ExecOrderSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryErrExecOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrTradingRightField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "tradingRight", &p->TradingRight);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryOptionInstrTradingRightField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "direction", &p->Direction);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputForQuoteField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "forQuoteRef", &p->ForQuoteRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcForQuoteField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "forQuoteRef", &p->ForQuoteRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "forQuoteLocalId", &p->ForQuoteLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "insertDate", &p->InsertDate);
    set_obj(obj, "insertTime", &p->InsertTime);
    set_obj(obj, "forQuoteStatus", &p->ForQuoteStatus);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "activeUserId", &p->ActiveUserID);
    set_obj(obj, "brokerForQutoSeq", &p->BrokerForQutoSeq);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryForQuoteField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "insertTimeStart", &p->InsertTimeStart);
    set_obj(obj, "insertTimeEnd", &p->InsertTimeEnd);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeForQuoteField *p)
{
    set_obj(obj, "forQuoteLocalId", &p->ForQuoteLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "insertDate", &p->InsertDate);
    set_obj(obj, "insertTime", &p->InsertTime);
    set_obj(obj, "forQuoteStatus", &p->ForQuoteStatus);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeForQuoteField *p)
{
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputQuoteField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "quoteRef", &p->QuoteRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "askPrice", &p->AskPrice);
    set_obj(obj, "bidPrice", &p->BidPrice);
    set_obj(obj, "askVolume", &p->AskVolume);
    set_obj(obj, "bidVolume", &p->BidVolume);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "askOffsetFlag", &p->AskOffsetFlag);
    set_obj(obj, "bidOffsetFlag", &p->BidOffsetFlag);
    set_obj(obj, "askHedgeFlag", &p->AskHedgeFlag);
    set_obj(obj, "bidHedgeFlag", &p->BidHedgeFlag);
    set_obj(obj, "askOrderRef", &p->AskOrderRef);
    set_obj(obj, "bidOrderRef", &p->BidOrderRef);
    set_obj(obj, "forQuoteSysId", &p->ForQuoteSysID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputQuoteActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "quoteActionRef", &p->QuoteActionRef);
    set_obj(obj, "quoteRef", &p->QuoteRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "quoteSysId", &p->QuoteSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQuoteField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "quoteRef", &p->QuoteRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "askPrice", &p->AskPrice);
    set_obj(obj, "bidPrice", &p->BidPrice);
    set_obj(obj, "askVolume", &p->AskVolume);
    set_obj(obj, "bidVolume", &p->BidVolume);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "askOffsetFlag", &p->AskOffsetFlag);
    set_obj(obj, "bidOffsetFlag", &p->BidOffsetFlag);
    set_obj(obj, "askHedgeFlag", &p->AskHedgeFlag);
    set_obj(obj, "bidHedgeFlag", &p->BidHedgeFlag);
    set_obj(obj, "quoteLocalId", &p->QuoteLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "notifySequence", &p->NotifySequence);
    set_obj(obj, "orderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "quoteSysId", &p->QuoteSysID);
    set_obj(obj, "insertDate", &p->InsertDate);
    set_obj(obj, "insertTime", &p->InsertTime);
    set_obj(obj, "cancelTime", &p->CancelTime);
    set_obj(obj, "quoteStatus", &p->QuoteStatus);
    set_obj(obj, "clearingPartId", &p->ClearingPartID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "askOrderSysId", &p->AskOrderSysID);
    set_obj(obj, "bidOrderSysId", &p->BidOrderSysID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "activeUserId", &p->ActiveUserID);
    set_obj(obj, "brokerQuoteSeq", &p->BrokerQuoteSeq);
    set_obj(obj, "askOrderRef", &p->AskOrderRef);
    set_obj(obj, "bidOrderRef", &p->BidOrderRef);
    set_obj(obj, "forQuoteSysId", &p->ForQuoteSysID);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQuoteActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "quoteActionRef", &p->QuoteActionRef);
    set_obj(obj, "quoteRef", &p->QuoteRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "quoteSysId", &p->QuoteSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "actionDate", &p->ActionDate);
    set_obj(obj, "actionTime", &p->ActionTime);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "quoteLocalId", &p->QuoteLocalID);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "orderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryQuoteField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "quoteSysId", &p->QuoteSysID);
    set_obj(obj, "insertTimeStart", &p->InsertTimeStart);
    set_obj(obj, "insertTimeEnd", &p->InsertTimeEnd);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeQuoteField *p)
{
    set_obj(obj, "askPrice", &p->AskPrice);
    set_obj(obj, "bidPrice", &p->BidPrice);
    set_obj(obj, "askVolume", &p->AskVolume);
    set_obj(obj, "bidVolume", &p->BidVolume);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "askOffsetFlag", &p->AskOffsetFlag);
    set_obj(obj, "bidOffsetFlag", &p->BidOffsetFlag);
    set_obj(obj, "askHedgeFlag", &p->AskHedgeFlag);
    set_obj(obj, "bidHedgeFlag", &p->BidHedgeFlag);
    set_obj(obj, "quoteLocalId", &p->QuoteLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "notifySequence", &p->NotifySequence);
    set_obj(obj, "orderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "quoteSysId", &p->QuoteSysID);
    set_obj(obj, "insertDate", &p->InsertDate);
    set_obj(obj, "insertTime", &p->InsertTime);
    set_obj(obj, "cancelTime", &p->CancelTime);
    set_obj(obj, "quoteStatus", &p->QuoteStatus);
    set_obj(obj, "clearingPartId", &p->ClearingPartID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "askOrderSysId", &p->AskOrderSysID);
    set_obj(obj, "bidOrderSysId", &p->BidOrderSysID);
    set_obj(obj, "forQuoteSysId", &p->ForQuoteSysID);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeQuoteField *p)
{
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryQuoteActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeQuoteActionField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "quoteSysId", &p->QuoteSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "actionDate", &p->ActionDate);
    set_obj(obj, "actionTime", &p->ActionTime);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "quoteLocalId", &p->QuoteLocalID);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "orderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeQuoteActionField *p)
{
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcOptionInstrDeltaField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "delta", &p->Delta);
}
static void set_obj(Local<Object>& obj, CThostFtdcForQuoteRspField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "forQuoteSysId", &p->ForQuoteSysID);
    set_obj(obj, "forQuoteTime", &p->ForQuoteTime);
    set_obj(obj, "actionDay", &p->ActionDay);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcStrikeOffsetField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "offset", &p->Offset);
    set_obj(obj, "offsetType", &p->OffsetType);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryStrikeOffsetField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputBatchOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "orderActionRef", &p->OrderActionRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcBatchOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "orderActionRef", &p->OrderActionRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "actionDate", &p->ActionDate);
    set_obj(obj, "actionTime", &p->ActionTime);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "orderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeBatchOrderActionField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "actionDate", &p->ActionDate);
    set_obj(obj, "actionTime", &p->ActionTime);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "orderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBatchOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcCombInstrumentGuardField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "guarantRatio", &p->GuarantRatio);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCombInstrumentGuardField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInputCombActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "combActionRef", &p->CombActionRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "combDirection", &p->CombDirection);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcCombActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "combActionRef", &p->CombActionRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "combDirection", &p->CombDirection);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "actionStatus", &p->ActionStatus);
    set_obj(obj, "notifySequence", &p->NotifySequence);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCombActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeCombActionField *p)
{
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "combDirection", &p->CombDirection);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "actionStatus", &p->ActionStatus);
    set_obj(obj, "notifySequence", &p->NotifySequence);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeCombActionField *p)
{
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcProductExchRateField *p)
{
    set_obj(obj, "productId", &p->ProductID);
    set_obj(obj, "quoteCurrencyId", &p->QuoteCurrencyID);
    set_obj(obj, "exchangeRate", &p->ExchangeRate);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryProductExchRateField *p)
{
    set_obj(obj, "productId", &p->ProductID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryForQuoteParamField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcForQuoteParamField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "lastPrice", &p->LastPrice);
    set_obj(obj, "priceInterval", &p->PriceInterval);
}
static void set_obj(Local<Object>& obj, CThostFtdcMMOptionInstrCommRateField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "openRatioByMoney", &p->OpenRatioByMoney);
    set_obj(obj, "openRatioByVolume", &p->OpenRatioByVolume);
    set_obj(obj, "closeRatioByMoney", &p->CloseRatioByMoney);
    set_obj(obj, "closeRatioByVolume", &p->CloseRatioByVolume);
    set_obj(obj, "closeTodayRatioByMoney", &p->CloseTodayRatioByMoney);
    set_obj(obj, "closeTodayRatioByVolume", &p->CloseTodayRatioByVolume);
    set_obj(obj, "strikeRatioByMoney", &p->StrikeRatioByMoney);
    set_obj(obj, "strikeRatioByVolume", &p->StrikeRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryMMOptionInstrCommRateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMMInstrumentCommissionRateField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "openRatioByMoney", &p->OpenRatioByMoney);
    set_obj(obj, "openRatioByVolume", &p->OpenRatioByVolume);
    set_obj(obj, "closeRatioByMoney", &p->CloseRatioByMoney);
    set_obj(obj, "closeRatioByVolume", &p->CloseRatioByVolume);
    set_obj(obj, "closeTodayRatioByMoney", &p->CloseTodayRatioByMoney);
    set_obj(obj, "closeTodayRatioByVolume", &p->CloseTodayRatioByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryMMInstrumentCommissionRateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentOrderCommRateField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "orderCommByVolume", &p->OrderCommByVolume);
    set_obj(obj, "orderActionCommByVolume", &p->OrderActionCommByVolume);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentOrderCommRateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "lastPrice", &p->LastPrice);
    set_obj(obj, "preSettlementPrice", &p->PreSettlementPrice);
    set_obj(obj, "preClosePrice", &p->PreClosePrice);
    set_obj(obj, "preOpenInterest", &p->PreOpenInterest);
    set_obj(obj, "openPrice", &p->OpenPrice);
    set_obj(obj, "highestPrice", &p->HighestPrice);
    set_obj(obj, "lowestPrice", &p->LowestPrice);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "turnover", &p->Turnover);
    set_obj(obj, "openInterest", &p->OpenInterest);
    set_obj(obj, "closePrice", &p->ClosePrice);
    set_obj(obj, "settlementPrice", &p->SettlementPrice);
    set_obj(obj, "upperLimitPrice", &p->UpperLimitPrice);
    set_obj(obj, "lowerLimitPrice", &p->LowerLimitPrice);
    set_obj(obj, "preDelta", &p->PreDelta);
    set_obj(obj, "currDelta", &p->CurrDelta);
    set_obj(obj, "updateTime", &p->UpdateTime);
    set_obj(obj, "updateMillisec", &p->UpdateMillisec);
    set_obj(obj, "actionDay", &p->ActionDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataBaseField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "preSettlementPrice", &p->PreSettlementPrice);
    set_obj(obj, "preClosePrice", &p->PreClosePrice);
    set_obj(obj, "preOpenInterest", &p->PreOpenInterest);
    set_obj(obj, "preDelta", &p->PreDelta);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataStaticField *p)
{
    set_obj(obj, "openPrice", &p->OpenPrice);
    set_obj(obj, "highestPrice", &p->HighestPrice);
    set_obj(obj, "lowestPrice", &p->LowestPrice);
    set_obj(obj, "closePrice", &p->ClosePrice);
    set_obj(obj, "upperLimitPrice", &p->UpperLimitPrice);
    set_obj(obj, "lowerLimitPrice", &p->LowerLimitPrice);
    set_obj(obj, "settlementPrice", &p->SettlementPrice);
    set_obj(obj, "currDelta", &p->CurrDelta);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataLastMatchField *p)
{
    set_obj(obj, "lastPrice", &p->LastPrice);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "turnover", &p->Turnover);
    set_obj(obj, "openInterest", &p->OpenInterest);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataBestPriceField *p)
{
    set_obj(obj, "bidPrice1", &p->BidPrice1);
    set_obj(obj, "bidVolume1", &p->BidVolume1);
    set_obj(obj, "askPrice1", &p->AskPrice1);
    set_obj(obj, "askVolume1", &p->AskVolume1);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataBid23Field *p)
{
    set_obj(obj, "bidPrice2", &p->BidPrice2);
    set_obj(obj, "bidVolume2", &p->BidVolume2);
    set_obj(obj, "bidPrice3", &p->BidPrice3);
    set_obj(obj, "bidVolume3", &p->BidVolume3);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataAsk23Field *p)
{
    set_obj(obj, "askPrice2", &p->AskPrice2);
    set_obj(obj, "askVolume2", &p->AskVolume2);
    set_obj(obj, "askPrice3", &p->AskPrice3);
    set_obj(obj, "askVolume3", &p->AskVolume3);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataBid45Field *p)
{
    set_obj(obj, "bidPrice4", &p->BidPrice4);
    set_obj(obj, "bidVolume4", &p->BidVolume4);
    set_obj(obj, "bidPrice5", &p->BidPrice5);
    set_obj(obj, "bidVolume5", &p->BidVolume5);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataAsk45Field *p)
{
    set_obj(obj, "askPrice4", &p->AskPrice4);
    set_obj(obj, "askVolume4", &p->AskVolume4);
    set_obj(obj, "askPrice5", &p->AskPrice5);
    set_obj(obj, "askVolume5", &p->AskVolume5);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataUpdateTimeField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "updateTime", &p->UpdateTime);
    set_obj(obj, "updateMillisec", &p->UpdateMillisec);
    set_obj(obj, "actionDay", &p->ActionDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataExchangeField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcSpecificInstrumentField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInstrumentStatusField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "settlementGroupId", &p->SettlementGroupID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "instrumentStatus", &p->InstrumentStatus);
    set_obj(obj, "tradingSegmentSn", &p->TradingSegmentSN);
    set_obj(obj, "enterTime", &p->EnterTime);
    set_obj(obj, "enterReason", &p->EnterReason);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInstrumentStatusField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorAccountField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcPositionProfitAlgorithmField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "algorithm", &p->Algorithm);
    set_obj(obj, "memo", &p->Memo);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcDiscountField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "discount", &p->Discount);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTransferBankField *p)
{
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBrchId", &p->BankBrchID);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferBankField *p)
{
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBrchId", &p->BankBrchID);
    set_obj(obj, "bankName", &p->BankName);
    set_obj(obj, "isActive", &p->IsActive);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorPositionDetailField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorPositionDetailField *p)
{
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "openDate", &p->OpenDate);
    set_obj(obj, "tradeId", &p->TradeID);
    set_obj(obj, "volume", &p->Volume);
    set_obj(obj, "openPrice", &p->OpenPrice);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "tradeType", &p->TradeType);
    set_obj(obj, "combInstrumentId", &p->CombInstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "closeProfitByDate", &p->CloseProfitByDate);
    set_obj(obj, "closeProfitByTrade", &p->CloseProfitByTrade);
    set_obj(obj, "positionProfitByDate", &p->PositionProfitByDate);
    set_obj(obj, "positionProfitByTrade", &p->PositionProfitByTrade);
    set_obj(obj, "margin", &p->Margin);
    set_obj(obj, "exchMargin", &p->ExchMargin);
    set_obj(obj, "marginRateByMoney", &p->MarginRateByMoney);
    set_obj(obj, "marginRateByVolume", &p->MarginRateByVolume);
    set_obj(obj, "lastSettlementPrice", &p->LastSettlementPrice);
    set_obj(obj, "settlementPrice", &p->SettlementPrice);
    set_obj(obj, "closeVolume", &p->CloseVolume);
    set_obj(obj, "closeAmount", &p->CloseAmount);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingAccountPasswordField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMDTraderOfferField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "traderConnectStatus", &p->TraderConnectStatus);
    set_obj(obj, "connectRequestDate", &p->ConnectRequestDate);
    set_obj(obj, "connectRequestTime", &p->ConnectRequestTime);
    set_obj(obj, "lastReportDate", &p->LastReportDate);
    set_obj(obj, "lastReportTime", &p->LastReportTime);
    set_obj(obj, "connectDate", &p->ConnectDate);
    set_obj(obj, "connectTime", &p->ConnectTime);
    set_obj(obj, "startDate", &p->StartDate);
    set_obj(obj, "startTime", &p->StartTime);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "maxTradeId", &p->MaxTradeID);
    set_obj(obj, "maxOrderMessageReference", &p->MaxOrderMessageReference);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryMDTraderOfferField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "traderId", &p->TraderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryNoticeField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcNoticeField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "content", &p->Content);
    set_obj(obj, "sequenceLabel", &p->SequenceLabel);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserRightField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "userRightType", &p->UserRightType);
    set_obj(obj, "isForbidden", &p->IsForbidden);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySettlementInfoConfirmField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcLoadSettlementInfoField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerWithdrawAlgorithmField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "withdrawAlgorithm", &p->WithdrawAlgorithm);
    set_obj(obj, "usingRatio", &p->UsingRatio);
    set_obj(obj, "includeCloseProfit", &p->IncludeCloseProfit);
    set_obj(obj, "allWithoutTrade", &p->AllWithoutTrade);
    set_obj(obj, "availIncludeCloseProfit", &p->AvailIncludeCloseProfit);
    set_obj(obj, "isBrokerUserEvent", &p->IsBrokerUserEvent);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "fundMortgageRatio", &p->FundMortgageRatio);
    set_obj(obj, "balanceAlgorithm", &p->BalanceAlgorithm);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingAccountPasswordUpdateV1Field *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "oldPassword", &p->OldPassword);
    set_obj(obj, "newPassword", &p->NewPassword);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingAccountPasswordUpdateField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "oldPassword", &p->OldPassword);
    set_obj(obj, "newPassword", &p->NewPassword);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCombinationLegField *p)
{
    set_obj(obj, "combInstrumentId", &p->CombInstrumentID);
    set_obj(obj, "legId", &p->LegID);
    set_obj(obj, "legInstrumentId", &p->LegInstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySyncStatusField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
}
static void set_obj(Local<Object>& obj, CThostFtdcCombinationLegField *p)
{
    set_obj(obj, "combInstrumentId", &p->CombInstrumentID);
    set_obj(obj, "legId", &p->LegID);
    set_obj(obj, "legInstrumentId", &p->LegInstrumentID);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "legMultiple", &p->LegMultiple);
    set_obj(obj, "implyLevel", &p->ImplyLevel);
}
static void set_obj(Local<Object>& obj, CThostFtdcSyncStatusField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "dataSyncStatus", &p->DataSyncStatus);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryLinkManField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcLinkManField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "personType", &p->PersonType);
    set_obj(obj, "identifiedCardType", &p->IdentifiedCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "personName", &p->PersonName);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "zipCode", &p->ZipCode);
    set_obj(obj, "priority", &p->Priority);
    set_obj(obj, "uOAZipCode", &p->UOAZipCode);
    set_obj(obj, "personFullName", &p->PersonFullName);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerUserEventField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "userEventType", &p->UserEventType);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserEventField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "userEventType", &p->UserEventType);
    set_obj(obj, "eventSequenceNo", &p->EventSequenceNo);
    set_obj(obj, "eventDate", &p->EventDate);
    set_obj(obj, "eventTime", &p->EventTime);
    set_obj(obj, "userEventInfo", &p->UserEventInfo);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryContractBankField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBrchId", &p->BankBrchID);
}
static void set_obj(Local<Object>& obj, CThostFtdcContractBankField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBrchId", &p->BankBrchID);
    set_obj(obj, "bankName", &p->BankName);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorPositionCombineDetailField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "openDate", &p->OpenDate);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "comTradeId", &p->ComTradeID);
    set_obj(obj, "tradeId", &p->TradeID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "totalAmt", &p->TotalAmt);
    set_obj(obj, "margin", &p->Margin);
    set_obj(obj, "exchMargin", &p->ExchMargin);
    set_obj(obj, "marginRateByMoney", &p->MarginRateByMoney);
    set_obj(obj, "marginRateByVolume", &p->MarginRateByVolume);
    set_obj(obj, "legId", &p->LegID);
    set_obj(obj, "legMultiple", &p->LegMultiple);
    set_obj(obj, "combInstrumentId", &p->CombInstrumentID);
    set_obj(obj, "tradeGroupId", &p->TradeGroupID);
}
static void set_obj(Local<Object>& obj, CThostFtdcParkedOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "orderRef", &p->OrderRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "orderPriceType", &p->OrderPriceType);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "combOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "combHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "timeCondition", &p->TimeCondition);
    set_obj(obj, "gtdDate", &p->GTDDate);
    set_obj(obj, "volumeCondition", &p->VolumeCondition);
    set_obj(obj, "minVolume", &p->MinVolume);
    set_obj(obj, "contingentCondition", &p->ContingentCondition);
    set_obj(obj, "stopPrice", &p->StopPrice);
    set_obj(obj, "forceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "isAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "userForceClose", &p->UserForceClose);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "parkedOrderId", &p->ParkedOrderID);
    set_obj(obj, "userType", &p->UserType);
    set_obj(obj, "status", &p->Status);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
    set_obj(obj, "isSwapOrder", &p->IsSwapOrder);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcParkedOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "orderActionRef", &p->OrderActionRef);
    set_obj(obj, "orderRef", &p->OrderRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeChange", &p->VolumeChange);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "parkedOrderActionId", &p->ParkedOrderActionID);
    set_obj(obj, "userType", &p->UserType);
    set_obj(obj, "status", &p->Status);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryParkedOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryParkedOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRemoveParkedOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "parkedOrderId", &p->ParkedOrderID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRemoveParkedOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "parkedOrderActionId", &p->ParkedOrderActionID);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorWithdrawAlgorithmField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "usingRatio", &p->UsingRatio);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "fundMortgageRatio", &p->FundMortgageRatio);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorPositionCombineDetailField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "combInstrumentId", &p->CombInstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarketDataAveragePriceField *p)
{
    set_obj(obj, "averagePrice", &p->AveragePrice);
}
static void set_obj(Local<Object>& obj, CThostFtdcVerifyInvestorPasswordField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "password", &p->Password);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserIPField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "iPMask", &p->IPMask);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingNoticeInfoField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "sendTime", &p->SendTime);
    set_obj(obj, "fieldContent", &p->FieldContent);
    set_obj(obj, "sequenceSeries", &p->SequenceSeries);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingNoticeField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorRange", &p->InvestorRange);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "sequenceSeries", &p->SequenceSeries);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "sendTime", &p->SendTime);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "fieldContent", &p->FieldContent);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTradingNoticeField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryErrOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcErrOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "orderRef", &p->OrderRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "orderPriceType", &p->OrderPriceType);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "combOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "combHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "timeCondition", &p->TimeCondition);
    set_obj(obj, "gtdDate", &p->GTDDate);
    set_obj(obj, "volumeCondition", &p->VolumeCondition);
    set_obj(obj, "minVolume", &p->MinVolume);
    set_obj(obj, "contingentCondition", &p->ContingentCondition);
    set_obj(obj, "stopPrice", &p->StopPrice);
    set_obj(obj, "forceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "isAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "userForceClose", &p->UserForceClose);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
    set_obj(obj, "isSwapOrder", &p->IsSwapOrder);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcErrorConditionalOrderField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "orderRef", &p->OrderRef);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "orderPriceType", &p->OrderPriceType);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "combOffsetFlag", &p->CombOffsetFlag);
    set_obj(obj, "combHedgeFlag", &p->CombHedgeFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal);
    set_obj(obj, "timeCondition", &p->TimeCondition);
    set_obj(obj, "gtdDate", &p->GTDDate);
    set_obj(obj, "volumeCondition", &p->VolumeCondition);
    set_obj(obj, "minVolume", &p->MinVolume);
    set_obj(obj, "contingentCondition", &p->ContingentCondition);
    set_obj(obj, "stopPrice", &p->StopPrice);
    set_obj(obj, "forceCloseReason", &p->ForceCloseReason);
    set_obj(obj, "isAutoSuspend", &p->IsAutoSuspend);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "exchangeInstId", &p->ExchangeInstID);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderSubmitStatus", &p->OrderSubmitStatus);
    set_obj(obj, "notifySequence", &p->NotifySequence);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "orderSource", &p->OrderSource);
    set_obj(obj, "orderStatus", &p->OrderStatus);
    set_obj(obj, "orderType", &p->OrderType);
    set_obj(obj, "volumeTraded", &p->VolumeTraded);
    set_obj(obj, "volumeTotal", &p->VolumeTotal);
    set_obj(obj, "insertDate", &p->InsertDate);
    set_obj(obj, "insertTime", &p->InsertTime);
    set_obj(obj, "activeTime", &p->ActiveTime);
    set_obj(obj, "suspendTime", &p->SuspendTime);
    set_obj(obj, "updateTime", &p->UpdateTime);
    set_obj(obj, "cancelTime", &p->CancelTime);
    set_obj(obj, "activeTraderId", &p->ActiveTraderID);
    set_obj(obj, "clearingPartId", &p->ClearingPartID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "userForceClose", &p->UserForceClose);
    set_obj(obj, "activeUserId", &p->ActiveUserID);
    set_obj(obj, "brokerOrderSeq", &p->BrokerOrderSeq);
    set_obj(obj, "relativeOrderSysId", &p->RelativeOrderSysID);
    set_obj(obj, "zceTotalTradedVolume", &p->ZCETotalTradedVolume);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
    set_obj(obj, "isSwapOrder", &p->IsSwapOrder);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryErrOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcErrOrderActionField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "orderActionRef", &p->OrderActionRef);
    set_obj(obj, "orderRef", &p->OrderRef);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "frontId", &p->FrontID);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "orderSysId", &p->OrderSysID);
    set_obj(obj, "actionFlag", &p->ActionFlag);
    set_obj(obj, "limitPrice", &p->LimitPrice);
    set_obj(obj, "volumeChange", &p->VolumeChange);
    set_obj(obj, "actionDate", &p->ActionDate);
    set_obj(obj, "actionTime", &p->ActionTime);
    set_obj(obj, "traderId", &p->TraderID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "orderLocalId", &p->OrderLocalID);
    set_obj(obj, "actionLocalId", &p->ActionLocalID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "clientId", &p->ClientID);
    set_obj(obj, "businessUnit", &p->BusinessUnit);
    set_obj(obj, "orderActionStatus", &p->OrderActionStatus);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "statusMsg", &p->StatusMsg);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "branchId", &p->BranchID);
    set_obj(obj, "investUnitId", &p->InvestUnitID);
    set_obj(obj, "iPAddress", &p->IPAddress);
    set_obj(obj, "macAddress", &p->MacAddress);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryExchangeSequenceField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcExchangeSequenceField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "marketStatus", &p->MarketStatus);
}
static void set_obj(Local<Object>& obj, CThostFtdcQueryMaxOrderVolumeWithPriceField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "offsetFlag", &p->OffsetFlag);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "maxVolume", &p->MaxVolume);
    set_obj(obj, "price", &p->Price);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerTradingParamsField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerTradingParamsField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "marginPriceType", &p->MarginPriceType);
    set_obj(obj, "algorithm", &p->Algorithm);
    set_obj(obj, "availIncludeCloseProfit", &p->AvailIncludeCloseProfit);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "optionRoyaltyPriceType", &p->OptionRoyaltyPriceType);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBrokerTradingAlgosField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerTradingAlgosField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "handlePositionAlgoId", &p->HandlePositionAlgoID);
    set_obj(obj, "findMarginRateAlgoId", &p->FindMarginRateAlgoID);
    set_obj(obj, "handleTradingAccountAlgoId", &p->HandleTradingAccountAlgoID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQueryBrokerDepositField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerDepositField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "preBalance", &p->PreBalance);
    set_obj(obj, "currMargin", &p->CurrMargin);
    set_obj(obj, "closeProfit", &p->CloseProfit);
    set_obj(obj, "balance", &p->Balance);
    set_obj(obj, "deposit", &p->Deposit);
    set_obj(obj, "withdraw", &p->Withdraw);
    set_obj(obj, "available", &p->Available);
    set_obj(obj, "reserve", &p->Reserve);
    set_obj(obj, "frozenMargin", &p->FrozenMargin);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCFMMCBrokerKeyField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcCFMMCBrokerKeyField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "createDate", &p->CreateDate);
    set_obj(obj, "createTime", &p->CreateTime);
    set_obj(obj, "keyId", &p->KeyID);
    set_obj(obj, "currentKey", &p->CurrentKey);
    set_obj(obj, "keyKind", &p->KeyKind);
}
static void set_obj(Local<Object>& obj, CThostFtdcCFMMCTradingAccountKeyField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "keyId", &p->KeyID);
    set_obj(obj, "currentKey", &p->CurrentKey);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCFMMCTradingAccountKeyField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserOTPParamField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "otpVendorsId", &p->OTPVendorsID);
    set_obj(obj, "serialNumber", &p->SerialNumber);
    set_obj(obj, "authKey", &p->AuthKey);
    set_obj(obj, "lastDrift", &p->LastDrift);
    set_obj(obj, "lastSuccess", &p->LastSuccess);
    set_obj(obj, "otpType", &p->OTPType);
}
static void set_obj(Local<Object>& obj, CThostFtdcManualSyncBrokerUserOTPField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "otpType", &p->OTPType);
    set_obj(obj, "firstOtp", &p->FirstOTP);
    set_obj(obj, "secondOtp", &p->SecondOTP);
}
static void set_obj(Local<Object>& obj, CThostFtdcCommRateModelField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "commModelId", &p->CommModelID);
    set_obj(obj, "commModelName", &p->CommModelName);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryCommRateModelField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "commModelId", &p->CommModelID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMarginModelField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "marginModelId", &p->MarginModelID);
    set_obj(obj, "marginModelName", &p->MarginModelName);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryMarginModelField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "marginModelId", &p->MarginModelID);
}
static void set_obj(Local<Object>& obj, CThostFtdcEWarrantOffsetField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "direction", &p->Direction);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
    set_obj(obj, "volume", &p->Volume);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryEWarrantOffsetField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryInvestorProductGroupMarginField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "productGroupId", &p->ProductGroupID);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
}
static void set_obj(Local<Object>& obj, CThostFtdcInvestorProductGroupMarginField *p)
{
    set_obj(obj, "productGroupId", &p->ProductGroupID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "settlementId", &p->SettlementID);
    set_obj(obj, "frozenMargin", &p->FrozenMargin);
    set_obj(obj, "longFrozenMargin", &p->LongFrozenMargin);
    set_obj(obj, "shortFrozenMargin", &p->ShortFrozenMargin);
    set_obj(obj, "useMargin", &p->UseMargin);
    set_obj(obj, "longUseMargin", &p->LongUseMargin);
    set_obj(obj, "shortUseMargin", &p->ShortUseMargin);
    set_obj(obj, "exchMargin", &p->ExchMargin);
    set_obj(obj, "longExchMargin", &p->LongExchMargin);
    set_obj(obj, "shortExchMargin", &p->ShortExchMargin);
    set_obj(obj, "closeProfit", &p->CloseProfit);
    set_obj(obj, "frozenCommission", &p->FrozenCommission);
    set_obj(obj, "commission", &p->Commission);
    set_obj(obj, "frozenCash", &p->FrozenCash);
    set_obj(obj, "cashIn", &p->CashIn);
    set_obj(obj, "positionProfit", &p->PositionProfit);
    set_obj(obj, "offsetAmount", &p->OffsetAmount);
    set_obj(obj, "longOffsetAmount", &p->LongOffsetAmount);
    set_obj(obj, "shortOffsetAmount", &p->ShortOffsetAmount);
    set_obj(obj, "exchOffsetAmount", &p->ExchOffsetAmount);
    set_obj(obj, "longExchOffsetAmount", &p->LongExchOffsetAmount);
    set_obj(obj, "shortExchOffsetAmount", &p->ShortExchOffsetAmount);
    set_obj(obj, "hedgeFlag", &p->HedgeFlag);
}
static void set_obj(Local<Object>& obj, CThostFtdcQueryCFMMCTradingAccountTokenField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}
static void set_obj(Local<Object>& obj, CThostFtdcCFMMCTradingAccountTokenField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "participantId", &p->ParticipantID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "keyId", &p->KeyID);
    set_obj(obj, "token", &p->Token);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryProductGroupField *p)
{
    set_obj(obj, "productId", &p->ProductID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
}
static void set_obj(Local<Object>& obj, CThostFtdcProductGroupField *p)
{
    set_obj(obj, "productId", &p->ProductID);
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "productGroupId", &p->ProductGroupID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBulletinField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "bulletinId", &p->BulletinID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "newsType", &p->NewsType);
    set_obj(obj, "newsUrgency", &p->NewsUrgency);
    set_obj(obj, "sendTime", &p->SendTime);
    set_obj(obj, "abstract", &p->Abstract);
    set_obj(obj, "comeFrom", &p->ComeFrom);
    set_obj(obj, "content", &p->Content);
    set_obj(obj, "uRLLink", &p->URLLink);
    set_obj(obj, "marketId", &p->MarketID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryBulletinField *p)
{
    set_obj(obj, "exchangeId", &p->ExchangeID);
    set_obj(obj, "bulletinId", &p->BulletinID);
    set_obj(obj, "sequenceNo", &p->SequenceNo);
    set_obj(obj, "newsType", &p->NewsType);
    set_obj(obj, "newsUrgency", &p->NewsUrgency);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqOpenAccountField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "gender", &p->Gender);
    set_obj(obj, "countryCode", &p->CountryCode);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "zipCode", &p->ZipCode);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "mobilePhone", &p->MobilePhone);
    set_obj(obj, "fax", &p->Fax);
    set_obj(obj, "eMail", &p->EMail);
    set_obj(obj, "moneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "cashExchangeCode", &p->CashExchangeCode);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "userId", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqCancelAccountField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "gender", &p->Gender);
    set_obj(obj, "countryCode", &p->CountryCode);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "zipCode", &p->ZipCode);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "mobilePhone", &p->MobilePhone);
    set_obj(obj, "fax", &p->Fax);
    set_obj(obj, "eMail", &p->EMail);
    set_obj(obj, "moneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "cashExchangeCode", &p->CashExchangeCode);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "userId", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqChangeAccountField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "gender", &p->Gender);
    set_obj(obj, "countryCode", &p->CountryCode);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "zipCode", &p->ZipCode);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "mobilePhone", &p->MobilePhone);
    set_obj(obj, "fax", &p->Fax);
    set_obj(obj, "eMail", &p->EMail);
    set_obj(obj, "moneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "newBankAccount", &p->NewBankAccount);
    set_obj(obj, "newBankPassWord", &p->NewBankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "digest", &p->Digest);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqTransferField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "futureSerial", &p->FutureSerial);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "tradeAmount", &p->TradeAmount);
    set_obj(obj, "futureFetchAmount", &p->FutureFetchAmount);
    set_obj(obj, "feePayFlag", &p->FeePayFlag);
    set_obj(obj, "custFee", &p->CustFee);
    set_obj(obj, "brokerFee", &p->BrokerFee);
    set_obj(obj, "message", &p->Message);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "transferStatus", &p->TransferStatus);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspTransferField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "futureSerial", &p->FutureSerial);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "tradeAmount", &p->TradeAmount);
    set_obj(obj, "futureFetchAmount", &p->FutureFetchAmount);
    set_obj(obj, "feePayFlag", &p->FeePayFlag);
    set_obj(obj, "custFee", &p->CustFee);
    set_obj(obj, "brokerFee", &p->BrokerFee);
    set_obj(obj, "message", &p->Message);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "transferStatus", &p->TransferStatus);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqRepealField *p)
{
    set_obj(obj, "repealTimeInterval", &p->RepealTimeInterval);
    set_obj(obj, "repealedTimes", &p->RepealedTimes);
    set_obj(obj, "bankRepealFlag", &p->BankRepealFlag);
    set_obj(obj, "brokerRepealFlag", &p->BrokerRepealFlag);
    set_obj(obj, "plateRepealSerial", &p->PlateRepealSerial);
    set_obj(obj, "bankRepealSerial", &p->BankRepealSerial);
    set_obj(obj, "futureRepealSerial", &p->FutureRepealSerial);
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "futureSerial", &p->FutureSerial);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "tradeAmount", &p->TradeAmount);
    set_obj(obj, "futureFetchAmount", &p->FutureFetchAmount);
    set_obj(obj, "feePayFlag", &p->FeePayFlag);
    set_obj(obj, "custFee", &p->CustFee);
    set_obj(obj, "brokerFee", &p->BrokerFee);
    set_obj(obj, "message", &p->Message);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "transferStatus", &p->TransferStatus);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspRepealField *p)
{
    set_obj(obj, "repealTimeInterval", &p->RepealTimeInterval);
    set_obj(obj, "repealedTimes", &p->RepealedTimes);
    set_obj(obj, "bankRepealFlag", &p->BankRepealFlag);
    set_obj(obj, "brokerRepealFlag", &p->BrokerRepealFlag);
    set_obj(obj, "plateRepealSerial", &p->PlateRepealSerial);
    set_obj(obj, "bankRepealSerial", &p->BankRepealSerial);
    set_obj(obj, "futureRepealSerial", &p->FutureRepealSerial);
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "futureSerial", &p->FutureSerial);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "tradeAmount", &p->TradeAmount);
    set_obj(obj, "futureFetchAmount", &p->FutureFetchAmount);
    set_obj(obj, "feePayFlag", &p->FeePayFlag);
    set_obj(obj, "custFee", &p->CustFee);
    set_obj(obj, "brokerFee", &p->BrokerFee);
    set_obj(obj, "message", &p->Message);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "transferStatus", &p->TransferStatus);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqQueryAccountField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "futureSerial", &p->FutureSerial);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspQueryAccountField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "futureSerial", &p->FutureSerial);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "bankUseAmount", &p->BankUseAmount);
    set_obj(obj, "bankFetchAmount", &p->BankFetchAmount);
}
static void set_obj(Local<Object>& obj, CThostFtdcFutureSignIOField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspFutureSignInField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
    set_obj(obj, "pinKey", &p->PinKey);
    set_obj(obj, "macKey", &p->MacKey);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqFutureSignOutField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspFutureSignOutField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqQueryTradeResultBySerialField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "reference", &p->Reference);
    set_obj(obj, "refrenceIssureType", &p->RefrenceIssureType);
    set_obj(obj, "refrenceIssure", &p->RefrenceIssure);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "tradeAmount", &p->TradeAmount);
    set_obj(obj, "digest", &p->Digest);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspQueryTradeResultBySerialField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
    set_obj(obj, "reference", &p->Reference);
    set_obj(obj, "refrenceIssureType", &p->RefrenceIssureType);
    set_obj(obj, "refrenceIssure", &p->RefrenceIssure);
    set_obj(obj, "originReturnCode", &p->OriginReturnCode);
    set_obj(obj, "originDescrInfoForReturnCode", &p->OriginDescrInfoForReturnCode);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "tradeAmount", &p->TradeAmount);
    set_obj(obj, "digest", &p->Digest);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqDayEndFileReadyField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "fileBusinessCode", &p->FileBusinessCode);
    set_obj(obj, "digest", &p->Digest);
}
static void set_obj(Local<Object>& obj, CThostFtdcReturnResultField *p)
{
    set_obj(obj, "returnCode", &p->ReturnCode);
    set_obj(obj, "descrInfoForReturnCode", &p->DescrInfoForReturnCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcVerifyFuturePasswordField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcVerifyCustInfoField *p)
{
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "custType", &p->CustType);
}
static void set_obj(Local<Object>& obj, CThostFtdcVerifyFuturePasswordAndCustInfoField *p)
{
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcDepositResultInformField *p)
{
    set_obj(obj, "depositSeqNo", &p->DepositSeqNo);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "deposit", &p->Deposit);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "returnCode", &p->ReturnCode);
    set_obj(obj, "descrInfoForReturnCode", &p->DescrInfoForReturnCode);
}
static void set_obj(Local<Object>& obj, CThostFtdcReqSyncKeyField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "message", &p->Message);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
}
static void set_obj(Local<Object>& obj, CThostFtdcRspSyncKeyField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "message", &p->Message);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcNotifyQueryAccountField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "futureSerial", &p->FutureSerial);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "bankUseAmount", &p->BankUseAmount);
    set_obj(obj, "bankFetchAmount", &p->BankFetchAmount);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcTransferSerialField *p)
{
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "futureAccType", &p->FutureAccType);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "futureSerial", &p->FutureSerial);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "tradeAmount", &p->TradeAmount);
    set_obj(obj, "custFee", &p->CustFee);
    set_obj(obj, "brokerFee", &p->BrokerFee);
    set_obj(obj, "availabilityFlag", &p->AvailabilityFlag);
    set_obj(obj, "operatorCode", &p->OperatorCode);
    set_obj(obj, "bankNewAccount", &p->BankNewAccount);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryTransferSerialField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcNotifyFutureSignInField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
    set_obj(obj, "pinKey", &p->PinKey);
    set_obj(obj, "macKey", &p->MacKey);
}
static void set_obj(Local<Object>& obj, CThostFtdcNotifyFutureSignOutField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcNotifySyncKeyField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "message", &p->Message);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "requestId", &p->RequestID);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryAccountregisterField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcAccountregisterField *p)
{
    set_obj(obj, "tradeDay", &p->TradeDay);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "openOrDestroy", &p->OpenOrDestroy);
    set_obj(obj, "regDate", &p->RegDate);
    set_obj(obj, "outDate", &p->OutDate);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "bankAccType", &p->BankAccType);
}
static void set_obj(Local<Object>& obj, CThostFtdcOpenAccountField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "gender", &p->Gender);
    set_obj(obj, "countryCode", &p->CountryCode);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "zipCode", &p->ZipCode);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "mobilePhone", &p->MobilePhone);
    set_obj(obj, "fax", &p->Fax);
    set_obj(obj, "eMail", &p->EMail);
    set_obj(obj, "moneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "cashExchangeCode", &p->CashExchangeCode);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcCancelAccountField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "gender", &p->Gender);
    set_obj(obj, "countryCode", &p->CountryCode);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "zipCode", &p->ZipCode);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "mobilePhone", &p->MobilePhone);
    set_obj(obj, "fax", &p->Fax);
    set_obj(obj, "eMail", &p->EMail);
    set_obj(obj, "moneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "cashExchangeCode", &p->CashExchangeCode);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "deviceId", &p->DeviceID);
    set_obj(obj, "bankSecuAccType", &p->BankSecuAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankSecuAcc", &p->BankSecuAcc);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "operNo", &p->OperNo);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcChangeAccountField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "gender", &p->Gender);
    set_obj(obj, "countryCode", &p->CountryCode);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "zipCode", &p->ZipCode);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "mobilePhone", &p->MobilePhone);
    set_obj(obj, "fax", &p->Fax);
    set_obj(obj, "eMail", &p->EMail);
    set_obj(obj, "moneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "newBankAccount", &p->NewBankAccount);
    set_obj(obj, "newBankPassWord", &p->NewBankPassWord);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "bankPwdFlag", &p->BankPwdFlag);
    set_obj(obj, "secuPwdFlag", &p->SecuPwdFlag);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcSecAgentACIDMapField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "brokerSecAgentId", &p->BrokerSecAgentID);
}
static void set_obj(Local<Object>& obj, CThostFtdcQrySecAgentACIDMapField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcUserRightsAssignField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "dRIdentityId", &p->DRIdentityID);
}
static void set_obj(Local<Object>& obj, CThostFtdcBrokerUserRightAssignField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "dRIdentityId", &p->DRIdentityID);
    set_obj(obj, "tradeable", &p->Tradeable);
}
static void set_obj(Local<Object>& obj, CThostFtdcDRTransferField *p)
{
    set_obj(obj, "origDRIdentityId", &p->OrigDRIdentityID);
    set_obj(obj, "destDRIdentityId", &p->DestDRIdentityID);
    set_obj(obj, "origBrokerId", &p->OrigBrokerID);
    set_obj(obj, "destBrokerId", &p->DestBrokerID);
}
static void set_obj(Local<Object>& obj, CThostFtdcFensUserInfoField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "loginMode", &p->LoginMode);
}
static void set_obj(Local<Object>& obj, CThostFtdcCurrTransferIdentityField *p)
{
    set_obj(obj, "identityId", &p->IdentityID);
}
static void set_obj(Local<Object>& obj, CThostFtdcLoginForbiddenUserField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "iPAddress", &p->IPAddress);
}
static void set_obj(Local<Object>& obj, CThostFtdcQryLoginForbiddenUserField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
}
static void set_obj(Local<Object>& obj, CThostFtdcMulticastGroupInfoField *p)
{
    set_obj(obj, "groupIp", &p->GroupIP);
    set_obj(obj, "groupPort", &p->GroupPort);
    set_obj(obj, "sourceIp", &p->SourceIP);
}
static void set_obj(Local<Object>& obj, CThostFtdcTradingAccountReserveField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "reserve", &p->Reserve);
    set_obj(obj, "currencyId", &p->CurrencyID);
}
static void set_obj(Local<Object>& obj, CThostFtdcReserveOpenAccountConfirmField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "gender", &p->Gender);
    set_obj(obj, "countryCode", &p->CountryCode);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "zipCode", &p->ZipCode);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "mobilePhone", &p->MobilePhone);
    set_obj(obj, "fax", &p->Fax);
    set_obj(obj, "eMail", &p->EMail);
    set_obj(obj, "moneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "accountId", &p->AccountID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "bankReserveOpenSeq", &p->BankReserveOpenSeq);
    set_obj(obj, "bookDate", &p->BookDate);
    set_obj(obj, "bookPsw", &p->BookPsw);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}
static void set_obj(Local<Object>& obj, CThostFtdcReserveOpenAccountField *p)
{
    set_obj(obj, "tradeCode", &p->TradeCode);
    set_obj(obj, "bankId", &p->BankID);
    set_obj(obj, "bankBranchId", &p->BankBranchID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerBranchId", &p->BrokerBranchID);
    set_obj(obj, "tradeDate", &p->TradeDate);
    set_obj(obj, "tradeTime", &p->TradeTime);
    set_obj(obj, "bankSerial", &p->BankSerial);
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "plateSerial", &p->PlateSerial);
    set_obj(obj, "lastFragment", &p->LastFragment);
    set_obj(obj, "sessionId", &p->SessionID);
    set_obj(obj, "customerName", &p->CustomerName);
    set_obj(obj, "idCardType", &p->IdCardType);
    set_obj(obj, "identifiedCardNo", &p->IdentifiedCardNo);
    set_obj(obj, "gender", &p->Gender);
    set_obj(obj, "countryCode", &p->CountryCode);
    set_obj(obj, "custType", &p->CustType);
    set_obj(obj, "address", &p->Address);
    set_obj(obj, "zipCode", &p->ZipCode);
    set_obj(obj, "telephone", &p->Telephone);
    set_obj(obj, "mobilePhone", &p->MobilePhone);
    set_obj(obj, "fax", &p->Fax);
    set_obj(obj, "eMail", &p->EMail);
    set_obj(obj, "moneyAccountStatus", &p->MoneyAccountStatus);
    set_obj(obj, "bankAccount", &p->BankAccount);
    set_obj(obj, "bankPassWord", &p->BankPassWord);
    set_obj(obj, "installId", &p->InstallID);
    set_obj(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "digest", &p->Digest);
    set_obj(obj, "bankAccType", &p->BankAccType);
    set_obj(obj, "brokerIdByBank", &p->BrokerIDByBank);
    set_obj(obj, "tId", &p->TID);
    set_obj(obj, "reserveOpenAccStas", &p->ReserveOpenAccStas);
    set_obj(obj, "errorId", &p->ErrorID);
    set_obj(obj, "errorMsg", &p->ErrorMsg);
}

// TODO 穿透式监管新增结构体

static void set_obj(Local<Object>& obj, CThostFtdcRspUserAuthMethodField *p)
{
    set_obj(obj, "usableAuthMethod", &p->UsableAuthMethod);
}

static void set_obj(Local<Object>& obj, CThostFtdcRspGenUserCaptchaField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "captchaInfoLen", &p->CaptchaInfoLen);
    set_obj(obj, "captchaInfo", &p->CaptchaInfo);
}

static void set_obj(Local<Object>& obj, CThostFtdcRspGenUserTextField *p)
{
    set_obj(obj, "userTextSeq", &p->UserTextSeq);
}

static void set_obj(Local<Object>& obj, CThostFtdcSecAgentTradeInfoField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerSecAgentId", &p->BrokerSecAgentID);
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "longCustomerName", &p->LongCustomerName);
}

static void set_obj(Local<Object>& obj, CThostFtdcMulticastInstrumentField *p)
{
    set_obj(obj, "topicId", &p->TopicID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
    set_obj(obj, "instrumentNo", &p->InstrumentNo);
    set_obj(obj, "codePrice", &p->CodePrice);
    set_obj(obj, "volumeMultiple", &p->VolumeMultiple);
    set_obj(obj, "priceTick", &p->PriceTick);
}

static void set_obj(Local<Object>& obj, CThostFtdcQryMulticastInstrumentField *p)
{
    set_obj(obj, "topicId", &p->TopicID);
    set_obj(obj, "instrumentId", &p->InstrumentID);
}

static void set_obj(Local<Object>& obj, CThostFtdcUserSystemInfoField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "clientSystemInfoLen", &p->ClientSystemInfoLen);
    set_obj(obj, "clientSystemInfo", &p->ClientSystemInfo);
    set_obj(obj, "clientPublicIp", &p->ClientPublicIP);
    set_obj(obj, "clientIpPort", &p->ClientIPPort);
    set_obj(obj, "clientLoginTime", &p->ClientLoginTime);
    set_obj(obj, "clientAppId", &p->ClientAppID);
}

static void set_obj(Local<Object>& obj, CThostFtdcReqUserAuthMethodField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
}

static void set_obj(Local<Object>& obj, CThostFtdcReqGenUserCaptchaField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
}

static void set_obj(Local<Object>& obj, CThostFtdcReqGenUserTextField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
}

static void set_obj(Local<Object>& obj, CThostFtdcReqUserLoginWithCaptchaField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "interfaceProductInfo", &p->InterfaceProductInfo);
    set_obj(obj, "protocolInfo", &p->ProtocolInfo);
    set_obj(obj, "macAddress", &p->MacAddress);
    set_obj(obj, "clientIpAddress", &p->ClientIPAddress);
    set_obj(obj, "loginRemark", &p->LoginRemark);
    set_obj(obj, "captcha", &p->Captcha);
    set_obj(obj, "clientIpPort", &p->ClientIPPort);
}

static void set_obj(Local<Object>& obj, CThostFtdcReqUserLoginWithTextField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "interfaceProductInfo", &p->InterfaceProductInfo);
    set_obj(obj, "protocolInfo", &p->ProtocolInfo);
    set_obj(obj, "macAddress", &p->MacAddress);
    set_obj(obj, "clientIpAddress", &p->ClientIPAddress);
    set_obj(obj, "loginRemark", &p->LoginRemark);
    set_obj(obj, "text", &p->Text);
    set_obj(obj, "clientIpPort", &p->ClientIPPort);
}

static void set_obj(Local<Object>& obj, CThostFtdcReqUserLoginWithOTPField *p)
{
    set_obj(obj, "tradingDay", &p->TradingDay);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "userId", &p->UserID);
    set_obj(obj, "password", &p->Password);
    set_obj(obj, "userProductInfo", &p->UserProductInfo);
    set_obj(obj, "interfaceProductInfo", &p->InterfaceProductInfo);
    set_obj(obj, "protocolInfo", &p->ProtocolInfo);
    set_obj(obj, "macAddress", &p->MacAddress);
    set_obj(obj, "clientIpAddress", &p->ClientIPAddress);
    set_obj(obj, "loginRemark", &p->LoginRemark);
    set_obj(obj, "otpPassword", &p->OTPPassword);
    set_obj(obj, "clientIpPort", &p->ClientIPPort);
}

static void set_obj(Local<Object>& obj, CThostFtdcQrySecAgentTradeInfoField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "brokerSecAgentId", &p->BrokerSecAgentID);
}

static void set_obj(Local<Object>& obj, CThostFtdcSecAgentCheckModeField *p)
{
    set_obj(obj, "investorId", &p->InvestorID);
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "currencyId", &p->CurrencyID);
    set_obj(obj, "brokerSecAgentId", &p->BrokerSecAgentID);
    set_obj(obj, "checkSelfAccount", &p->CheckSelfAccount);
}

static void set_obj(Local<Object>& obj, CThostFtdcQrySecAgentCheckModeField *p)
{
    set_obj(obj, "brokerId", &p->BrokerID);
    set_obj(obj, "investorId", &p->InvestorID);
}

////////////////////////////// set_struct /////////////////////////////////////////////

static void set_struct(Local<Object>& obj, CThostFtdcDisseminationField *p)
{
    set_struct(obj, "sequenceSeries", &p->SequenceSeries, sizeof(p->SequenceSeries));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqUserLoginField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "interfaceProductInfo", &p->InterfaceProductInfo, sizeof(p->InterfaceProductInfo));
    set_struct(obj, "protocolInfo", &p->ProtocolInfo, sizeof(p->ProtocolInfo));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "oneTimePassword", &p->OneTimePassword, sizeof(p->OneTimePassword));
    set_struct(obj, "clientIpAddress", &p->ClientIPAddress, sizeof(p->ClientIPAddress));
    set_struct(obj, "loginRemark", &p->LoginRemark, sizeof(p->LoginRemark));
    set_struct(obj, "clientIpPort", &p->ClientIPPort, sizeof(p->ClientIPPort));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspUserLoginField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "loginTime", &p->LoginTime, sizeof(p->LoginTime));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "systemName", &p->SystemName, sizeof(p->SystemName));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "maxOrderRef", &p->MaxOrderRef, sizeof(p->MaxOrderRef));
    set_struct(obj, "sHFETime", &p->SHFETime, sizeof(p->SHFETime));
    set_struct(obj, "dceTime", &p->DCETime, sizeof(p->DCETime));
    set_struct(obj, "czceTime", &p->CZCETime, sizeof(p->CZCETime));
    set_struct(obj, "ffexTime", &p->FFEXTime, sizeof(p->FFEXTime));
    set_struct(obj, "ineTime", &p->INETime, sizeof(p->INETime));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserLogoutField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcForceUserLogoutField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqAuthenticateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "authCode", &p->AuthCode, sizeof(p->AuthCode));
    set_struct(obj, "appId", &p->AppID, sizeof(p->AppID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspAuthenticateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "appId", &p->AppID, sizeof(p->AppID));
    set_struct(obj, "appType", &p->AppType, sizeof(p->AppType));
}
static void set_struct(Local<Object>& obj, CThostFtdcAuthenticationInfoField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "authInfo", &p->AuthInfo, sizeof(p->AuthInfo));
    set_struct(obj, "isResult", &p->IsResult, sizeof(p->IsResult));
    set_struct(obj, "appId", &p->AppID, sizeof(p->AppID));
    set_struct(obj, "appType", &p->AppType, sizeof(p->AppType));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferHeaderField *p)
{
    set_struct(obj, "version", &p->Version, sizeof(p->Version));
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "tradeSerial", &p->TradeSerial, sizeof(p->TradeSerial));
    set_struct(obj, "futureId", &p->FutureID, sizeof(p->FutureID));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBrchId", &p->BankBrchID, sizeof(p->BankBrchID));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "recordNum", &p->RecordNum, sizeof(p->RecordNum));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferBankToFutureReqField *p)
{
    set_struct(obj, "futureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "futurePwdFlag", &p->FuturePwdFlag, sizeof(p->FuturePwdFlag));
    set_struct(obj, "futureAccPwd", &p->FutureAccPwd, sizeof(p->FutureAccPwd));
    set_struct(obj, "tradeAmt", &p->TradeAmt, sizeof(p->TradeAmt));
    set_struct(obj, "custFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "currencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferBankToFutureRspField *p)
{
    set_struct(obj, "retCode", &p->RetCode, sizeof(p->RetCode));
    set_struct(obj, "retInfo", &p->RetInfo, sizeof(p->RetInfo));
    set_struct(obj, "futureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "tradeAmt", &p->TradeAmt, sizeof(p->TradeAmt));
    set_struct(obj, "custFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "currencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferFutureToBankReqField *p)
{
    set_struct(obj, "futureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "futurePwdFlag", &p->FuturePwdFlag, sizeof(p->FuturePwdFlag));
    set_struct(obj, "futureAccPwd", &p->FutureAccPwd, sizeof(p->FutureAccPwd));
    set_struct(obj, "tradeAmt", &p->TradeAmt, sizeof(p->TradeAmt));
    set_struct(obj, "custFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "currencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferFutureToBankRspField *p)
{
    set_struct(obj, "retCode", &p->RetCode, sizeof(p->RetCode));
    set_struct(obj, "retInfo", &p->RetInfo, sizeof(p->RetInfo));
    set_struct(obj, "futureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "tradeAmt", &p->TradeAmt, sizeof(p->TradeAmt));
    set_struct(obj, "custFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "currencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferQryBankReqField *p)
{
    set_struct(obj, "futureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "futurePwdFlag", &p->FuturePwdFlag, sizeof(p->FuturePwdFlag));
    set_struct(obj, "futureAccPwd", &p->FutureAccPwd, sizeof(p->FutureAccPwd));
    set_struct(obj, "currencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferQryBankRspField *p)
{
    set_struct(obj, "retCode", &p->RetCode, sizeof(p->RetCode));
    set_struct(obj, "retInfo", &p->RetInfo, sizeof(p->RetInfo));
    set_struct(obj, "futureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "tradeAmt", &p->TradeAmt, sizeof(p->TradeAmt));
    set_struct(obj, "useAmt", &p->UseAmt, sizeof(p->UseAmt));
    set_struct(obj, "fetchAmt", &p->FetchAmt, sizeof(p->FetchAmt));
    set_struct(obj, "currencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferQryDetailReqField *p)
{
    set_struct(obj, "futureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferQryDetailRspField *p)
{
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "futureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "futureId", &p->FutureID, sizeof(p->FutureID));
    set_struct(obj, "futureAccount", &p->FutureAccount, sizeof(p->FutureAccount));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBrchId", &p->BankBrchID, sizeof(p->BankBrchID));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "certCode", &p->CertCode, sizeof(p->CertCode));
    set_struct(obj, "currencyCode", &p->CurrencyCode, sizeof(p->CurrencyCode));
    set_struct(obj, "txAmount", &p->TxAmount, sizeof(p->TxAmount));
    set_struct(obj, "flag", &p->Flag, sizeof(p->Flag));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspInfoField *p)
{
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "exchangeName", &p->ExchangeName, sizeof(p->ExchangeName));
    set_struct(obj, "exchangeProperty", &p->ExchangeProperty, sizeof(p->ExchangeProperty));
}
static void set_struct(Local<Object>& obj, CThostFtdcProductField *p)
{
    set_struct(obj, "productId", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "productName", &p->ProductName, sizeof(p->ProductName));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "productClass", &p->ProductClass, sizeof(p->ProductClass));
    set_struct(obj, "volumeMultiple", &p->VolumeMultiple, sizeof(p->VolumeMultiple));
    set_struct(obj, "priceTick", &p->PriceTick, sizeof(p->PriceTick));
    set_struct(obj, "maxMarketOrderVolume", &p->MaxMarketOrderVolume, sizeof(p->MaxMarketOrderVolume));
    set_struct(obj, "minMarketOrderVolume", &p->MinMarketOrderVolume, sizeof(p->MinMarketOrderVolume));
    set_struct(obj, "maxLimitOrderVolume", &p->MaxLimitOrderVolume, sizeof(p->MaxLimitOrderVolume));
    set_struct(obj, "minLimitOrderVolume", &p->MinLimitOrderVolume, sizeof(p->MinLimitOrderVolume));
    set_struct(obj, "positionType", &p->PositionType, sizeof(p->PositionType));
    set_struct(obj, "positionDateType", &p->PositionDateType, sizeof(p->PositionDateType));
    set_struct(obj, "closeDealType", &p->CloseDealType, sizeof(p->CloseDealType));
    set_struct(obj, "tradeCurrencyId", &p->TradeCurrencyID, sizeof(p->TradeCurrencyID));
    set_struct(obj, "mortgageFundUseRange", &p->MortgageFundUseRange, sizeof(p->MortgageFundUseRange));
    set_struct(obj, "exchangeProductId", &p->ExchangeProductID, sizeof(p->ExchangeProductID));
    set_struct(obj, "underlyingMultiple", &p->UnderlyingMultiple, sizeof(p->UnderlyingMultiple));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "instrumentName", &p->InstrumentName, sizeof(p->InstrumentName));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "productId", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "productClass", &p->ProductClass, sizeof(p->ProductClass));
    set_struct(obj, "deliveryYear", &p->DeliveryYear, sizeof(p->DeliveryYear));
    set_struct(obj, "deliveryMonth", &p->DeliveryMonth, sizeof(p->DeliveryMonth));
    set_struct(obj, "maxMarketOrderVolume", &p->MaxMarketOrderVolume, sizeof(p->MaxMarketOrderVolume));
    set_struct(obj, "minMarketOrderVolume", &p->MinMarketOrderVolume, sizeof(p->MinMarketOrderVolume));
    set_struct(obj, "maxLimitOrderVolume", &p->MaxLimitOrderVolume, sizeof(p->MaxLimitOrderVolume));
    set_struct(obj, "minLimitOrderVolume", &p->MinLimitOrderVolume, sizeof(p->MinLimitOrderVolume));
    set_struct(obj, "volumeMultiple", &p->VolumeMultiple, sizeof(p->VolumeMultiple));
    set_struct(obj, "priceTick", &p->PriceTick, sizeof(p->PriceTick));
    set_struct(obj, "createDate", &p->CreateDate, sizeof(p->CreateDate));
    set_struct(obj, "openDate", &p->OpenDate, sizeof(p->OpenDate));
    set_struct(obj, "expireDate", &p->ExpireDate, sizeof(p->ExpireDate));
    set_struct(obj, "startDelivDate", &p->StartDelivDate, sizeof(p->StartDelivDate));
    set_struct(obj, "endDelivDate", &p->EndDelivDate, sizeof(p->EndDelivDate));
    set_struct(obj, "instLifePhase", &p->InstLifePhase, sizeof(p->InstLifePhase));
    set_struct(obj, "isTrading", &p->IsTrading, sizeof(p->IsTrading));
    set_struct(obj, "positionType", &p->PositionType, sizeof(p->PositionType));
    set_struct(obj, "positionDateType", &p->PositionDateType, sizeof(p->PositionDateType));
    set_struct(obj, "longMarginRatio", &p->LongMarginRatio, sizeof(p->LongMarginRatio));
    set_struct(obj, "shortMarginRatio", &p->ShortMarginRatio, sizeof(p->ShortMarginRatio));
    set_struct(obj, "maxMarginSideAlgorithm", &p->MaxMarginSideAlgorithm, sizeof(p->MaxMarginSideAlgorithm));
    set_struct(obj, "underlyingInstrId", &p->UnderlyingInstrID, sizeof(p->UnderlyingInstrID));
    set_struct(obj, "strikePrice", &p->StrikePrice, sizeof(p->StrikePrice));
    set_struct(obj, "optionsType", &p->OptionsType, sizeof(p->OptionsType));
    set_struct(obj, "underlyingMultiple", &p->UnderlyingMultiple, sizeof(p->UnderlyingMultiple));
    set_struct(obj, "combinationType", &p->CombinationType, sizeof(p->CombinationType));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerAbbr", &p->BrokerAbbr, sizeof(p->BrokerAbbr));
    set_struct(obj, "brokerName", &p->BrokerName, sizeof(p->BrokerName));
    set_struct(obj, "isActive", &p->IsActive, sizeof(p->IsActive));
}
static void set_struct(Local<Object>& obj, CThostFtdcTraderField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installCount", &p->InstallCount, sizeof(p->InstallCount));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorField *p)
{
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorGroupId", &p->InvestorGroupID, sizeof(p->InvestorGroupID));
    set_struct(obj, "investorName", &p->InvestorName, sizeof(p->InvestorName));
    set_struct(obj, "identifiedCardType", &p->IdentifiedCardType, sizeof(p->IdentifiedCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "isActive", &p->IsActive, sizeof(p->IsActive));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "openDate", &p->OpenDate, sizeof(p->OpenDate));
    set_struct(obj, "mobile", &p->Mobile, sizeof(p->Mobile));
    set_struct(obj, "commModelId", &p->CommModelID, sizeof(p->CommModelID));
    set_struct(obj, "marginModelId", &p->MarginModelID, sizeof(p->MarginModelID));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingCodeField *p)
{
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "isActive", &p->IsActive, sizeof(p->IsActive));
    set_struct(obj, "clientIDType", &p->ClientIDType, sizeof(p->ClientIDType));
}
static void set_struct(Local<Object>& obj, CThostFtdcPartBrokerField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "isActive", &p->IsActive, sizeof(p->IsActive));
}
static void set_struct(Local<Object>& obj, CThostFtdcSuperUserField *p)
{
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "userName", &p->UserName, sizeof(p->UserName));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "isActive", &p->IsActive, sizeof(p->IsActive));
}
static void set_struct(Local<Object>& obj, CThostFtdcSuperUserFunctionField *p)
{
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "functionCode", &p->FunctionCode, sizeof(p->FunctionCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorGroupField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorGroupId", &p->InvestorGroupID, sizeof(p->InvestorGroupID));
    set_struct(obj, "investorGroupName", &p->InvestorGroupName, sizeof(p->InvestorGroupName));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingAccountField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "preMortgage", &p->PreMortgage, sizeof(p->PreMortgage));
    set_struct(obj, "preCredit", &p->PreCredit, sizeof(p->PreCredit));
    set_struct(obj, "preDeposit", &p->PreDeposit, sizeof(p->PreDeposit));
    set_struct(obj, "preBalance", &p->PreBalance, sizeof(p->PreBalance));
    set_struct(obj, "preMargin", &p->PreMargin, sizeof(p->PreMargin));
    set_struct(obj, "interestBase", &p->InterestBase, sizeof(p->InterestBase));
    set_struct(obj, "interest", &p->Interest, sizeof(p->Interest));
    set_struct(obj, "deposit", &p->Deposit, sizeof(p->Deposit));
    set_struct(obj, "withdraw", &p->Withdraw, sizeof(p->Withdraw));
    set_struct(obj, "frozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
    set_struct(obj, "frozenCash", &p->FrozenCash, sizeof(p->FrozenCash));
    set_struct(obj, "frozenCommission", &p->FrozenCommission, sizeof(p->FrozenCommission));
    set_struct(obj, "currMargin", &p->CurrMargin, sizeof(p->CurrMargin));
    set_struct(obj, "cashIn", &p->CashIn, sizeof(p->CashIn));
    set_struct(obj, "commission", &p->Commission, sizeof(p->Commission));
    set_struct(obj, "closeProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "positionProfit", &p->PositionProfit, sizeof(p->PositionProfit));
    set_struct(obj, "balance", &p->Balance, sizeof(p->Balance));
    set_struct(obj, "available", &p->Available, sizeof(p->Available));
    set_struct(obj, "withdrawQuota", &p->WithdrawQuota, sizeof(p->WithdrawQuota));
    set_struct(obj, "reserve", &p->Reserve, sizeof(p->Reserve));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "credit", &p->Credit, sizeof(p->Credit));
    set_struct(obj, "mortgage", &p->Mortgage, sizeof(p->Mortgage));
    set_struct(obj, "exchangeMargin", &p->ExchangeMargin, sizeof(p->ExchangeMargin));
    set_struct(obj, "deliveryMargin", &p->DeliveryMargin, sizeof(p->DeliveryMargin));
    set_struct(obj, "exchangeDeliveryMargin", &p->ExchangeDeliveryMargin, sizeof(p->ExchangeDeliveryMargin));
    set_struct(obj, "reserveBalance", &p->ReserveBalance, sizeof(p->ReserveBalance));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "preFundMortgageIn", &p->PreFundMortgageIn, sizeof(p->PreFundMortgageIn));
    set_struct(obj, "preFundMortgageOut", &p->PreFundMortgageOut, sizeof(p->PreFundMortgageOut));
    set_struct(obj, "fundMortgageIn", &p->FundMortgageIn, sizeof(p->FundMortgageIn));
    set_struct(obj, "fundMortgageOut", &p->FundMortgageOut, sizeof(p->FundMortgageOut));
    set_struct(obj, "fundMortgageAvailable", &p->FundMortgageAvailable, sizeof(p->FundMortgageAvailable));
    set_struct(obj, "mortgageableFund", &p->MortgageableFund, sizeof(p->MortgageableFund));
    set_struct(obj, "specProductMargin", &p->SpecProductMargin, sizeof(p->SpecProductMargin));
    set_struct(obj, "specProductFrozenMargin", &p->SpecProductFrozenMargin, sizeof(p->SpecProductFrozenMargin));
    set_struct(obj, "specProductCommission", &p->SpecProductCommission, sizeof(p->SpecProductCommission));
    set_struct(obj, "specProductFrozenCommission", &p->SpecProductFrozenCommission, sizeof(p->SpecProductFrozenCommission));
    set_struct(obj, "specProductPositionProfit", &p->SpecProductPositionProfit, sizeof(p->SpecProductPositionProfit));
    set_struct(obj, "specProductCloseProfit", &p->SpecProductCloseProfit, sizeof(p->SpecProductCloseProfit));
    set_struct(obj, "specProductPositionProfitByAlg", &p->SpecProductPositionProfitByAlg, sizeof(p->SpecProductPositionProfitByAlg));
    set_struct(obj, "specProductExchangeMargin", &p->SpecProductExchangeMargin, sizeof(p->SpecProductExchangeMargin));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorPositionField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "posiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "positionDate", &p->PositionDate, sizeof(p->PositionDate));
    set_struct(obj, "ydPosition", &p->YdPosition, sizeof(p->YdPosition));
    set_struct(obj, "position", &p->Position, sizeof(p->Position));
    set_struct(obj, "longFrozen", &p->LongFrozen, sizeof(p->LongFrozen));
    set_struct(obj, "shortFrozen", &p->ShortFrozen, sizeof(p->ShortFrozen));
    set_struct(obj, "longFrozenAmount", &p->LongFrozenAmount, sizeof(p->LongFrozenAmount));
    set_struct(obj, "shortFrozenAmount", &p->ShortFrozenAmount, sizeof(p->ShortFrozenAmount));
    set_struct(obj, "openVolume", &p->OpenVolume, sizeof(p->OpenVolume));
    set_struct(obj, "closeVolume", &p->CloseVolume, sizeof(p->CloseVolume));
    set_struct(obj, "openAmount", &p->OpenAmount, sizeof(p->OpenAmount));
    set_struct(obj, "closeAmount", &p->CloseAmount, sizeof(p->CloseAmount));
    set_struct(obj, "positionCost", &p->PositionCost, sizeof(p->PositionCost));
    set_struct(obj, "preMargin", &p->PreMargin, sizeof(p->PreMargin));
    set_struct(obj, "useMargin", &p->UseMargin, sizeof(p->UseMargin));
    set_struct(obj, "frozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
    set_struct(obj, "frozenCash", &p->FrozenCash, sizeof(p->FrozenCash));
    set_struct(obj, "frozenCommission", &p->FrozenCommission, sizeof(p->FrozenCommission));
    set_struct(obj, "cashIn", &p->CashIn, sizeof(p->CashIn));
    set_struct(obj, "commission", &p->Commission, sizeof(p->Commission));
    set_struct(obj, "closeProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "positionProfit", &p->PositionProfit, sizeof(p->PositionProfit));
    set_struct(obj, "preSettlementPrice", &p->PreSettlementPrice, sizeof(p->PreSettlementPrice));
    set_struct(obj, "settlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "openCost", &p->OpenCost, sizeof(p->OpenCost));
    set_struct(obj, "exchangeMargin", &p->ExchangeMargin, sizeof(p->ExchangeMargin));
    set_struct(obj, "combPosition", &p->CombPosition, sizeof(p->CombPosition));
    set_struct(obj, "combLongFrozen", &p->CombLongFrozen, sizeof(p->CombLongFrozen));
    set_struct(obj, "combShortFrozen", &p->CombShortFrozen, sizeof(p->CombShortFrozen));
    set_struct(obj, "closeProfitByDate", &p->CloseProfitByDate, sizeof(p->CloseProfitByDate));
    set_struct(obj, "closeProfitByTrade", &p->CloseProfitByTrade, sizeof(p->CloseProfitByTrade));
    set_struct(obj, "todayPosition", &p->TodayPosition, sizeof(p->TodayPosition));
    set_struct(obj, "marginRateByMoney", &p->MarginRateByMoney, sizeof(p->MarginRateByMoney));
    set_struct(obj, "marginRateByVolume", &p->MarginRateByVolume, sizeof(p->MarginRateByVolume));
    set_struct(obj, "strikeFrozen", &p->StrikeFrozen, sizeof(p->StrikeFrozen));
    set_struct(obj, "strikeFrozenAmount", &p->StrikeFrozenAmount, sizeof(p->StrikeFrozenAmount));
    set_struct(obj, "abandonFrozen", &p->AbandonFrozen, sizeof(p->AbandonFrozen));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentMarginRateField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "longMarginRatioByMoney", &p->LongMarginRatioByMoney, sizeof(p->LongMarginRatioByMoney));
    set_struct(obj, "longMarginRatioByVolume", &p->LongMarginRatioByVolume, sizeof(p->LongMarginRatioByVolume));
    set_struct(obj, "shortMarginRatioByMoney", &p->ShortMarginRatioByMoney, sizeof(p->ShortMarginRatioByMoney));
    set_struct(obj, "shortMarginRatioByVolume", &p->ShortMarginRatioByVolume, sizeof(p->ShortMarginRatioByVolume));
    set_struct(obj, "isRelative", &p->IsRelative, sizeof(p->IsRelative));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentCommissionRateField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "openRatioByMoney", &p->OpenRatioByMoney, sizeof(p->OpenRatioByMoney));
    set_struct(obj, "openRatioByVolume", &p->OpenRatioByVolume, sizeof(p->OpenRatioByVolume));
    set_struct(obj, "closeRatioByMoney", &p->CloseRatioByMoney, sizeof(p->CloseRatioByMoney));
    set_struct(obj, "closeRatioByVolume", &p->CloseRatioByVolume, sizeof(p->CloseRatioByVolume));
    set_struct(obj, "closeTodayRatioByMoney", &p->CloseTodayRatioByMoney, sizeof(p->CloseTodayRatioByMoney));
    set_struct(obj, "closeTodayRatioByVolume", &p->CloseTodayRatioByVolume, sizeof(p->CloseTodayRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcDepthMarketDataField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "lastPrice", &p->LastPrice, sizeof(p->LastPrice));
    set_struct(obj, "preSettlementPrice", &p->PreSettlementPrice, sizeof(p->PreSettlementPrice));
    set_struct(obj, "preClosePrice", &p->PreClosePrice, sizeof(p->PreClosePrice));
    set_struct(obj, "preOpenInterest", &p->PreOpenInterest, sizeof(p->PreOpenInterest));
    set_struct(obj, "openPrice", &p->OpenPrice, sizeof(p->OpenPrice));
    set_struct(obj, "highestPrice", &p->HighestPrice, sizeof(p->HighestPrice));
    set_struct(obj, "lowestPrice", &p->LowestPrice, sizeof(p->LowestPrice));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "turnover", &p->Turnover, sizeof(p->Turnover));
    set_struct(obj, "openInterest", &p->OpenInterest, sizeof(p->OpenInterest));
    set_struct(obj, "closePrice", &p->ClosePrice, sizeof(p->ClosePrice));
    set_struct(obj, "settlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "upperLimitPrice", &p->UpperLimitPrice, sizeof(p->UpperLimitPrice));
    set_struct(obj, "lowerLimitPrice", &p->LowerLimitPrice, sizeof(p->LowerLimitPrice));
    set_struct(obj, "preDelta", &p->PreDelta, sizeof(p->PreDelta));
    set_struct(obj, "currDelta", &p->CurrDelta, sizeof(p->CurrDelta));
    set_struct(obj, "updateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "updateMillisec", &p->UpdateMillisec, sizeof(p->UpdateMillisec));
    set_struct(obj, "bidPrice1", &p->BidPrice1, sizeof(p->BidPrice1));
    set_struct(obj, "bidVolume1", &p->BidVolume1, sizeof(p->BidVolume1));
    set_struct(obj, "askPrice1", &p->AskPrice1, sizeof(p->AskPrice1));
    set_struct(obj, "askVolume1", &p->AskVolume1, sizeof(p->AskVolume1));
    set_struct(obj, "bidPrice2", &p->BidPrice2, sizeof(p->BidPrice2));
    set_struct(obj, "bidVolume2", &p->BidVolume2, sizeof(p->BidVolume2));
    set_struct(obj, "askPrice2", &p->AskPrice2, sizeof(p->AskPrice2));
    set_struct(obj, "askVolume2", &p->AskVolume2, sizeof(p->AskVolume2));
    set_struct(obj, "bidPrice3", &p->BidPrice3, sizeof(p->BidPrice3));
    set_struct(obj, "bidVolume3", &p->BidVolume3, sizeof(p->BidVolume3));
    set_struct(obj, "askPrice3", &p->AskPrice3, sizeof(p->AskPrice3));
    set_struct(obj, "askVolume3", &p->AskVolume3, sizeof(p->AskVolume3));
    set_struct(obj, "bidPrice4", &p->BidPrice4, sizeof(p->BidPrice4));
    set_struct(obj, "bidVolume4", &p->BidVolume4, sizeof(p->BidVolume4));
    set_struct(obj, "askPrice4", &p->AskPrice4, sizeof(p->AskPrice4));
    set_struct(obj, "askVolume4", &p->AskVolume4, sizeof(p->AskVolume4));
    set_struct(obj, "bidPrice5", &p->BidPrice5, sizeof(p->BidPrice5));
    set_struct(obj, "bidVolume5", &p->BidVolume5, sizeof(p->BidVolume5));
    set_struct(obj, "askPrice5", &p->AskPrice5, sizeof(p->AskPrice5));
    set_struct(obj, "askVolume5", &p->AskVolume5, sizeof(p->AskVolume5));
    set_struct(obj, "averagePrice", &p->AveragePrice, sizeof(p->AveragePrice));
    set_struct(obj, "actionDay", &p->ActionDay, sizeof(p->ActionDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentTradingRightField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "tradingRight", &p->TradingRight, sizeof(p->TradingRight));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "userName", &p->UserName, sizeof(p->UserName));
    set_struct(obj, "userType", &p->UserType, sizeof(p->UserType));
    set_struct(obj, "isActive", &p->IsActive, sizeof(p->IsActive));
    set_struct(obj, "isUsingOtp", &p->IsUsingOTP, sizeof(p->IsUsingOTP));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserPasswordField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserFunctionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "brokerFunctionCode", &p->BrokerFunctionCode, sizeof(p->BrokerFunctionCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcTraderOfferField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "traderConnectStatus", &p->TraderConnectStatus, sizeof(p->TraderConnectStatus));
    set_struct(obj, "connectRequestDate", &p->ConnectRequestDate, sizeof(p->ConnectRequestDate));
    set_struct(obj, "connectRequestTime", &p->ConnectRequestTime, sizeof(p->ConnectRequestTime));
    set_struct(obj, "lastReportDate", &p->LastReportDate, sizeof(p->LastReportDate));
    set_struct(obj, "lastReportTime", &p->LastReportTime, sizeof(p->LastReportTime));
    set_struct(obj, "connectDate", &p->ConnectDate, sizeof(p->ConnectDate));
    set_struct(obj, "connectTime", &p->ConnectTime, sizeof(p->ConnectTime));
    set_struct(obj, "startDate", &p->StartDate, sizeof(p->StartDate));
    set_struct(obj, "startTime", &p->StartTime, sizeof(p->StartTime));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "maxTradeId", &p->MaxTradeID, sizeof(p->MaxTradeID));
    set_struct(obj, "maxOrderMessageReference", &p->MaxOrderMessageReference, sizeof(p->MaxOrderMessageReference));
}
static void set_struct(Local<Object>& obj, CThostFtdcSettlementInfoField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "content", &p->Content, sizeof(p->Content));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentMarginRateAdjustField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "longMarginRatioByMoney", &p->LongMarginRatioByMoney, sizeof(p->LongMarginRatioByMoney));
    set_struct(obj, "longMarginRatioByVolume", &p->LongMarginRatioByVolume, sizeof(p->LongMarginRatioByVolume));
    set_struct(obj, "shortMarginRatioByMoney", &p->ShortMarginRatioByMoney, sizeof(p->ShortMarginRatioByMoney));
    set_struct(obj, "shortMarginRatioByVolume", &p->ShortMarginRatioByVolume, sizeof(p->ShortMarginRatioByVolume));
    set_struct(obj, "isRelative", &p->IsRelative, sizeof(p->IsRelative));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeMarginRateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "longMarginRatioByMoney", &p->LongMarginRatioByMoney, sizeof(p->LongMarginRatioByMoney));
    set_struct(obj, "longMarginRatioByVolume", &p->LongMarginRatioByVolume, sizeof(p->LongMarginRatioByVolume));
    set_struct(obj, "shortMarginRatioByMoney", &p->ShortMarginRatioByMoney, sizeof(p->ShortMarginRatioByMoney));
    set_struct(obj, "shortMarginRatioByVolume", &p->ShortMarginRatioByVolume, sizeof(p->ShortMarginRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeMarginRateAdjustField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "longMarginRatioByMoney", &p->LongMarginRatioByMoney, sizeof(p->LongMarginRatioByMoney));
    set_struct(obj, "longMarginRatioByVolume", &p->LongMarginRatioByVolume, sizeof(p->LongMarginRatioByVolume));
    set_struct(obj, "shortMarginRatioByMoney", &p->ShortMarginRatioByMoney, sizeof(p->ShortMarginRatioByMoney));
    set_struct(obj, "shortMarginRatioByVolume", &p->ShortMarginRatioByVolume, sizeof(p->ShortMarginRatioByVolume));
    set_struct(obj, "exchLongMarginRatioByMoney", &p->ExchLongMarginRatioByMoney, sizeof(p->ExchLongMarginRatioByMoney));
    set_struct(obj, "exchLongMarginRatioByVolume", &p->ExchLongMarginRatioByVolume, sizeof(p->ExchLongMarginRatioByVolume));
    set_struct(obj, "exchShortMarginRatioByMoney", &p->ExchShortMarginRatioByMoney, sizeof(p->ExchShortMarginRatioByMoney));
    set_struct(obj, "exchShortMarginRatioByVolume", &p->ExchShortMarginRatioByVolume, sizeof(p->ExchShortMarginRatioByVolume));
    set_struct(obj, "noLongMarginRatioByMoney", &p->NoLongMarginRatioByMoney, sizeof(p->NoLongMarginRatioByMoney));
    set_struct(obj, "noLongMarginRatioByVolume", &p->NoLongMarginRatioByVolume, sizeof(p->NoLongMarginRatioByVolume));
    set_struct(obj, "noShortMarginRatioByMoney", &p->NoShortMarginRatioByMoney, sizeof(p->NoShortMarginRatioByMoney));
    set_struct(obj, "noShortMarginRatioByVolume", &p->NoShortMarginRatioByVolume, sizeof(p->NoShortMarginRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeRateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "fromCurrencyId", &p->FromCurrencyID, sizeof(p->FromCurrencyID));
    set_struct(obj, "fromCurrencyUnit", &p->FromCurrencyUnit, sizeof(p->FromCurrencyUnit));
    set_struct(obj, "toCurrencyId", &p->ToCurrencyID, sizeof(p->ToCurrencyID));
    set_struct(obj, "exchangeRate", &p->ExchangeRate, sizeof(p->ExchangeRate));
}
static void set_struct(Local<Object>& obj, CThostFtdcSettlementRefField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
}
static void set_struct(Local<Object>& obj, CThostFtdcCurrentTimeField *p)
{
    set_struct(obj, "currDate", &p->CurrDate, sizeof(p->CurrDate));
    set_struct(obj, "currTime", &p->CurrTime, sizeof(p->CurrTime));
    set_struct(obj, "currMillisec", &p->CurrMillisec, sizeof(p->CurrMillisec));
    set_struct(obj, "actionDay", &p->ActionDay, sizeof(p->ActionDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcCommPhaseField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "commPhaseNo", &p->CommPhaseNo, sizeof(p->CommPhaseNo));
    set_struct(obj, "systemId", &p->SystemID, sizeof(p->SystemID));
}
static void set_struct(Local<Object>& obj, CThostFtdcLoginInfoField *p)
{
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "loginDate", &p->LoginDate, sizeof(p->LoginDate));
    set_struct(obj, "loginTime", &p->LoginTime, sizeof(p->LoginTime));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "interfaceProductInfo", &p->InterfaceProductInfo, sizeof(p->InterfaceProductInfo));
    set_struct(obj, "protocolInfo", &p->ProtocolInfo, sizeof(p->ProtocolInfo));
    set_struct(obj, "systemName", &p->SystemName, sizeof(p->SystemName));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "maxOrderRef", &p->MaxOrderRef, sizeof(p->MaxOrderRef));
    set_struct(obj, "sHFETime", &p->SHFETime, sizeof(p->SHFETime));
    set_struct(obj, "dCETime", &p->DCETime, sizeof(p->DCETime));
    set_struct(obj, "cZCETime", &p->CZCETime, sizeof(p->CZCETime));
    set_struct(obj, "fFEXTime", &p->FFEXTime, sizeof(p->FFEXTime));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "oneTimePassword", &p->OneTimePassword, sizeof(p->OneTimePassword));
    set_struct(obj, "iNETime", &p->INETime, sizeof(p->INETime));
    set_struct(obj, "isQryControl", &p->IsQryControl, sizeof(p->IsQryControl));
    set_struct(obj, "loginRemark", &p->LoginRemark, sizeof(p->LoginRemark));
}
static void set_struct(Local<Object>& obj, CThostFtdcLogoutAllField *p)
{
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "systemName", &p->SystemName, sizeof(p->SystemName));
}
static void set_struct(Local<Object>& obj, CThostFtdcFrontStatusField *p)
{
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "lastReportDate", &p->LastReportDate, sizeof(p->LastReportDate));
    set_struct(obj, "lastReportTime", &p->LastReportTime, sizeof(p->LastReportTime));
    set_struct(obj, "isActive", &p->IsActive, sizeof(p->IsActive));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserPasswordUpdateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "oldPassword", &p->OldPassword, sizeof(p->OldPassword));
    set_struct(obj, "newPassword", &p->NewPassword, sizeof(p->NewPassword));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "orderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "orderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "combOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "combHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "timeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "gtdDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "volumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "minVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "contingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "stopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "forceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "isAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "userForceClose", &p->UserForceClose, sizeof(p->UserForceClose));
    set_struct(obj, "isSwapOrder", &p->IsSwapOrder, sizeof(p->IsSwapOrder));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "orderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "orderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "combOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "combHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "timeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "gtdDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "volumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "minVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "contingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "stopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "forceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "isAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "notifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "orderSource", &p->OrderSource, sizeof(p->OrderSource));
    set_struct(obj, "orderStatus", &p->OrderStatus, sizeof(p->OrderStatus));
    set_struct(obj, "orderType", &p->OrderType, sizeof(p->OrderType));
    set_struct(obj, "volumeTraded", &p->VolumeTraded, sizeof(p->VolumeTraded));
    set_struct(obj, "volumeTotal", &p->VolumeTotal, sizeof(p->VolumeTotal));
    set_struct(obj, "insertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "insertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "activeTime", &p->ActiveTime, sizeof(p->ActiveTime));
    set_struct(obj, "suspendTime", &p->SuspendTime, sizeof(p->SuspendTime));
    set_struct(obj, "updateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "cancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "activeTraderId", &p->ActiveTraderID, sizeof(p->ActiveTraderID));
    set_struct(obj, "clearingPartId", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "userForceClose", &p->UserForceClose, sizeof(p->UserForceClose));
    set_struct(obj, "activeUserId", &p->ActiveUserID, sizeof(p->ActiveUserID));
    set_struct(obj, "brokerOrderSeq", &p->BrokerOrderSeq, sizeof(p->BrokerOrderSeq));
    set_struct(obj, "relativeOrderSysId", &p->RelativeOrderSysID, sizeof(p->RelativeOrderSysID));
    set_struct(obj, "zceTotalTradedVolume", &p->ZCETotalTradedVolume, sizeof(p->ZCETotalTradedVolume));
    set_struct(obj, "isSwapOrder", &p->IsSwapOrder, sizeof(p->IsSwapOrder));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeOrderField *p)
{
    set_struct(obj, "orderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "combOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "combHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "timeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "gtdDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "volumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "minVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "contingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "stopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "forceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "isAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "notifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "orderSource", &p->OrderSource, sizeof(p->OrderSource));
    set_struct(obj, "orderStatus", &p->OrderStatus, sizeof(p->OrderStatus));
    set_struct(obj, "orderType", &p->OrderType, sizeof(p->OrderType));
    set_struct(obj, "volumeTraded", &p->VolumeTraded, sizeof(p->VolumeTraded));
    set_struct(obj, "volumeTotal", &p->VolumeTotal, sizeof(p->VolumeTotal));
    set_struct(obj, "insertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "insertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "activeTime", &p->ActiveTime, sizeof(p->ActiveTime));
    set_struct(obj, "suspendTime", &p->SuspendTime, sizeof(p->SuspendTime));
    set_struct(obj, "updateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "cancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "activeTraderId", &p->ActiveTraderID, sizeof(p->ActiveTraderID));
    set_struct(obj, "clearingPartId", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeOrderInsertErrorField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "orderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "orderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeChange", &p->VolumeChange, sizeof(p->VolumeChange));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "orderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "orderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeChange", &p->VolumeChange, sizeof(p->VolumeChange));
    set_struct(obj, "actionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "actionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "orderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeOrderActionField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeChange", &p->VolumeChange, sizeof(p->VolumeChange));
    set_struct(obj, "actionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "actionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "orderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeOrderActionErrorField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeTradeField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "tradeId", &p->TradeID, sizeof(p->TradeID));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "tradingRole", &p->TradingRole, sizeof(p->TradingRole));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "offsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "price", &p->Price, sizeof(p->Price));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "tradeType", &p->TradeType, sizeof(p->TradeType));
    set_struct(obj, "priceSource", &p->PriceSource, sizeof(p->PriceSource));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "clearingPartId", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "tradeSource", &p->TradeSource, sizeof(p->TradeSource));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradeField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "orderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "tradeId", &p->TradeID, sizeof(p->TradeID));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "tradingRole", &p->TradingRole, sizeof(p->TradingRole));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "offsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "price", &p->Price, sizeof(p->Price));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "tradeType", &p->TradeType, sizeof(p->TradeType));
    set_struct(obj, "priceSource", &p->PriceSource, sizeof(p->PriceSource));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "clearingPartId", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "brokerOrderSeq", &p->BrokerOrderSeq, sizeof(p->BrokerOrderSeq));
    set_struct(obj, "tradeSource", &p->TradeSource, sizeof(p->TradeSource));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserSessionField *p)
{
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "loginDate", &p->LoginDate, sizeof(p->LoginDate));
    set_struct(obj, "loginTime", &p->LoginTime, sizeof(p->LoginTime));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "interfaceProductInfo", &p->InterfaceProductInfo, sizeof(p->InterfaceProductInfo));
    set_struct(obj, "protocolInfo", &p->ProtocolInfo, sizeof(p->ProtocolInfo));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "loginRemark", &p->LoginRemark, sizeof(p->LoginRemark));
}
static void set_struct(Local<Object>& obj, CThostFtdcQueryMaxOrderVolumeField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "offsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "maxVolume", &p->MaxVolume, sizeof(p->MaxVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcSettlementInfoConfirmField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "confirmDate", &p->ConfirmDate, sizeof(p->ConfirmDate));
    set_struct(obj, "confirmTime", &p->ConfirmTime, sizeof(p->ConfirmTime));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncDepositField *p)
{
    set_struct(obj, "depositSeqNo", &p->DepositSeqNo, sizeof(p->DepositSeqNo));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "deposit", &p->Deposit, sizeof(p->Deposit));
    set_struct(obj, "isForce", &p->IsForce, sizeof(p->IsForce));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncFundMortgageField *p)
{
    set_struct(obj, "mortgageSeqNo", &p->MortgageSeqNo, sizeof(p->MortgageSeqNo));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "fromCurrencyId", &p->FromCurrencyID, sizeof(p->FromCurrencyID));
    set_struct(obj, "mortgageAmount", &p->MortgageAmount, sizeof(p->MortgageAmount));
    set_struct(obj, "toCurrencyId", &p->ToCurrencyID, sizeof(p->ToCurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerSyncField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInvestorField *p)
{
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorGroupId", &p->InvestorGroupID, sizeof(p->InvestorGroupID));
    set_struct(obj, "investorName", &p->InvestorName, sizeof(p->InvestorName));
    set_struct(obj, "identifiedCardType", &p->IdentifiedCardType, sizeof(p->IdentifiedCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "isActive", &p->IsActive, sizeof(p->IsActive));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "openDate", &p->OpenDate, sizeof(p->OpenDate));
    set_struct(obj, "mobile", &p->Mobile, sizeof(p->Mobile));
    set_struct(obj, "commModelId", &p->CommModelID, sizeof(p->CommModelID));
    set_struct(obj, "marginModelId", &p->MarginModelID, sizeof(p->MarginModelID));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingTradingCodeField *p)
{
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "isActive", &p->IsActive, sizeof(p->IsActive));
    set_struct(obj, "clientIDType", &p->ClientIDType, sizeof(p->ClientIDType));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInvestorGroupField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorGroupId", &p->InvestorGroupID, sizeof(p->InvestorGroupID));
    set_struct(obj, "investorGroupName", &p->InvestorGroupName, sizeof(p->InvestorGroupName));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingTradingAccountField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "preMortgage", &p->PreMortgage, sizeof(p->PreMortgage));
    set_struct(obj, "preCredit", &p->PreCredit, sizeof(p->PreCredit));
    set_struct(obj, "preDeposit", &p->PreDeposit, sizeof(p->PreDeposit));
    set_struct(obj, "preBalance", &p->PreBalance, sizeof(p->PreBalance));
    set_struct(obj, "preMargin", &p->PreMargin, sizeof(p->PreMargin));
    set_struct(obj, "interestBase", &p->InterestBase, sizeof(p->InterestBase));
    set_struct(obj, "interest", &p->Interest, sizeof(p->Interest));
    set_struct(obj, "deposit", &p->Deposit, sizeof(p->Deposit));
    set_struct(obj, "withdraw", &p->Withdraw, sizeof(p->Withdraw));
    set_struct(obj, "frozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
    set_struct(obj, "frozenCash", &p->FrozenCash, sizeof(p->FrozenCash));
    set_struct(obj, "frozenCommission", &p->FrozenCommission, sizeof(p->FrozenCommission));
    set_struct(obj, "currMargin", &p->CurrMargin, sizeof(p->CurrMargin));
    set_struct(obj, "cashIn", &p->CashIn, sizeof(p->CashIn));
    set_struct(obj, "commission", &p->Commission, sizeof(p->Commission));
    set_struct(obj, "closeProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "positionProfit", &p->PositionProfit, sizeof(p->PositionProfit));
    set_struct(obj, "balance", &p->Balance, sizeof(p->Balance));
    set_struct(obj, "available", &p->Available, sizeof(p->Available));
    set_struct(obj, "withdrawQuota", &p->WithdrawQuota, sizeof(p->WithdrawQuota));
    set_struct(obj, "reserve", &p->Reserve, sizeof(p->Reserve));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "credit", &p->Credit, sizeof(p->Credit));
    set_struct(obj, "mortgage", &p->Mortgage, sizeof(p->Mortgage));
    set_struct(obj, "exchangeMargin", &p->ExchangeMargin, sizeof(p->ExchangeMargin));
    set_struct(obj, "deliveryMargin", &p->DeliveryMargin, sizeof(p->DeliveryMargin));
    set_struct(obj, "exchangeDeliveryMargin", &p->ExchangeDeliveryMargin, sizeof(p->ExchangeDeliveryMargin));
    set_struct(obj, "reserveBalance", &p->ReserveBalance, sizeof(p->ReserveBalance));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "preFundMortgageIn", &p->PreFundMortgageIn, sizeof(p->PreFundMortgageIn));
    set_struct(obj, "preFundMortgageOut", &p->PreFundMortgageOut, sizeof(p->PreFundMortgageOut));
    set_struct(obj, "fundMortgageIn", &p->FundMortgageIn, sizeof(p->FundMortgageIn));
    set_struct(obj, "fundMortgageOut", &p->FundMortgageOut, sizeof(p->FundMortgageOut));
    set_struct(obj, "fundMortgageAvailable", &p->FundMortgageAvailable, sizeof(p->FundMortgageAvailable));
    set_struct(obj, "mortgageableFund", &p->MortgageableFund, sizeof(p->MortgageableFund));
    set_struct(obj, "specProductMargin", &p->SpecProductMargin, sizeof(p->SpecProductMargin));
    set_struct(obj, "specProductFrozenMargin", &p->SpecProductFrozenMargin, sizeof(p->SpecProductFrozenMargin));
    set_struct(obj, "specProductCommission", &p->SpecProductCommission, sizeof(p->SpecProductCommission));
    set_struct(obj, "specProductFrozenCommission", &p->SpecProductFrozenCommission, sizeof(p->SpecProductFrozenCommission));
    set_struct(obj, "specProductPositionProfit", &p->SpecProductPositionProfit, sizeof(p->SpecProductPositionProfit));
    set_struct(obj, "specProductCloseProfit", &p->SpecProductCloseProfit, sizeof(p->SpecProductCloseProfit));
    set_struct(obj, "specProductPositionProfitByAlg", &p->SpecProductPositionProfitByAlg, sizeof(p->SpecProductPositionProfitByAlg));
    set_struct(obj, "specProductExchangeMargin", &p->SpecProductExchangeMargin, sizeof(p->SpecProductExchangeMargin));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInvestorPositionField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "posiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "positionDate", &p->PositionDate, sizeof(p->PositionDate));
    set_struct(obj, "ydPosition", &p->YdPosition, sizeof(p->YdPosition));
    set_struct(obj, "position", &p->Position, sizeof(p->Position));
    set_struct(obj, "longFrozen", &p->LongFrozen, sizeof(p->LongFrozen));
    set_struct(obj, "shortFrozen", &p->ShortFrozen, sizeof(p->ShortFrozen));
    set_struct(obj, "longFrozenAmount", &p->LongFrozenAmount, sizeof(p->LongFrozenAmount));
    set_struct(obj, "shortFrozenAmount", &p->ShortFrozenAmount, sizeof(p->ShortFrozenAmount));
    set_struct(obj, "openVolume", &p->OpenVolume, sizeof(p->OpenVolume));
    set_struct(obj, "closeVolume", &p->CloseVolume, sizeof(p->CloseVolume));
    set_struct(obj, "openAmount", &p->OpenAmount, sizeof(p->OpenAmount));
    set_struct(obj, "closeAmount", &p->CloseAmount, sizeof(p->CloseAmount));
    set_struct(obj, "positionCost", &p->PositionCost, sizeof(p->PositionCost));
    set_struct(obj, "preMargin", &p->PreMargin, sizeof(p->PreMargin));
    set_struct(obj, "useMargin", &p->UseMargin, sizeof(p->UseMargin));
    set_struct(obj, "frozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
    set_struct(obj, "frozenCash", &p->FrozenCash, sizeof(p->FrozenCash));
    set_struct(obj, "frozenCommission", &p->FrozenCommission, sizeof(p->FrozenCommission));
    set_struct(obj, "cashIn", &p->CashIn, sizeof(p->CashIn));
    set_struct(obj, "commission", &p->Commission, sizeof(p->Commission));
    set_struct(obj, "closeProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "positionProfit", &p->PositionProfit, sizeof(p->PositionProfit));
    set_struct(obj, "preSettlementPrice", &p->PreSettlementPrice, sizeof(p->PreSettlementPrice));
    set_struct(obj, "settlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "openCost", &p->OpenCost, sizeof(p->OpenCost));
    set_struct(obj, "exchangeMargin", &p->ExchangeMargin, sizeof(p->ExchangeMargin));
    set_struct(obj, "combPosition", &p->CombPosition, sizeof(p->CombPosition));
    set_struct(obj, "combLongFrozen", &p->CombLongFrozen, sizeof(p->CombLongFrozen));
    set_struct(obj, "combShortFrozen", &p->CombShortFrozen, sizeof(p->CombShortFrozen));
    set_struct(obj, "closeProfitByDate", &p->CloseProfitByDate, sizeof(p->CloseProfitByDate));
    set_struct(obj, "closeProfitByTrade", &p->CloseProfitByTrade, sizeof(p->CloseProfitByTrade));
    set_struct(obj, "todayPosition", &p->TodayPosition, sizeof(p->TodayPosition));
    set_struct(obj, "marginRateByMoney", &p->MarginRateByMoney, sizeof(p->MarginRateByMoney));
    set_struct(obj, "marginRateByVolume", &p->MarginRateByVolume, sizeof(p->MarginRateByVolume));
    set_struct(obj, "strikeFrozen", &p->StrikeFrozen, sizeof(p->StrikeFrozen));
    set_struct(obj, "strikeFrozenAmount", &p->StrikeFrozenAmount, sizeof(p->StrikeFrozenAmount));
    set_struct(obj, "abandonFrozen", &p->AbandonFrozen, sizeof(p->AbandonFrozen));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInstrumentMarginRateField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "longMarginRatioByMoney", &p->LongMarginRatioByMoney, sizeof(p->LongMarginRatioByMoney));
    set_struct(obj, "longMarginRatioByVolume", &p->LongMarginRatioByVolume, sizeof(p->LongMarginRatioByVolume));
    set_struct(obj, "shortMarginRatioByMoney", &p->ShortMarginRatioByMoney, sizeof(p->ShortMarginRatioByMoney));
    set_struct(obj, "shortMarginRatioByVolume", &p->ShortMarginRatioByVolume, sizeof(p->ShortMarginRatioByVolume));
    set_struct(obj, "isRelative", &p->IsRelative, sizeof(p->IsRelative));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInstrumentCommissionRateField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "openRatioByMoney", &p->OpenRatioByMoney, sizeof(p->OpenRatioByMoney));
    set_struct(obj, "openRatioByVolume", &p->OpenRatioByVolume, sizeof(p->OpenRatioByVolume));
    set_struct(obj, "closeRatioByMoney", &p->CloseRatioByMoney, sizeof(p->CloseRatioByMoney));
    set_struct(obj, "closeRatioByVolume", &p->CloseRatioByVolume, sizeof(p->CloseRatioByVolume));
    set_struct(obj, "closeTodayRatioByMoney", &p->CloseTodayRatioByMoney, sizeof(p->CloseTodayRatioByMoney));
    set_struct(obj, "closeTodayRatioByVolume", &p->CloseTodayRatioByVolume, sizeof(p->CloseTodayRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncingInstrumentTradingRightField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "tradingRight", &p->TradingRight, sizeof(p->TradingRight));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "insertTimeStart", &p->InsertTimeStart, sizeof(p->InsertTimeStart));
    set_struct(obj, "insertTimeEnd", &p->InsertTimeEnd, sizeof(p->InsertTimeEnd));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTradeField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "tradeId", &p->TradeID, sizeof(p->TradeID));
    set_struct(obj, "tradeTimeStart", &p->TradeTimeStart, sizeof(p->TradeTimeStart));
    set_struct(obj, "tradeTimeEnd", &p->TradeTimeEnd, sizeof(p->TradeTimeEnd));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorPositionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTradingAccountField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTradingCodeField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "clientIDType", &p->ClientIDType, sizeof(p->ClientIDType));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorGroupField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentMarginRateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentCommissionRateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentTradingRightField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTraderField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySuperUserFunctionField *p)
{
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryUserSessionField *p)
{
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryPartBrokerField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryFrontStatusField *p)
{
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeOrderField *p)
{
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeOrderActionField *p)
{
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySuperUserField *p)
{
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryProductField *p)
{
    set_struct(obj, "productId", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "productClass", &p->ProductClass, sizeof(p->ProductClass));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "productId", &p->ProductID, sizeof(p->ProductID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryDepthMarketDataField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerUserField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerUserFunctionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTraderOfferField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySyncDepositField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "depositSeqNo", &p->DepositSeqNo, sizeof(p->DepositSeqNo));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySettlementInfoField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeMarginRateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeMarginRateAdjustField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeRateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "fromCurrencyId", &p->FromCurrencyID, sizeof(p->FromCurrencyID));
    set_struct(obj, "toCurrencyId", &p->ToCurrencyID, sizeof(p->ToCurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySyncFundMortgageField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "mortgageSeqNo", &p->MortgageSeqNo, sizeof(p->MortgageSeqNo));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryHisOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "insertTimeStart", &p->InsertTimeStart, sizeof(p->InsertTimeStart));
    set_struct(obj, "insertTimeEnd", &p->InsertTimeEnd, sizeof(p->InsertTimeEnd));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrMiniMarginField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "minMargin", &p->MinMargin, sizeof(p->MinMargin));
    set_struct(obj, "valueMethod", &p->ValueMethod, sizeof(p->ValueMethod));
    set_struct(obj, "isRelative", &p->IsRelative, sizeof(p->IsRelative));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrMarginAdjustField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "sShortMarginRatioByMoney", &p->SShortMarginRatioByMoney, sizeof(p->SShortMarginRatioByMoney));
    set_struct(obj, "sShortMarginRatioByVolume", &p->SShortMarginRatioByVolume, sizeof(p->SShortMarginRatioByVolume));
    set_struct(obj, "hShortMarginRatioByMoney", &p->HShortMarginRatioByMoney, sizeof(p->HShortMarginRatioByMoney));
    set_struct(obj, "hShortMarginRatioByVolume", &p->HShortMarginRatioByVolume, sizeof(p->HShortMarginRatioByVolume));
    set_struct(obj, "aShortMarginRatioByMoney", &p->AShortMarginRatioByMoney, sizeof(p->AShortMarginRatioByMoney));
    set_struct(obj, "aShortMarginRatioByVolume", &p->AShortMarginRatioByVolume, sizeof(p->AShortMarginRatioByVolume));
    set_struct(obj, "isRelative", &p->IsRelative, sizeof(p->IsRelative));
    set_struct(obj, "mShortMarginRatioByMoney", &p->MShortMarginRatioByMoney, sizeof(p->MShortMarginRatioByMoney));
    set_struct(obj, "mShortMarginRatioByVolume", &p->MShortMarginRatioByVolume, sizeof(p->MShortMarginRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrCommRateField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "openRatioByMoney", &p->OpenRatioByMoney, sizeof(p->OpenRatioByMoney));
    set_struct(obj, "openRatioByVolume", &p->OpenRatioByVolume, sizeof(p->OpenRatioByVolume));
    set_struct(obj, "closeRatioByMoney", &p->CloseRatioByMoney, sizeof(p->CloseRatioByMoney));
    set_struct(obj, "closeRatioByVolume", &p->CloseRatioByVolume, sizeof(p->CloseRatioByVolume));
    set_struct(obj, "closeTodayRatioByMoney", &p->CloseTodayRatioByMoney, sizeof(p->CloseTodayRatioByMoney));
    set_struct(obj, "closeTodayRatioByVolume", &p->CloseTodayRatioByVolume, sizeof(p->CloseTodayRatioByVolume));
    set_struct(obj, "strikeRatioByMoney", &p->StrikeRatioByMoney, sizeof(p->StrikeRatioByMoney));
    set_struct(obj, "strikeRatioByVolume", &p->StrikeRatioByVolume, sizeof(p->StrikeRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrTradeCostField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "fixedMargin", &p->FixedMargin, sizeof(p->FixedMargin));
    set_struct(obj, "miniMargin", &p->MiniMargin, sizeof(p->MiniMargin));
    set_struct(obj, "royalty", &p->Royalty, sizeof(p->Royalty));
    set_struct(obj, "exchFixedMargin", &p->ExchFixedMargin, sizeof(p->ExchFixedMargin));
    set_struct(obj, "exchMiniMargin", &p->ExchMiniMargin, sizeof(p->ExchMiniMargin));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryOptionInstrTradeCostField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "inputPrice", &p->InputPrice, sizeof(p->InputPrice));
    set_struct(obj, "underlyingPrice", &p->UnderlyingPrice, sizeof(p->UnderlyingPrice));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryOptionInstrCommRateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcIndexPriceField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "closePrice", &p->ClosePrice, sizeof(p->ClosePrice));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputExecOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "execOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "offsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "actionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "posiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "reservePositionFlag", &p->ReservePositionFlag, sizeof(p->ReservePositionFlag));
    set_struct(obj, "closeFlag", &p->CloseFlag, sizeof(p->CloseFlag));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputExecOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "execOrderActionRef", &p->ExecOrderActionRef, sizeof(p->ExecOrderActionRef));
    set_struct(obj, "execOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "execOrderSysId", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExecOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "execOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "offsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "actionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "posiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "reservePositionFlag", &p->ReservePositionFlag, sizeof(p->ReservePositionFlag));
    set_struct(obj, "closeFlag", &p->CloseFlag, sizeof(p->CloseFlag));
    set_struct(obj, "execOrderLocalId", &p->ExecOrderLocalID, sizeof(p->ExecOrderLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "notifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "execOrderSysId", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "insertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "insertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "cancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "execResult", &p->ExecResult, sizeof(p->ExecResult));
    set_struct(obj, "clearingPartId", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "activeUserId", &p->ActiveUserID, sizeof(p->ActiveUserID));
    set_struct(obj, "brokerExecOrderSeq", &p->BrokerExecOrderSeq, sizeof(p->BrokerExecOrderSeq));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExecOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "execOrderActionRef", &p->ExecOrderActionRef, sizeof(p->ExecOrderActionRef));
    set_struct(obj, "execOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "execOrderSysId", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "actionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "actionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "execOrderLocalId", &p->ExecOrderLocalID, sizeof(p->ExecOrderLocalID));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "orderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "actionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExecOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "execOrderSysId", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "insertTimeStart", &p->InsertTimeStart, sizeof(p->InsertTimeStart));
    set_struct(obj, "insertTimeEnd", &p->InsertTimeEnd, sizeof(p->InsertTimeEnd));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeExecOrderField *p)
{
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "offsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "actionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "posiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "reservePositionFlag", &p->ReservePositionFlag, sizeof(p->ReservePositionFlag));
    set_struct(obj, "closeFlag", &p->CloseFlag, sizeof(p->CloseFlag));
    set_struct(obj, "execOrderLocalId", &p->ExecOrderLocalID, sizeof(p->ExecOrderLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "notifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "execOrderSysId", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "insertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "insertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "cancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "execResult", &p->ExecResult, sizeof(p->ExecResult));
    set_struct(obj, "clearingPartId", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeExecOrderField *p)
{
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExecOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeExecOrderActionField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "execOrderSysId", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "actionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "actionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "execOrderLocalId", &p->ExecOrderLocalID, sizeof(p->ExecOrderLocalID));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "orderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "actionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeExecOrderActionField *p)
{
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcErrExecOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "execOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "offsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "actionType", &p->ActionType, sizeof(p->ActionType));
    set_struct(obj, "posiDirection", &p->PosiDirection, sizeof(p->PosiDirection));
    set_struct(obj, "reservePositionFlag", &p->ReservePositionFlag, sizeof(p->ReservePositionFlag));
    set_struct(obj, "closeFlag", &p->CloseFlag, sizeof(p->CloseFlag));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryErrExecOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcErrExecOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "execOrderActionRef", &p->ExecOrderActionRef, sizeof(p->ExecOrderActionRef));
    set_struct(obj, "execOrderRef", &p->ExecOrderRef, sizeof(p->ExecOrderRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "execOrderSysId", &p->ExecOrderSysID, sizeof(p->ExecOrderSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryErrExecOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrTradingRightField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "tradingRight", &p->TradingRight, sizeof(p->TradingRight));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryOptionInstrTradingRightField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputForQuoteField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "forQuoteRef", &p->ForQuoteRef, sizeof(p->ForQuoteRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcForQuoteField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "forQuoteRef", &p->ForQuoteRef, sizeof(p->ForQuoteRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "forQuoteLocalId", &p->ForQuoteLocalID, sizeof(p->ForQuoteLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "insertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "insertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "forQuoteStatus", &p->ForQuoteStatus, sizeof(p->ForQuoteStatus));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "activeUserId", &p->ActiveUserID, sizeof(p->ActiveUserID));
    set_struct(obj, "brokerForQutoSeq", &p->BrokerForQutoSeq, sizeof(p->BrokerForQutoSeq));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryForQuoteField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "insertTimeStart", &p->InsertTimeStart, sizeof(p->InsertTimeStart));
    set_struct(obj, "insertTimeEnd", &p->InsertTimeEnd, sizeof(p->InsertTimeEnd));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeForQuoteField *p)
{
    set_struct(obj, "forQuoteLocalId", &p->ForQuoteLocalID, sizeof(p->ForQuoteLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "insertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "insertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "forQuoteStatus", &p->ForQuoteStatus, sizeof(p->ForQuoteStatus));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeForQuoteField *p)
{
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputQuoteField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "quoteRef", &p->QuoteRef, sizeof(p->QuoteRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "askPrice", &p->AskPrice, sizeof(p->AskPrice));
    set_struct(obj, "bidPrice", &p->BidPrice, sizeof(p->BidPrice));
    set_struct(obj, "askVolume", &p->AskVolume, sizeof(p->AskVolume));
    set_struct(obj, "bidVolume", &p->BidVolume, sizeof(p->BidVolume));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "askOffsetFlag", &p->AskOffsetFlag, sizeof(p->AskOffsetFlag));
    set_struct(obj, "bidOffsetFlag", &p->BidOffsetFlag, sizeof(p->BidOffsetFlag));
    set_struct(obj, "askHedgeFlag", &p->AskHedgeFlag, sizeof(p->AskHedgeFlag));
    set_struct(obj, "bidHedgeFlag", &p->BidHedgeFlag, sizeof(p->BidHedgeFlag));
    set_struct(obj, "askOrderRef", &p->AskOrderRef, sizeof(p->AskOrderRef));
    set_struct(obj, "bidOrderRef", &p->BidOrderRef, sizeof(p->BidOrderRef));
    set_struct(obj, "forQuoteSysId", &p->ForQuoteSysID, sizeof(p->ForQuoteSysID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputQuoteActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "quoteActionRef", &p->QuoteActionRef, sizeof(p->QuoteActionRef));
    set_struct(obj, "quoteRef", &p->QuoteRef, sizeof(p->QuoteRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "quoteSysId", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQuoteField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "quoteRef", &p->QuoteRef, sizeof(p->QuoteRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "askPrice", &p->AskPrice, sizeof(p->AskPrice));
    set_struct(obj, "bidPrice", &p->BidPrice, sizeof(p->BidPrice));
    set_struct(obj, "askVolume", &p->AskVolume, sizeof(p->AskVolume));
    set_struct(obj, "bidVolume", &p->BidVolume, sizeof(p->BidVolume));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "askOffsetFlag", &p->AskOffsetFlag, sizeof(p->AskOffsetFlag));
    set_struct(obj, "bidOffsetFlag", &p->BidOffsetFlag, sizeof(p->BidOffsetFlag));
    set_struct(obj, "askHedgeFlag", &p->AskHedgeFlag, sizeof(p->AskHedgeFlag));
    set_struct(obj, "bidHedgeFlag", &p->BidHedgeFlag, sizeof(p->BidHedgeFlag));
    set_struct(obj, "quoteLocalId", &p->QuoteLocalID, sizeof(p->QuoteLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "notifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "orderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "quoteSysId", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "insertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "insertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "cancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "quoteStatus", &p->QuoteStatus, sizeof(p->QuoteStatus));
    set_struct(obj, "clearingPartId", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "askOrderSysId", &p->AskOrderSysID, sizeof(p->AskOrderSysID));
    set_struct(obj, "bidOrderSysId", &p->BidOrderSysID, sizeof(p->BidOrderSysID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "activeUserId", &p->ActiveUserID, sizeof(p->ActiveUserID));
    set_struct(obj, "brokerQuoteSeq", &p->BrokerQuoteSeq, sizeof(p->BrokerQuoteSeq));
    set_struct(obj, "askOrderRef", &p->AskOrderRef, sizeof(p->AskOrderRef));
    set_struct(obj, "bidOrderRef", &p->BidOrderRef, sizeof(p->BidOrderRef));
    set_struct(obj, "forQuoteSysId", &p->ForQuoteSysID, sizeof(p->ForQuoteSysID));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQuoteActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "quoteActionRef", &p->QuoteActionRef, sizeof(p->QuoteActionRef));
    set_struct(obj, "quoteRef", &p->QuoteRef, sizeof(p->QuoteRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "quoteSysId", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "actionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "actionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "quoteLocalId", &p->QuoteLocalID, sizeof(p->QuoteLocalID));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "orderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryQuoteField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "quoteSysId", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "insertTimeStart", &p->InsertTimeStart, sizeof(p->InsertTimeStart));
    set_struct(obj, "insertTimeEnd", &p->InsertTimeEnd, sizeof(p->InsertTimeEnd));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeQuoteField *p)
{
    set_struct(obj, "askPrice", &p->AskPrice, sizeof(p->AskPrice));
    set_struct(obj, "bidPrice", &p->BidPrice, sizeof(p->BidPrice));
    set_struct(obj, "askVolume", &p->AskVolume, sizeof(p->AskVolume));
    set_struct(obj, "bidVolume", &p->BidVolume, sizeof(p->BidVolume));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "askOffsetFlag", &p->AskOffsetFlag, sizeof(p->AskOffsetFlag));
    set_struct(obj, "bidOffsetFlag", &p->BidOffsetFlag, sizeof(p->BidOffsetFlag));
    set_struct(obj, "askHedgeFlag", &p->AskHedgeFlag, sizeof(p->AskHedgeFlag));
    set_struct(obj, "bidHedgeFlag", &p->BidHedgeFlag, sizeof(p->BidHedgeFlag));
    set_struct(obj, "quoteLocalId", &p->QuoteLocalID, sizeof(p->QuoteLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "notifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "orderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "quoteSysId", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "insertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "insertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "cancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "quoteStatus", &p->QuoteStatus, sizeof(p->QuoteStatus));
    set_struct(obj, "clearingPartId", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "askOrderSysId", &p->AskOrderSysID, sizeof(p->AskOrderSysID));
    set_struct(obj, "bidOrderSysId", &p->BidOrderSysID, sizeof(p->BidOrderSysID));
    set_struct(obj, "forQuoteSysId", &p->ForQuoteSysID, sizeof(p->ForQuoteSysID));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeQuoteField *p)
{
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryQuoteActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeQuoteActionField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "quoteSysId", &p->QuoteSysID, sizeof(p->QuoteSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "actionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "actionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "quoteLocalId", &p->QuoteLocalID, sizeof(p->QuoteLocalID));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "orderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeQuoteActionField *p)
{
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcOptionInstrDeltaField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "delta", &p->Delta, sizeof(p->Delta));
}
static void set_struct(Local<Object>& obj, CThostFtdcForQuoteRspField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "forQuoteSysId", &p->ForQuoteSysID, sizeof(p->ForQuoteSysID));
    set_struct(obj, "forQuoteTime", &p->ForQuoteTime, sizeof(p->ForQuoteTime));
    set_struct(obj, "actionDay", &p->ActionDay, sizeof(p->ActionDay));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcStrikeOffsetField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "offset", &p->Offset, sizeof(p->Offset));
    set_struct(obj, "offsetType", &p->OffsetType, sizeof(p->OffsetType));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryStrikeOffsetField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputBatchOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "orderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcBatchOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "orderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "actionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "actionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "orderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeBatchOrderActionField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "actionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "actionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "orderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBatchOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcCombInstrumentGuardField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "guarantRatio", &p->GuarantRatio, sizeof(p->GuarantRatio));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCombInstrumentGuardField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInputCombActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "combActionRef", &p->CombActionRef, sizeof(p->CombActionRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "combDirection", &p->CombDirection, sizeof(p->CombDirection));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcCombActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "combActionRef", &p->CombActionRef, sizeof(p->CombActionRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "combDirection", &p->CombDirection, sizeof(p->CombDirection));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "actionStatus", &p->ActionStatus, sizeof(p->ActionStatus));
    set_struct(obj, "notifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCombActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeCombActionField *p)
{
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "combDirection", &p->CombDirection, sizeof(p->CombDirection));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "actionStatus", &p->ActionStatus, sizeof(p->ActionStatus));
    set_struct(obj, "notifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeCombActionField *p)
{
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcProductExchRateField *p)
{
    set_struct(obj, "productId", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "quoteCurrencyId", &p->QuoteCurrencyID, sizeof(p->QuoteCurrencyID));
    set_struct(obj, "exchangeRate", &p->ExchangeRate, sizeof(p->ExchangeRate));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryProductExchRateField *p)
{
    set_struct(obj, "productId", &p->ProductID, sizeof(p->ProductID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryForQuoteParamField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcForQuoteParamField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "lastPrice", &p->LastPrice, sizeof(p->LastPrice));
    set_struct(obj, "priceInterval", &p->PriceInterval, sizeof(p->PriceInterval));
}
static void set_struct(Local<Object>& obj, CThostFtdcMMOptionInstrCommRateField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "openRatioByMoney", &p->OpenRatioByMoney, sizeof(p->OpenRatioByMoney));
    set_struct(obj, "openRatioByVolume", &p->OpenRatioByVolume, sizeof(p->OpenRatioByVolume));
    set_struct(obj, "closeRatioByMoney", &p->CloseRatioByMoney, sizeof(p->CloseRatioByMoney));
    set_struct(obj, "closeRatioByVolume", &p->CloseRatioByVolume, sizeof(p->CloseRatioByVolume));
    set_struct(obj, "closeTodayRatioByMoney", &p->CloseTodayRatioByMoney, sizeof(p->CloseTodayRatioByMoney));
    set_struct(obj, "closeTodayRatioByVolume", &p->CloseTodayRatioByVolume, sizeof(p->CloseTodayRatioByVolume));
    set_struct(obj, "strikeRatioByMoney", &p->StrikeRatioByMoney, sizeof(p->StrikeRatioByMoney));
    set_struct(obj, "strikeRatioByVolume", &p->StrikeRatioByVolume, sizeof(p->StrikeRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryMMOptionInstrCommRateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMMInstrumentCommissionRateField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "openRatioByMoney", &p->OpenRatioByMoney, sizeof(p->OpenRatioByMoney));
    set_struct(obj, "openRatioByVolume", &p->OpenRatioByVolume, sizeof(p->OpenRatioByVolume));
    set_struct(obj, "closeRatioByMoney", &p->CloseRatioByMoney, sizeof(p->CloseRatioByMoney));
    set_struct(obj, "closeRatioByVolume", &p->CloseRatioByVolume, sizeof(p->CloseRatioByVolume));
    set_struct(obj, "closeTodayRatioByMoney", &p->CloseTodayRatioByMoney, sizeof(p->CloseTodayRatioByMoney));
    set_struct(obj, "closeTodayRatioByVolume", &p->CloseTodayRatioByVolume, sizeof(p->CloseTodayRatioByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryMMInstrumentCommissionRateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentOrderCommRateField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "orderCommByVolume", &p->OrderCommByVolume, sizeof(p->OrderCommByVolume));
    set_struct(obj, "orderActionCommByVolume", &p->OrderActionCommByVolume, sizeof(p->OrderActionCommByVolume));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentOrderCommRateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "lastPrice", &p->LastPrice, sizeof(p->LastPrice));
    set_struct(obj, "preSettlementPrice", &p->PreSettlementPrice, sizeof(p->PreSettlementPrice));
    set_struct(obj, "preClosePrice", &p->PreClosePrice, sizeof(p->PreClosePrice));
    set_struct(obj, "preOpenInterest", &p->PreOpenInterest, sizeof(p->PreOpenInterest));
    set_struct(obj, "openPrice", &p->OpenPrice, sizeof(p->OpenPrice));
    set_struct(obj, "highestPrice", &p->HighestPrice, sizeof(p->HighestPrice));
    set_struct(obj, "lowestPrice", &p->LowestPrice, sizeof(p->LowestPrice));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "turnover", &p->Turnover, sizeof(p->Turnover));
    set_struct(obj, "openInterest", &p->OpenInterest, sizeof(p->OpenInterest));
    set_struct(obj, "closePrice", &p->ClosePrice, sizeof(p->ClosePrice));
    set_struct(obj, "settlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "upperLimitPrice", &p->UpperLimitPrice, sizeof(p->UpperLimitPrice));
    set_struct(obj, "lowerLimitPrice", &p->LowerLimitPrice, sizeof(p->LowerLimitPrice));
    set_struct(obj, "preDelta", &p->PreDelta, sizeof(p->PreDelta));
    set_struct(obj, "currDelta", &p->CurrDelta, sizeof(p->CurrDelta));
    set_struct(obj, "updateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "updateMillisec", &p->UpdateMillisec, sizeof(p->UpdateMillisec));
    set_struct(obj, "actionDay", &p->ActionDay, sizeof(p->ActionDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataBaseField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "preSettlementPrice", &p->PreSettlementPrice, sizeof(p->PreSettlementPrice));
    set_struct(obj, "preClosePrice", &p->PreClosePrice, sizeof(p->PreClosePrice));
    set_struct(obj, "preOpenInterest", &p->PreOpenInterest, sizeof(p->PreOpenInterest));
    set_struct(obj, "preDelta", &p->PreDelta, sizeof(p->PreDelta));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataStaticField *p)
{
    set_struct(obj, "openPrice", &p->OpenPrice, sizeof(p->OpenPrice));
    set_struct(obj, "highestPrice", &p->HighestPrice, sizeof(p->HighestPrice));
    set_struct(obj, "lowestPrice", &p->LowestPrice, sizeof(p->LowestPrice));
    set_struct(obj, "closePrice", &p->ClosePrice, sizeof(p->ClosePrice));
    set_struct(obj, "upperLimitPrice", &p->UpperLimitPrice, sizeof(p->UpperLimitPrice));
    set_struct(obj, "lowerLimitPrice", &p->LowerLimitPrice, sizeof(p->LowerLimitPrice));
    set_struct(obj, "settlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "currDelta", &p->CurrDelta, sizeof(p->CurrDelta));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataLastMatchField *p)
{
    set_struct(obj, "lastPrice", &p->LastPrice, sizeof(p->LastPrice));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "turnover", &p->Turnover, sizeof(p->Turnover));
    set_struct(obj, "openInterest", &p->OpenInterest, sizeof(p->OpenInterest));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataBestPriceField *p)
{
    set_struct(obj, "bidPrice1", &p->BidPrice1, sizeof(p->BidPrice1));
    set_struct(obj, "bidVolume1", &p->BidVolume1, sizeof(p->BidVolume1));
    set_struct(obj, "askPrice1", &p->AskPrice1, sizeof(p->AskPrice1));
    set_struct(obj, "askVolume1", &p->AskVolume1, sizeof(p->AskVolume1));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataBid23Field *p)
{
    set_struct(obj, "bidPrice2", &p->BidPrice2, sizeof(p->BidPrice2));
    set_struct(obj, "bidVolume2", &p->BidVolume2, sizeof(p->BidVolume2));
    set_struct(obj, "bidPrice3", &p->BidPrice3, sizeof(p->BidPrice3));
    set_struct(obj, "bidVolume3", &p->BidVolume3, sizeof(p->BidVolume3));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataAsk23Field *p)
{
    set_struct(obj, "askPrice2", &p->AskPrice2, sizeof(p->AskPrice2));
    set_struct(obj, "askVolume2", &p->AskVolume2, sizeof(p->AskVolume2));
    set_struct(obj, "askPrice3", &p->AskPrice3, sizeof(p->AskPrice3));
    set_struct(obj, "askVolume3", &p->AskVolume3, sizeof(p->AskVolume3));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataBid45Field *p)
{
    set_struct(obj, "bidPrice4", &p->BidPrice4, sizeof(p->BidPrice4));
    set_struct(obj, "bidVolume4", &p->BidVolume4, sizeof(p->BidVolume4));
    set_struct(obj, "bidPrice5", &p->BidPrice5, sizeof(p->BidPrice5));
    set_struct(obj, "bidVolume5", &p->BidVolume5, sizeof(p->BidVolume5));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataAsk45Field *p)
{
    set_struct(obj, "askPrice4", &p->AskPrice4, sizeof(p->AskPrice4));
    set_struct(obj, "askVolume4", &p->AskVolume4, sizeof(p->AskVolume4));
    set_struct(obj, "askPrice5", &p->AskPrice5, sizeof(p->AskPrice5));
    set_struct(obj, "askVolume5", &p->AskVolume5, sizeof(p->AskVolume5));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataUpdateTimeField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "updateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "updateMillisec", &p->UpdateMillisec, sizeof(p->UpdateMillisec));
    set_struct(obj, "actionDay", &p->ActionDay, sizeof(p->ActionDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataExchangeField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcSpecificInstrumentField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInstrumentStatusField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "settlementGroupId", &p->SettlementGroupID, sizeof(p->SettlementGroupID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "instrumentStatus", &p->InstrumentStatus, sizeof(p->InstrumentStatus));
    set_struct(obj, "tradingSegmentSn", &p->TradingSegmentSN, sizeof(p->TradingSegmentSN));
    set_struct(obj, "enterTime", &p->EnterTime, sizeof(p->EnterTime));
    set_struct(obj, "enterReason", &p->EnterReason, sizeof(p->EnterReason));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInstrumentStatusField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorAccountField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcPositionProfitAlgorithmField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "algorithm", &p->Algorithm, sizeof(p->Algorithm));
    set_struct(obj, "memo", &p->Memo, sizeof(p->Memo));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcDiscountField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "discount", &p->Discount, sizeof(p->Discount));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTransferBankField *p)
{
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBrchId", &p->BankBrchID, sizeof(p->BankBrchID));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferBankField *p)
{
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBrchId", &p->BankBrchID, sizeof(p->BankBrchID));
    set_struct(obj, "bankName", &p->BankName, sizeof(p->BankName));
    set_struct(obj, "isActive", &p->IsActive, sizeof(p->IsActive));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorPositionDetailField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorPositionDetailField *p)
{
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "openDate", &p->OpenDate, sizeof(p->OpenDate));
    set_struct(obj, "tradeId", &p->TradeID, sizeof(p->TradeID));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
    set_struct(obj, "openPrice", &p->OpenPrice, sizeof(p->OpenPrice));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "tradeType", &p->TradeType, sizeof(p->TradeType));
    set_struct(obj, "combInstrumentId", &p->CombInstrumentID, sizeof(p->CombInstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "closeProfitByDate", &p->CloseProfitByDate, sizeof(p->CloseProfitByDate));
    set_struct(obj, "closeProfitByTrade", &p->CloseProfitByTrade, sizeof(p->CloseProfitByTrade));
    set_struct(obj, "positionProfitByDate", &p->PositionProfitByDate, sizeof(p->PositionProfitByDate));
    set_struct(obj, "positionProfitByTrade", &p->PositionProfitByTrade, sizeof(p->PositionProfitByTrade));
    set_struct(obj, "margin", &p->Margin, sizeof(p->Margin));
    set_struct(obj, "exchMargin", &p->ExchMargin, sizeof(p->ExchMargin));
    set_struct(obj, "marginRateByMoney", &p->MarginRateByMoney, sizeof(p->MarginRateByMoney));
    set_struct(obj, "marginRateByVolume", &p->MarginRateByVolume, sizeof(p->MarginRateByVolume));
    set_struct(obj, "lastSettlementPrice", &p->LastSettlementPrice, sizeof(p->LastSettlementPrice));
    set_struct(obj, "settlementPrice", &p->SettlementPrice, sizeof(p->SettlementPrice));
    set_struct(obj, "closeVolume", &p->CloseVolume, sizeof(p->CloseVolume));
    set_struct(obj, "closeAmount", &p->CloseAmount, sizeof(p->CloseAmount));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingAccountPasswordField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMDTraderOfferField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "traderConnectStatus", &p->TraderConnectStatus, sizeof(p->TraderConnectStatus));
    set_struct(obj, "connectRequestDate", &p->ConnectRequestDate, sizeof(p->ConnectRequestDate));
    set_struct(obj, "connectRequestTime", &p->ConnectRequestTime, sizeof(p->ConnectRequestTime));
    set_struct(obj, "lastReportDate", &p->LastReportDate, sizeof(p->LastReportDate));
    set_struct(obj, "lastReportTime", &p->LastReportTime, sizeof(p->LastReportTime));
    set_struct(obj, "connectDate", &p->ConnectDate, sizeof(p->ConnectDate));
    set_struct(obj, "connectTime", &p->ConnectTime, sizeof(p->ConnectTime));
    set_struct(obj, "startDate", &p->StartDate, sizeof(p->StartDate));
    set_struct(obj, "startTime", &p->StartTime, sizeof(p->StartTime));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "maxTradeId", &p->MaxTradeID, sizeof(p->MaxTradeID));
    set_struct(obj, "maxOrderMessageReference", &p->MaxOrderMessageReference, sizeof(p->MaxOrderMessageReference));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryMDTraderOfferField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryNoticeField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcNoticeField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "content", &p->Content, sizeof(p->Content));
    set_struct(obj, "sequenceLabel", &p->SequenceLabel, sizeof(p->SequenceLabel));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserRightField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "userRightType", &p->UserRightType, sizeof(p->UserRightType));
    set_struct(obj, "isForbidden", &p->IsForbidden, sizeof(p->IsForbidden));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySettlementInfoConfirmField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcLoadSettlementInfoField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerWithdrawAlgorithmField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "withdrawAlgorithm", &p->WithdrawAlgorithm, sizeof(p->WithdrawAlgorithm));
    set_struct(obj, "usingRatio", &p->UsingRatio, sizeof(p->UsingRatio));
    set_struct(obj, "includeCloseProfit", &p->IncludeCloseProfit, sizeof(p->IncludeCloseProfit));
    set_struct(obj, "allWithoutTrade", &p->AllWithoutTrade, sizeof(p->AllWithoutTrade));
    set_struct(obj, "availIncludeCloseProfit", &p->AvailIncludeCloseProfit, sizeof(p->AvailIncludeCloseProfit));
    set_struct(obj, "isBrokerUserEvent", &p->IsBrokerUserEvent, sizeof(p->IsBrokerUserEvent));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "fundMortgageRatio", &p->FundMortgageRatio, sizeof(p->FundMortgageRatio));
    set_struct(obj, "balanceAlgorithm", &p->BalanceAlgorithm, sizeof(p->BalanceAlgorithm));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingAccountPasswordUpdateV1Field *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "oldPassword", &p->OldPassword, sizeof(p->OldPassword));
    set_struct(obj, "newPassword", &p->NewPassword, sizeof(p->NewPassword));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingAccountPasswordUpdateField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "oldPassword", &p->OldPassword, sizeof(p->OldPassword));
    set_struct(obj, "newPassword", &p->NewPassword, sizeof(p->NewPassword));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCombinationLegField *p)
{
    set_struct(obj, "combInstrumentId", &p->CombInstrumentID, sizeof(p->CombInstrumentID));
    set_struct(obj, "legId", &p->LegID, sizeof(p->LegID));
    set_struct(obj, "legInstrumentId", &p->LegInstrumentID, sizeof(p->LegInstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySyncStatusField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
}
static void set_struct(Local<Object>& obj, CThostFtdcCombinationLegField *p)
{
    set_struct(obj, "combInstrumentId", &p->CombInstrumentID, sizeof(p->CombInstrumentID));
    set_struct(obj, "legId", &p->LegID, sizeof(p->LegID));
    set_struct(obj, "legInstrumentId", &p->LegInstrumentID, sizeof(p->LegInstrumentID));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "legMultiple", &p->LegMultiple, sizeof(p->LegMultiple));
    set_struct(obj, "implyLevel", &p->ImplyLevel, sizeof(p->ImplyLevel));
}
static void set_struct(Local<Object>& obj, CThostFtdcSyncStatusField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "dataSyncStatus", &p->DataSyncStatus, sizeof(p->DataSyncStatus));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryLinkManField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcLinkManField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "personType", &p->PersonType, sizeof(p->PersonType));
    set_struct(obj, "identifiedCardType", &p->IdentifiedCardType, sizeof(p->IdentifiedCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "personName", &p->PersonName, sizeof(p->PersonName));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "zipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "priority", &p->Priority, sizeof(p->Priority));
    set_struct(obj, "uOAZipCode", &p->UOAZipCode, sizeof(p->UOAZipCode));
    set_struct(obj, "personFullName", &p->PersonFullName, sizeof(p->PersonFullName));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerUserEventField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "userEventType", &p->UserEventType, sizeof(p->UserEventType));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserEventField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "userEventType", &p->UserEventType, sizeof(p->UserEventType));
    set_struct(obj, "eventSequenceNo", &p->EventSequenceNo, sizeof(p->EventSequenceNo));
    set_struct(obj, "eventDate", &p->EventDate, sizeof(p->EventDate));
    set_struct(obj, "eventTime", &p->EventTime, sizeof(p->EventTime));
    set_struct(obj, "userEventInfo", &p->UserEventInfo, sizeof(p->UserEventInfo));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryContractBankField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBrchId", &p->BankBrchID, sizeof(p->BankBrchID));
}
static void set_struct(Local<Object>& obj, CThostFtdcContractBankField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBrchId", &p->BankBrchID, sizeof(p->BankBrchID));
    set_struct(obj, "bankName", &p->BankName, sizeof(p->BankName));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorPositionCombineDetailField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "openDate", &p->OpenDate, sizeof(p->OpenDate));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "comTradeId", &p->ComTradeID, sizeof(p->ComTradeID));
    set_struct(obj, "tradeId", &p->TradeID, sizeof(p->TradeID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "totalAmt", &p->TotalAmt, sizeof(p->TotalAmt));
    set_struct(obj, "margin", &p->Margin, sizeof(p->Margin));
    set_struct(obj, "exchMargin", &p->ExchMargin, sizeof(p->ExchMargin));
    set_struct(obj, "marginRateByMoney", &p->MarginRateByMoney, sizeof(p->MarginRateByMoney));
    set_struct(obj, "marginRateByVolume", &p->MarginRateByVolume, sizeof(p->MarginRateByVolume));
    set_struct(obj, "legId", &p->LegID, sizeof(p->LegID));
    set_struct(obj, "legMultiple", &p->LegMultiple, sizeof(p->LegMultiple));
    set_struct(obj, "combInstrumentId", &p->CombInstrumentID, sizeof(p->CombInstrumentID));
    set_struct(obj, "tradeGroupId", &p->TradeGroupID, sizeof(p->TradeGroupID));
}
static void set_struct(Local<Object>& obj, CThostFtdcParkedOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "orderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "orderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "combOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "combHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "timeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "gtdDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "volumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "minVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "contingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "stopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "forceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "isAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "userForceClose", &p->UserForceClose, sizeof(p->UserForceClose));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "parkedOrderId", &p->ParkedOrderID, sizeof(p->ParkedOrderID));
    set_struct(obj, "userType", &p->UserType, sizeof(p->UserType));
    set_struct(obj, "status", &p->Status, sizeof(p->Status));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "isSwapOrder", &p->IsSwapOrder, sizeof(p->IsSwapOrder));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcParkedOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "orderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "orderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeChange", &p->VolumeChange, sizeof(p->VolumeChange));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "parkedOrderActionId", &p->ParkedOrderActionID, sizeof(p->ParkedOrderActionID));
    set_struct(obj, "userType", &p->UserType, sizeof(p->UserType));
    set_struct(obj, "status", &p->Status, sizeof(p->Status));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryParkedOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryParkedOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRemoveParkedOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "parkedOrderId", &p->ParkedOrderID, sizeof(p->ParkedOrderID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRemoveParkedOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "parkedOrderActionId", &p->ParkedOrderActionID, sizeof(p->ParkedOrderActionID));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorWithdrawAlgorithmField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "usingRatio", &p->UsingRatio, sizeof(p->UsingRatio));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "fundMortgageRatio", &p->FundMortgageRatio, sizeof(p->FundMortgageRatio));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorPositionCombineDetailField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "combInstrumentId", &p->CombInstrumentID, sizeof(p->CombInstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarketDataAveragePriceField *p)
{
    set_struct(obj, "averagePrice", &p->AveragePrice, sizeof(p->AveragePrice));
}
static void set_struct(Local<Object>& obj, CThostFtdcVerifyInvestorPasswordField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserIPField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "iPMask", &p->IPMask, sizeof(p->IPMask));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingNoticeInfoField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "sendTime", &p->SendTime, sizeof(p->SendTime));
    set_struct(obj, "fieldContent", &p->FieldContent, sizeof(p->FieldContent));
    set_struct(obj, "sequenceSeries", &p->SequenceSeries, sizeof(p->SequenceSeries));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingNoticeField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorRange", &p->InvestorRange, sizeof(p->InvestorRange));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "sequenceSeries", &p->SequenceSeries, sizeof(p->SequenceSeries));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "sendTime", &p->SendTime, sizeof(p->SendTime));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "fieldContent", &p->FieldContent, sizeof(p->FieldContent));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTradingNoticeField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryErrOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcErrOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "orderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "orderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "combOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "combHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "timeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "gtdDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "volumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "minVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "contingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "stopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "forceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "isAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "userForceClose", &p->UserForceClose, sizeof(p->UserForceClose));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "isSwapOrder", &p->IsSwapOrder, sizeof(p->IsSwapOrder));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcErrorConditionalOrderField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "orderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "orderPriceType", &p->OrderPriceType, sizeof(p->OrderPriceType));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "combOffsetFlag", &p->CombOffsetFlag, sizeof(p->CombOffsetFlag));
    set_struct(obj, "combHedgeFlag", &p->CombHedgeFlag, sizeof(p->CombHedgeFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeTotalOriginal", &p->VolumeTotalOriginal, sizeof(p->VolumeTotalOriginal));
    set_struct(obj, "timeCondition", &p->TimeCondition, sizeof(p->TimeCondition));
    set_struct(obj, "gtdDate", &p->GTDDate, sizeof(p->GTDDate));
    set_struct(obj, "volumeCondition", &p->VolumeCondition, sizeof(p->VolumeCondition));
    set_struct(obj, "minVolume", &p->MinVolume, sizeof(p->MinVolume));
    set_struct(obj, "contingentCondition", &p->ContingentCondition, sizeof(p->ContingentCondition));
    set_struct(obj, "stopPrice", &p->StopPrice, sizeof(p->StopPrice));
    set_struct(obj, "forceCloseReason", &p->ForceCloseReason, sizeof(p->ForceCloseReason));
    set_struct(obj, "isAutoSuspend", &p->IsAutoSuspend, sizeof(p->IsAutoSuspend));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "exchangeInstId", &p->ExchangeInstID, sizeof(p->ExchangeInstID));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderSubmitStatus", &p->OrderSubmitStatus, sizeof(p->OrderSubmitStatus));
    set_struct(obj, "notifySequence", &p->NotifySequence, sizeof(p->NotifySequence));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "orderSource", &p->OrderSource, sizeof(p->OrderSource));
    set_struct(obj, "orderStatus", &p->OrderStatus, sizeof(p->OrderStatus));
    set_struct(obj, "orderType", &p->OrderType, sizeof(p->OrderType));
    set_struct(obj, "volumeTraded", &p->VolumeTraded, sizeof(p->VolumeTraded));
    set_struct(obj, "volumeTotal", &p->VolumeTotal, sizeof(p->VolumeTotal));
    set_struct(obj, "insertDate", &p->InsertDate, sizeof(p->InsertDate));
    set_struct(obj, "insertTime", &p->InsertTime, sizeof(p->InsertTime));
    set_struct(obj, "activeTime", &p->ActiveTime, sizeof(p->ActiveTime));
    set_struct(obj, "suspendTime", &p->SuspendTime, sizeof(p->SuspendTime));
    set_struct(obj, "updateTime", &p->UpdateTime, sizeof(p->UpdateTime));
    set_struct(obj, "cancelTime", &p->CancelTime, sizeof(p->CancelTime));
    set_struct(obj, "activeTraderId", &p->ActiveTraderID, sizeof(p->ActiveTraderID));
    set_struct(obj, "clearingPartId", &p->ClearingPartID, sizeof(p->ClearingPartID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "userForceClose", &p->UserForceClose, sizeof(p->UserForceClose));
    set_struct(obj, "activeUserId", &p->ActiveUserID, sizeof(p->ActiveUserID));
    set_struct(obj, "brokerOrderSeq", &p->BrokerOrderSeq, sizeof(p->BrokerOrderSeq));
    set_struct(obj, "relativeOrderSysId", &p->RelativeOrderSysID, sizeof(p->RelativeOrderSysID));
    set_struct(obj, "zceTotalTradedVolume", &p->ZCETotalTradedVolume, sizeof(p->ZCETotalTradedVolume));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "isSwapOrder", &p->IsSwapOrder, sizeof(p->IsSwapOrder));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryErrOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcErrOrderActionField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "orderActionRef", &p->OrderActionRef, sizeof(p->OrderActionRef));
    set_struct(obj, "orderRef", &p->OrderRef, sizeof(p->OrderRef));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "frontId", &p->FrontID, sizeof(p->FrontID));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "orderSysId", &p->OrderSysID, sizeof(p->OrderSysID));
    set_struct(obj, "actionFlag", &p->ActionFlag, sizeof(p->ActionFlag));
    set_struct(obj, "limitPrice", &p->LimitPrice, sizeof(p->LimitPrice));
    set_struct(obj, "volumeChange", &p->VolumeChange, sizeof(p->VolumeChange));
    set_struct(obj, "actionDate", &p->ActionDate, sizeof(p->ActionDate));
    set_struct(obj, "actionTime", &p->ActionTime, sizeof(p->ActionTime));
    set_struct(obj, "traderId", &p->TraderID, sizeof(p->TraderID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "orderLocalId", &p->OrderLocalID, sizeof(p->OrderLocalID));
    set_struct(obj, "actionLocalId", &p->ActionLocalID, sizeof(p->ActionLocalID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "clientId", &p->ClientID, sizeof(p->ClientID));
    set_struct(obj, "businessUnit", &p->BusinessUnit, sizeof(p->BusinessUnit));
    set_struct(obj, "orderActionStatus", &p->OrderActionStatus, sizeof(p->OrderActionStatus));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "statusMsg", &p->StatusMsg, sizeof(p->StatusMsg));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "branchId", &p->BranchID, sizeof(p->BranchID));
    set_struct(obj, "investUnitId", &p->InvestUnitID, sizeof(p->InvestUnitID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryExchangeSequenceField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcExchangeSequenceField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "marketStatus", &p->MarketStatus, sizeof(p->MarketStatus));
}
static void set_struct(Local<Object>& obj, CThostFtdcQueryMaxOrderVolumeWithPriceField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "offsetFlag", &p->OffsetFlag, sizeof(p->OffsetFlag));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "maxVolume", &p->MaxVolume, sizeof(p->MaxVolume));
    set_struct(obj, "price", &p->Price, sizeof(p->Price));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerTradingParamsField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerTradingParamsField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "marginPriceType", &p->MarginPriceType, sizeof(p->MarginPriceType));
    set_struct(obj, "algorithm", &p->Algorithm, sizeof(p->Algorithm));
    set_struct(obj, "availIncludeCloseProfit", &p->AvailIncludeCloseProfit, sizeof(p->AvailIncludeCloseProfit));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "optionRoyaltyPriceType", &p->OptionRoyaltyPriceType, sizeof(p->OptionRoyaltyPriceType));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBrokerTradingAlgosField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerTradingAlgosField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "handlePositionAlgoId", &p->HandlePositionAlgoID, sizeof(p->HandlePositionAlgoID));
    set_struct(obj, "findMarginRateAlgoId", &p->FindMarginRateAlgoID, sizeof(p->FindMarginRateAlgoID));
    set_struct(obj, "handleTradingAccountAlgoId", &p->HandleTradingAccountAlgoID, sizeof(p->HandleTradingAccountAlgoID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQueryBrokerDepositField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerDepositField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "preBalance", &p->PreBalance, sizeof(p->PreBalance));
    set_struct(obj, "currMargin", &p->CurrMargin, sizeof(p->CurrMargin));
    set_struct(obj, "closeProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "balance", &p->Balance, sizeof(p->Balance));
    set_struct(obj, "deposit", &p->Deposit, sizeof(p->Deposit));
    set_struct(obj, "withdraw", &p->Withdraw, sizeof(p->Withdraw));
    set_struct(obj, "available", &p->Available, sizeof(p->Available));
    set_struct(obj, "reserve", &p->Reserve, sizeof(p->Reserve));
    set_struct(obj, "frozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCFMMCBrokerKeyField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcCFMMCBrokerKeyField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "createDate", &p->CreateDate, sizeof(p->CreateDate));
    set_struct(obj, "createTime", &p->CreateTime, sizeof(p->CreateTime));
    set_struct(obj, "keyId", &p->KeyID, sizeof(p->KeyID));
    set_struct(obj, "currentKey", &p->CurrentKey, sizeof(p->CurrentKey));
    set_struct(obj, "keyKind", &p->KeyKind, sizeof(p->KeyKind));
}
static void set_struct(Local<Object>& obj, CThostFtdcCFMMCTradingAccountKeyField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "keyId", &p->KeyID, sizeof(p->KeyID));
    set_struct(obj, "currentKey", &p->CurrentKey, sizeof(p->CurrentKey));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCFMMCTradingAccountKeyField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserOTPParamField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "oTPVendorsId", &p->OTPVendorsID, sizeof(p->OTPVendorsID));
    set_struct(obj, "serialNumber", &p->SerialNumber, sizeof(p->SerialNumber));
    set_struct(obj, "authKey", &p->AuthKey, sizeof(p->AuthKey));
    set_struct(obj, "lastDrift", &p->LastDrift, sizeof(p->LastDrift));
    set_struct(obj, "lastSuccess", &p->LastSuccess, sizeof(p->LastSuccess));
    set_struct(obj, "oTPType", &p->OTPType, sizeof(p->OTPType));
}
static void set_struct(Local<Object>& obj, CThostFtdcManualSyncBrokerUserOTPField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "otpType", &p->OTPType, sizeof(p->OTPType));
    set_struct(obj, "firstOtp", &p->FirstOTP, sizeof(p->FirstOTP));
    set_struct(obj, "secondOtp", &p->SecondOTP, sizeof(p->SecondOTP));
}
static void set_struct(Local<Object>& obj, CThostFtdcCommRateModelField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "commModelId", &p->CommModelID, sizeof(p->CommModelID));
    set_struct(obj, "commModelName", &p->CommModelName, sizeof(p->CommModelName));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryCommRateModelField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "commModelId", &p->CommModelID, sizeof(p->CommModelID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMarginModelField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "marginModelId", &p->MarginModelID, sizeof(p->MarginModelID));
    set_struct(obj, "marginModelName", &p->MarginModelName, sizeof(p->MarginModelName));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryMarginModelField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "marginModelId", &p->MarginModelID, sizeof(p->MarginModelID));
}
static void set_struct(Local<Object>& obj, CThostFtdcEWarrantOffsetField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "direction", &p->Direction, sizeof(p->Direction));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
    set_struct(obj, "volume", &p->Volume, sizeof(p->Volume));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryEWarrantOffsetField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryInvestorProductGroupMarginField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "productGroupId", &p->ProductGroupID, sizeof(p->ProductGroupID));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
}
static void set_struct(Local<Object>& obj, CThostFtdcInvestorProductGroupMarginField *p)
{
    set_struct(obj, "productGroupId", &p->ProductGroupID, sizeof(p->ProductGroupID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "settlementId", &p->SettlementID, sizeof(p->SettlementID));
    set_struct(obj, "frozenMargin", &p->FrozenMargin, sizeof(p->FrozenMargin));
    set_struct(obj, "longFrozenMargin", &p->LongFrozenMargin, sizeof(p->LongFrozenMargin));
    set_struct(obj, "shortFrozenMargin", &p->ShortFrozenMargin, sizeof(p->ShortFrozenMargin));
    set_struct(obj, "useMargin", &p->UseMargin, sizeof(p->UseMargin));
    set_struct(obj, "longUseMargin", &p->LongUseMargin, sizeof(p->LongUseMargin));
    set_struct(obj, "shortUseMargin", &p->ShortUseMargin, sizeof(p->ShortUseMargin));
    set_struct(obj, "exchMargin", &p->ExchMargin, sizeof(p->ExchMargin));
    set_struct(obj, "longExchMargin", &p->LongExchMargin, sizeof(p->LongExchMargin));
    set_struct(obj, "shortExchMargin", &p->ShortExchMargin, sizeof(p->ShortExchMargin));
    set_struct(obj, "closeProfit", &p->CloseProfit, sizeof(p->CloseProfit));
    set_struct(obj, "frozenCommission", &p->FrozenCommission, sizeof(p->FrozenCommission));
    set_struct(obj, "commission", &p->Commission, sizeof(p->Commission));
    set_struct(obj, "frozenCash", &p->FrozenCash, sizeof(p->FrozenCash));
    set_struct(obj, "cashIn", &p->CashIn, sizeof(p->CashIn));
    set_struct(obj, "positionProfit", &p->PositionProfit, sizeof(p->PositionProfit));
    set_struct(obj, "offsetAmount", &p->OffsetAmount, sizeof(p->OffsetAmount));
    set_struct(obj, "longOffsetAmount", &p->LongOffsetAmount, sizeof(p->LongOffsetAmount));
    set_struct(obj, "shortOffsetAmount", &p->ShortOffsetAmount, sizeof(p->ShortOffsetAmount));
    set_struct(obj, "exchOffsetAmount", &p->ExchOffsetAmount, sizeof(p->ExchOffsetAmount));
    set_struct(obj, "longExchOffsetAmount", &p->LongExchOffsetAmount, sizeof(p->LongExchOffsetAmount));
    set_struct(obj, "shortExchOffsetAmount", &p->ShortExchOffsetAmount, sizeof(p->ShortExchOffsetAmount));
    set_struct(obj, "hedgeFlag", &p->HedgeFlag, sizeof(p->HedgeFlag));
}
static void set_struct(Local<Object>& obj, CThostFtdcQueryCFMMCTradingAccountTokenField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}
static void set_struct(Local<Object>& obj, CThostFtdcCFMMCTradingAccountTokenField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "participantId", &p->ParticipantID, sizeof(p->ParticipantID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "keyId", &p->KeyID, sizeof(p->KeyID));
    set_struct(obj, "token", &p->Token, sizeof(p->Token));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryProductGroupField *p)
{
    set_struct(obj, "productId", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
}
static void set_struct(Local<Object>& obj, CThostFtdcProductGroupField *p)
{
    set_struct(obj, "productId", &p->ProductID, sizeof(p->ProductID));
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "productGroupId", &p->ProductGroupID, sizeof(p->ProductGroupID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBulletinField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "bulletinId", &p->BulletinID, sizeof(p->BulletinID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "newsType", &p->NewsType, sizeof(p->NewsType));
    set_struct(obj, "newsUrgency", &p->NewsUrgency, sizeof(p->NewsUrgency));
    set_struct(obj, "sendTime", &p->SendTime, sizeof(p->SendTime));
    set_struct(obj, "abstract", &p->Abstract, sizeof(p->Abstract));
    set_struct(obj, "comeFrom", &p->ComeFrom, sizeof(p->ComeFrom));
    set_struct(obj, "content", &p->Content, sizeof(p->Content));
    set_struct(obj, "uRLLink", &p->URLLink, sizeof(p->URLLink));
    set_struct(obj, "marketId", &p->MarketID, sizeof(p->MarketID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryBulletinField *p)
{
    set_struct(obj, "exchangeId", &p->ExchangeID, sizeof(p->ExchangeID));
    set_struct(obj, "bulletinId", &p->BulletinID, sizeof(p->BulletinID));
    set_struct(obj, "sequenceNo", &p->SequenceNo, sizeof(p->SequenceNo));
    set_struct(obj, "newsType", &p->NewsType, sizeof(p->NewsType));
    set_struct(obj, "newsUrgency", &p->NewsUrgency, sizeof(p->NewsUrgency));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqOpenAccountField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "countryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "zipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "mobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "eMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "moneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "cashExchangeCode", &p->CashExchangeCode, sizeof(p->CashExchangeCode));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqCancelAccountField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "countryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "zipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "mobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "eMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "moneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "cashExchangeCode", &p->CashExchangeCode, sizeof(p->CashExchangeCode));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqChangeAccountField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "countryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "zipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "mobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "eMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "moneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "newBankAccount", &p->NewBankAccount, sizeof(p->NewBankAccount));
    set_struct(obj, "newBankPassWord", &p->NewBankPassWord, sizeof(p->NewBankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqTransferField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "futureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "tradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "futureFetchAmount", &p->FutureFetchAmount, sizeof(p->FutureFetchAmount));
    set_struct(obj, "feePayFlag", &p->FeePayFlag, sizeof(p->FeePayFlag));
    set_struct(obj, "custFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "brokerFee", &p->BrokerFee, sizeof(p->BrokerFee));
    set_struct(obj, "message", &p->Message, sizeof(p->Message));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "transferStatus", &p->TransferStatus, sizeof(p->TransferStatus));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspTransferField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "futureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "tradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "futureFetchAmount", &p->FutureFetchAmount, sizeof(p->FutureFetchAmount));
    set_struct(obj, "feePayFlag", &p->FeePayFlag, sizeof(p->FeePayFlag));
    set_struct(obj, "custFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "brokerFee", &p->BrokerFee, sizeof(p->BrokerFee));
    set_struct(obj, "message", &p->Message, sizeof(p->Message));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "transferStatus", &p->TransferStatus, sizeof(p->TransferStatus));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqRepealField *p)
{
    set_struct(obj, "repealTimeInterval", &p->RepealTimeInterval, sizeof(p->RepealTimeInterval));
    set_struct(obj, "repealedTimes", &p->RepealedTimes, sizeof(p->RepealedTimes));
    set_struct(obj, "bankRepealFlag", &p->BankRepealFlag, sizeof(p->BankRepealFlag));
    set_struct(obj, "brokerRepealFlag", &p->BrokerRepealFlag, sizeof(p->BrokerRepealFlag));
    set_struct(obj, "plateRepealSerial", &p->PlateRepealSerial, sizeof(p->PlateRepealSerial));
    set_struct(obj, "bankRepealSerial", &p->BankRepealSerial, sizeof(p->BankRepealSerial));
    set_struct(obj, "futureRepealSerial", &p->FutureRepealSerial, sizeof(p->FutureRepealSerial));
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "futureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "tradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "futureFetchAmount", &p->FutureFetchAmount, sizeof(p->FutureFetchAmount));
    set_struct(obj, "feePayFlag", &p->FeePayFlag, sizeof(p->FeePayFlag));
    set_struct(obj, "custFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "brokerFee", &p->BrokerFee, sizeof(p->BrokerFee));
    set_struct(obj, "message", &p->Message, sizeof(p->Message));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "transferStatus", &p->TransferStatus, sizeof(p->TransferStatus));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspRepealField *p)
{
    set_struct(obj, "repealTimeInterval", &p->RepealTimeInterval, sizeof(p->RepealTimeInterval));
    set_struct(obj, "repealedTimes", &p->RepealedTimes, sizeof(p->RepealedTimes));
    set_struct(obj, "bankRepealFlag", &p->BankRepealFlag, sizeof(p->BankRepealFlag));
    set_struct(obj, "brokerRepealFlag", &p->BrokerRepealFlag, sizeof(p->BrokerRepealFlag));
    set_struct(obj, "plateRepealSerial", &p->PlateRepealSerial, sizeof(p->PlateRepealSerial));
    set_struct(obj, "bankRepealSerial", &p->BankRepealSerial, sizeof(p->BankRepealSerial));
    set_struct(obj, "futureRepealSerial", &p->FutureRepealSerial, sizeof(p->FutureRepealSerial));
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "futureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "tradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "futureFetchAmount", &p->FutureFetchAmount, sizeof(p->FutureFetchAmount));
    set_struct(obj, "feePayFlag", &p->FeePayFlag, sizeof(p->FeePayFlag));
    set_struct(obj, "custFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "brokerFee", &p->BrokerFee, sizeof(p->BrokerFee));
    set_struct(obj, "message", &p->Message, sizeof(p->Message));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "transferStatus", &p->TransferStatus, sizeof(p->TransferStatus));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqQueryAccountField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "futureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspQueryAccountField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "futureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "bankUseAmount", &p->BankUseAmount, sizeof(p->BankUseAmount));
    set_struct(obj, "bankFetchAmount", &p->BankFetchAmount, sizeof(p->BankFetchAmount));
}
static void set_struct(Local<Object>& obj, CThostFtdcFutureSignIOField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspFutureSignInField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "pinKey", &p->PinKey, sizeof(p->PinKey));
    set_struct(obj, "macKey", &p->MacKey, sizeof(p->MacKey));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqFutureSignOutField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspFutureSignOutField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqQueryTradeResultBySerialField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "reference", &p->Reference, sizeof(p->Reference));
    set_struct(obj, "refrenceIssureType", &p->RefrenceIssureType, sizeof(p->RefrenceIssureType));
    set_struct(obj, "refrenceIssure", &p->RefrenceIssure, sizeof(p->RefrenceIssure));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "tradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspQueryTradeResultBySerialField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "reference", &p->Reference, sizeof(p->Reference));
    set_struct(obj, "refrenceIssureType", &p->RefrenceIssureType, sizeof(p->RefrenceIssureType));
    set_struct(obj, "refrenceIssure", &p->RefrenceIssure, sizeof(p->RefrenceIssure));
    set_struct(obj, "originReturnCode", &p->OriginReturnCode, sizeof(p->OriginReturnCode));
    set_struct(obj, "originDescrInfoForReturnCode", &p->OriginDescrInfoForReturnCode, sizeof(p->OriginDescrInfoForReturnCode));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "tradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqDayEndFileReadyField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "fileBusinessCode", &p->FileBusinessCode, sizeof(p->FileBusinessCode));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
}
static void set_struct(Local<Object>& obj, CThostFtdcReturnResultField *p)
{
    set_struct(obj, "returnCode", &p->ReturnCode, sizeof(p->ReturnCode));
    set_struct(obj, "descrInfoForReturnCode", &p->DescrInfoForReturnCode, sizeof(p->DescrInfoForReturnCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcVerifyFuturePasswordField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcVerifyCustInfoField *p)
{
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
}
static void set_struct(Local<Object>& obj, CThostFtdcVerifyFuturePasswordAndCustInfoField *p)
{
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcDepositResultInformField *p)
{
    set_struct(obj, "depositSeqNo", &p->DepositSeqNo, sizeof(p->DepositSeqNo));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "deposit", &p->Deposit, sizeof(p->Deposit));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "returnCode", &p->ReturnCode, sizeof(p->ReturnCode));
    set_struct(obj, "descrInfoForReturnCode", &p->DescrInfoForReturnCode, sizeof(p->DescrInfoForReturnCode));
}
static void set_struct(Local<Object>& obj, CThostFtdcReqSyncKeyField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "message", &p->Message, sizeof(p->Message));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
}
static void set_struct(Local<Object>& obj, CThostFtdcRspSyncKeyField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "message", &p->Message, sizeof(p->Message));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcNotifyQueryAccountField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "futureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "bankUseAmount", &p->BankUseAmount, sizeof(p->BankUseAmount));
    set_struct(obj, "bankFetchAmount", &p->BankFetchAmount, sizeof(p->BankFetchAmount));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcTransferSerialField *p)
{
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "futureAccType", &p->FutureAccType, sizeof(p->FutureAccType));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "futureSerial", &p->FutureSerial, sizeof(p->FutureSerial));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "tradeAmount", &p->TradeAmount, sizeof(p->TradeAmount));
    set_struct(obj, "custFee", &p->CustFee, sizeof(p->CustFee));
    set_struct(obj, "brokerFee", &p->BrokerFee, sizeof(p->BrokerFee));
    set_struct(obj, "availabilityFlag", &p->AvailabilityFlag, sizeof(p->AvailabilityFlag));
    set_struct(obj, "operatorCode", &p->OperatorCode, sizeof(p->OperatorCode));
    set_struct(obj, "bankNewAccount", &p->BankNewAccount, sizeof(p->BankNewAccount));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryTransferSerialField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcNotifyFutureSignInField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
    set_struct(obj, "pinKey", &p->PinKey, sizeof(p->PinKey));
    set_struct(obj, "macKey", &p->MacKey, sizeof(p->MacKey));
}
static void set_struct(Local<Object>& obj, CThostFtdcNotifyFutureSignOutField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcNotifySyncKeyField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "message", &p->Message, sizeof(p->Message));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "requestId", &p->RequestID, sizeof(p->RequestID));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryAccountregisterField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcAccountregisterField *p)
{
    set_struct(obj, "tradeDay", &p->TradeDay, sizeof(p->TradeDay));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "openOrDestroy", &p->OpenOrDestroy, sizeof(p->OpenOrDestroy));
    set_struct(obj, "regDate", &p->RegDate, sizeof(p->RegDate));
    set_struct(obj, "outDate", &p->OutDate, sizeof(p->OutDate));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
}
static void set_struct(Local<Object>& obj, CThostFtdcOpenAccountField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "countryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "zipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "mobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "eMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "moneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "cashExchangeCode", &p->CashExchangeCode, sizeof(p->CashExchangeCode));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcCancelAccountField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "countryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "zipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "mobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "eMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "moneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "cashExchangeCode", &p->CashExchangeCode, sizeof(p->CashExchangeCode));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "deviceId", &p->DeviceID, sizeof(p->DeviceID));
    set_struct(obj, "bankSecuAccType", &p->BankSecuAccType, sizeof(p->BankSecuAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankSecuAcc", &p->BankSecuAcc, sizeof(p->BankSecuAcc));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "operNo", &p->OperNo, sizeof(p->OperNo));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcChangeAccountField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "countryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "zipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "mobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "eMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "moneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "newBankAccount", &p->NewBankAccount, sizeof(p->NewBankAccount));
    set_struct(obj, "newBankPassWord", &p->NewBankPassWord, sizeof(p->NewBankPassWord));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "bankPwdFlag", &p->BankPwdFlag, sizeof(p->BankPwdFlag));
    set_struct(obj, "secuPwdFlag", &p->SecuPwdFlag, sizeof(p->SecuPwdFlag));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcSecAgentACIDMapField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "brokerSecAgentId", &p->BrokerSecAgentID, sizeof(p->BrokerSecAgentID));
}
static void set_struct(Local<Object>& obj, CThostFtdcQrySecAgentACIDMapField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcUserRightsAssignField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "dRIdentityId", &p->DRIdentityID, sizeof(p->DRIdentityID));
}
static void set_struct(Local<Object>& obj, CThostFtdcBrokerUserRightAssignField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "dRIdentityId", &p->DRIdentityID, sizeof(p->DRIdentityID));
    set_struct(obj, "tradeable", &p->Tradeable, sizeof(p->Tradeable));
}
static void set_struct(Local<Object>& obj, CThostFtdcDRTransferField *p)
{
    set_struct(obj, "origDRIdentityId", &p->OrigDRIdentityID, sizeof(p->OrigDRIdentityID));
    set_struct(obj, "destDRIdentityId", &p->DestDRIdentityID, sizeof(p->DestDRIdentityID));
    set_struct(obj, "origBrokerId", &p->OrigBrokerID, sizeof(p->OrigBrokerID));
    set_struct(obj, "destBrokerId", &p->DestBrokerID, sizeof(p->DestBrokerID));
}
static void set_struct(Local<Object>& obj, CThostFtdcFensUserInfoField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "loginMode", &p->LoginMode, sizeof(p->LoginMode));
}
static void set_struct(Local<Object>& obj, CThostFtdcCurrTransferIdentityField *p)
{
    set_struct(obj, "identityId", &p->IdentityID, sizeof(p->IdentityID));
}
static void set_struct(Local<Object>& obj, CThostFtdcLoginForbiddenUserField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "iPAddress", &p->IPAddress, sizeof(p->IPAddress));
}
static void set_struct(Local<Object>& obj, CThostFtdcQryLoginForbiddenUserField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}
static void set_struct(Local<Object>& obj, CThostFtdcMulticastGroupInfoField *p)
{
    set_struct(obj, "groupIp", &p->GroupIP, sizeof(p->GroupIP));
    set_struct(obj, "groupPort", &p->GroupPort, sizeof(p->GroupPort));
    set_struct(obj, "sourceIp", &p->SourceIP, sizeof(p->SourceIP));
}
static void set_struct(Local<Object>& obj, CThostFtdcTradingAccountReserveField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "reserve", &p->Reserve, sizeof(p->Reserve));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
}
static void set_struct(Local<Object>& obj, CThostFtdcReserveOpenAccountConfirmField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "countryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "zipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "mobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "eMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "moneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "accountId", &p->AccountID, sizeof(p->AccountID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "bankReserveOpenSeq", &p->BankReserveOpenSeq, sizeof(p->BankReserveOpenSeq));
    set_struct(obj, "bookDate", &p->BookDate, sizeof(p->BookDate));
    set_struct(obj, "bookPsw", &p->BookPsw, sizeof(p->BookPsw));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}
static void set_struct(Local<Object>& obj, CThostFtdcReserveOpenAccountField *p)
{
    set_struct(obj, "tradeCode", &p->TradeCode, sizeof(p->TradeCode));
    set_struct(obj, "bankId", &p->BankID, sizeof(p->BankID));
    set_struct(obj, "bankBranchId", &p->BankBranchID, sizeof(p->BankBranchID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerBranchId", &p->BrokerBranchID, sizeof(p->BrokerBranchID));
    set_struct(obj, "tradeDate", &p->TradeDate, sizeof(p->TradeDate));
    set_struct(obj, "tradeTime", &p->TradeTime, sizeof(p->TradeTime));
    set_struct(obj, "bankSerial", &p->BankSerial, sizeof(p->BankSerial));
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "plateSerial", &p->PlateSerial, sizeof(p->PlateSerial));
    set_struct(obj, "lastFragment", &p->LastFragment, sizeof(p->LastFragment));
    set_struct(obj, "sessionId", &p->SessionID, sizeof(p->SessionID));
    set_struct(obj, "customerName", &p->CustomerName, sizeof(p->CustomerName));
    set_struct(obj, "idCardType", &p->IdCardType, sizeof(p->IdCardType));
    set_struct(obj, "identifiedCardNo", &p->IdentifiedCardNo, sizeof(p->IdentifiedCardNo));
    set_struct(obj, "gender", &p->Gender, sizeof(p->Gender));
    set_struct(obj, "countryCode", &p->CountryCode, sizeof(p->CountryCode));
    set_struct(obj, "custType", &p->CustType, sizeof(p->CustType));
    set_struct(obj, "address", &p->Address, sizeof(p->Address));
    set_struct(obj, "zipCode", &p->ZipCode, sizeof(p->ZipCode));
    set_struct(obj, "telephone", &p->Telephone, sizeof(p->Telephone));
    set_struct(obj, "mobilePhone", &p->MobilePhone, sizeof(p->MobilePhone));
    set_struct(obj, "fax", &p->Fax, sizeof(p->Fax));
    set_struct(obj, "eMail", &p->EMail, sizeof(p->EMail));
    set_struct(obj, "moneyAccountStatus", &p->MoneyAccountStatus, sizeof(p->MoneyAccountStatus));
    set_struct(obj, "bankAccount", &p->BankAccount, sizeof(p->BankAccount));
    set_struct(obj, "bankPassWord", &p->BankPassWord, sizeof(p->BankPassWord));
    set_struct(obj, "installId", &p->InstallID, sizeof(p->InstallID));
    set_struct(obj, "verifyCertNoFlag", &p->VerifyCertNoFlag, sizeof(p->VerifyCertNoFlag));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "digest", &p->Digest, sizeof(p->Digest));
    set_struct(obj, "bankAccType", &p->BankAccType, sizeof(p->BankAccType));
    set_struct(obj, "brokerIdByBank", &p->BrokerIDByBank, sizeof(p->BrokerIDByBank));
    set_struct(obj, "tId", &p->TID, sizeof(p->TID));
    set_struct(obj, "reserveOpenAccStas", &p->ReserveOpenAccStas, sizeof(p->ReserveOpenAccStas));
    set_struct(obj, "errorId", &p->ErrorID, sizeof(p->ErrorID));
    set_struct(obj, "errorMsg", &p->ErrorMsg, sizeof(p->ErrorMsg));
}

// TODO 穿透式监管新增结构体

static void set_struct(Local<Object>& obj, CThostFtdcMulticastInstrumentField *p)
{
    set_struct(obj, "topicId", &p->TopicID, sizeof(p->TopicID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
    set_struct(obj, "instrumentNo", &p->InstrumentNo, sizeof(p->InstrumentNo));
    set_struct(obj, "codePrice", &p->CodePrice, sizeof(p->CodePrice));
    set_struct(obj, "volumeMultiple", &p->VolumeMultiple, sizeof(p->VolumeMultiple));
    set_struct(obj, "priceTick", &p->PriceTick, sizeof(p->PriceTick));
}

static void set_struct(Local<Object>& obj, CThostFtdcQryMulticastInstrumentField *p)
{
    set_struct(obj, "topicId", &p->TopicID, sizeof(p->TopicID));
    set_struct(obj, "instrumentId", &p->InstrumentID, sizeof(p->InstrumentID));
}

static void set_struct(Local<Object>& obj, CThostFtdcUserSystemInfoField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "clientSystemInfoLen", &p->ClientSystemInfoLen, sizeof(p->ClientSystemInfoLen));
    set_struct(obj, "clientSystemInfo", &p->ClientSystemInfo, sizeof(p->ClientSystemInfo));
    set_struct(obj, "clientPublicIp", &p->ClientPublicIP, sizeof(p->ClientPublicIP));
    set_struct(obj, "clientIpPort", &p->ClientIPPort, sizeof(p->ClientIPPort));
    set_struct(obj, "clientLoginTime", &p->ClientLoginTime, sizeof(p->ClientLoginTime));
    set_struct(obj, "clientAppId", &p->ClientAppID, sizeof(p->ClientAppID));
}

static void set_struct(Local<Object>& obj, CThostFtdcReqUserAuthMethodField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}

static void set_struct(Local<Object>& obj, CThostFtdcReqGenUserCaptchaField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}

static void set_struct(Local<Object>& obj, CThostFtdcReqGenUserTextField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
}

static void set_struct(Local<Object>& obj, CThostFtdcReqUserLoginWithCaptchaField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "interfaceProductInfo", &p->InterfaceProductInfo, sizeof(p->InterfaceProductInfo));
    set_struct(obj, "protocolInfo", &p->ProtocolInfo, sizeof(p->ProtocolInfo));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "clientIpAddress", &p->ClientIPAddress, sizeof(p->ClientIPAddress));
    set_struct(obj, "loginRemark", &p->LoginRemark, sizeof(p->LoginRemark));
    set_struct(obj, "captcha", &p->Captcha, sizeof(p->Captcha));
    set_struct(obj, "clientIpPort", &p->ClientIPPort, sizeof(p->ClientIPPort));
}

static void set_struct(Local<Object>& obj, CThostFtdcReqUserLoginWithTextField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "interfaceProductInfo", &p->InterfaceProductInfo, sizeof(p->InterfaceProductInfo));
    set_struct(obj, "protocolInfo", &p->ProtocolInfo, sizeof(p->ProtocolInfo));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "clientIpAddress", &p->ClientIPAddress, sizeof(p->ClientIPAddress));
    set_struct(obj, "loginRemark", &p->LoginRemark, sizeof(p->LoginRemark));
    set_struct(obj, "text", &p->Text, sizeof(p->Text));
    set_struct(obj, "clientIpPort", &p->ClientIPPort, sizeof(p->ClientIPPort));
}

static void set_struct(Local<Object>& obj, CThostFtdcReqUserLoginWithOTPField *p)
{
    set_struct(obj, "tradingDay", &p->TradingDay, sizeof(p->TradingDay));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "password", &p->Password, sizeof(p->Password));
    set_struct(obj, "userProductInfo", &p->UserProductInfo, sizeof(p->UserProductInfo));
    set_struct(obj, "interfaceProductInfo", &p->InterfaceProductInfo, sizeof(p->InterfaceProductInfo));
    set_struct(obj, "protocolInfo", &p->ProtocolInfo, sizeof(p->ProtocolInfo));
    set_struct(obj, "macAddress", &p->MacAddress, sizeof(p->MacAddress));
    set_struct(obj, "clientIpAddress", &p->ClientIPAddress, sizeof(p->ClientIPAddress));
    set_struct(obj, "loginRemark", &p->LoginRemark, sizeof(p->LoginRemark));
    set_struct(obj, "oTPPassword", &p->OTPPassword, sizeof(p->OTPPassword));
    set_struct(obj, "clientIpPort", &p->ClientIPPort, sizeof(p->ClientIPPort));
}

static void set_struct(Local<Object>& obj, CThostFtdcQrySecAgentTradeInfoField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerSecAgentId", &p->BrokerSecAgentID, sizeof(p->BrokerSecAgentID));
}

static void set_struct(Local<Object>& obj, CThostFtdcRspUserAuthMethodField *p)
{
    set_struct(obj, "usableAuthMethod", &p->UsableAuthMethod, sizeof(p->UsableAuthMethod));
}

static void set_struct(Local<Object>& obj, CThostFtdcRspGenUserCaptchaField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "userId", &p->UserID, sizeof(p->UserID));
    set_struct(obj, "captchaInfoLen", &p->CaptchaInfoLen, sizeof(p->CaptchaInfoLen));
    set_struct(obj, "captchaInfo", &p->CaptchaInfo, sizeof(p->CaptchaInfo));
}

static void set_struct(Local<Object>& obj, CThostFtdcRspGenUserTextField *p)
{
    set_struct(obj, "userTextSeq", &p->UserTextSeq, sizeof(p->UserTextSeq));
}

static void set_struct(Local<Object>& obj, CThostFtdcSecAgentTradeInfoField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "brokerSecAgentId", &p->BrokerSecAgentID, sizeof(p->BrokerSecAgentID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "longCustomerName", &p->LongCustomerName, sizeof(p->LongCustomerName));
}

static void set_struct(Local<Object>& obj, CThostFtdcSecAgentCheckModeField *p)
{
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "currencyId", &p->CurrencyID, sizeof(p->CurrencyID));
    set_struct(obj, "brokerSecAgentId", &p->BrokerSecAgentID, sizeof(p->BrokerSecAgentID));
    set_struct(obj, "checkSelfAccount", &p->CheckSelfAccount, sizeof(p->CheckSelfAccount));
}

static void set_struct(Local<Object>& obj, CThostFtdcQrySecAgentCheckModeField *p)
{
    set_struct(obj, "brokerId", &p->BrokerID, sizeof(p->BrokerID));
    set_struct(obj, "investorId", &p->InvestorID, sizeof(p->InvestorID));
}

};
#endif



