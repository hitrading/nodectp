//*******************************************************************************
//  *Copyright(C),2018, invesmart.cn
//  *FileName:  WrapTd.h
//  *Author: 	dreamyzhang
//  *Version:   v2.1
//  *Date:  	2018-05-30
//  *Description:  invoked by js
//*******************************************************************************

#ifndef __WRAPTD_H__
#define __WRAPTD_H__

//#include <sys/socket.h>
//#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
//#include <pthread.h>
#include <map>
#include <node.h>
// #include <node_object_wrap.h>
#include <nan.h>

#include <set>

#include "comm.h"

#include "ThostFtdcTraderSpiI.h"
#include "ctp_node.h"


using namespace std;

namespace td
{
    class WrapTd : public CThostFtdcTraderSpiI, public Nan::ObjectWrap
    {
        public:
            WrapTd();
            virtual ~WrapTd();

            static void On(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static v8::Local<v8::Object> NewInstance(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void Init();

            ///////////////////////////////主动请求函数start//////////////////////////////////////////////////
            //参数传递以对象的形式
            static void GetApiVersion(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void Init(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void Release(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void Dispose(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void CreateFtdcTraderApi(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void GetTradingDay(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void RegisterFront(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void RegisterNameServer(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void RegisterFensUserInfo(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void SubscribePrivateTopic(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void SubscribePublicTopic(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqAuthenticate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqUserLogin(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqUserLogout(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqUserPasswordUpdate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqTradingAccountPasswordUpdate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqOrderAction(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqOrderInsert(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqSettlementInfoConfirm(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryProduct(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryInstrument(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryInvestorPositionDetail(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryOrder(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryTrade(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryInvestorPosition(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryTradingAccount(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqParkedOrderInsert(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqParkedOrderAction(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQueryMaxOrderVolume(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqRemoveParkedOrder(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqRemoveParkedOrderAction(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqExecOrderInsert(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqExecOrderAction(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqForQuoteInsert(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQuoteInsert(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQuoteAction(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqBatchOrderAction(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqCombActionInsert(const Nan::FunctionCallbackInfo<v8::Value>& args);

            static void ReqQryInvestor(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryTradingCode(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryInstrumentMarginRate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryInstrumentCommissionRate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryExchange(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryDepthMarketData(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQrySettlementInfo(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryTransferBank(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryNotice(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQrySettlementInfoConfirm(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryInvestorPositionCombineDetail(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryCFMMCTradingAccountKey(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryEWarrantOffset(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryInvestorProductGroupMargin(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryExchangeMarginRate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryExchangeMarginRateAdjust(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryExchangeRate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQrySecAgentACIDMap(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryProductExchRate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryProductGroup(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryMMInstrumentCommissionRate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryMMOptionInstrCommRate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryInstrumentOrderCommRate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryOptionInstrTradeCost(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryOptionInstrCommRate(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryExecOrder(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryForQuote(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryQuote(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryCombInstrumentGuard(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryCombAction(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryTransferSerial(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryAccountregister(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryContractBank(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryParkedOrder(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryParkedOrderAction(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryTradingNotice(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryBrokerTradingParams(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQryBrokerTradingAlgos(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQueryCFMMCTradingAccountToken(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqFromBankToFutureByFuture(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqFromFutureToBankByFuture(const Nan::FunctionCallbackInfo<v8::Value>& args);
            static void ReqQueryBankAccountMoneyByFuture(const Nan::FunctionCallbackInfo<v8::Value>& args);

            // TODO 穿透式监控新增主动请求接口

            // 注册用户终端信息，用于中继服务器多连接模式
            // 需要在终端认证成功后，用户登录前调用该接口
            static void RegisterUserSystemInfo(const Nan::FunctionCallbackInfo<v8::Value>& args);
            // 上报用户终端信息，用于中继服务器操作员登录模式
            // 操作员登录后，可以多次调用该接口上报客户信息
            static void SubmitUserSystemInfo(const Nan::FunctionCallbackInfo<v8::Value>& args);
            // 查询用户当前支持的认证模式
            static void ReqUserAuthMethod(const Nan::FunctionCallbackInfo<v8::Value>& args);
            // 用户发出获取图形验证码请求
            static void ReqGenUserCaptcha(const Nan::FunctionCallbackInfo<v8::Value>& args);
            // 用户发出获取短信验证码请求
            static void ReqGenUserText(const Nan::FunctionCallbackInfo<v8::Value>& args);
            // 用户发出带有图片验证码的登陆请求
            static void ReqUserLoginWithCaptcha(const Nan::FunctionCallbackInfo<v8::Value>& args);
            // 用户发出带有短信验证码的登陆请求
            static void ReqUserLoginWithText(const Nan::FunctionCallbackInfo<v8::Value>& args);
            // 用户发出带有动态口令的登陆请求
            static void ReqUserLoginWithOTP(const Nan::FunctionCallbackInfo<v8::Value>& args);
            // 请求查询二级代理商信息
            static void ReqQrySecAgentTradeInfo(const Nan::FunctionCallbackInfo<v8::Value>& args);
            // 请求查询二级代理商资金校验模式
            static void ReqQrySecAgentCheckMode(const Nan::FunctionCallbackInfo<v8::Value>& args);
            // 请求查询资金账户
            static void ReqQrySecAgentTradingAccount(const Nan::FunctionCallbackInfo<v8::Value>& args);
            /////////////////////////////主动请求函数end/////////////////////////////////////////////////////



            /////////////////////////ctp线程回调过来的///////////////////////////////////////////////////
            ///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
            virtual void MainOnFrontConnected();

            ///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
            ///@param nReason 错误原因
            ///        0x1001 网络读失败
            ///        0x1002 网络写失败
            ///        0x2001 接收心跳超时
            ///        0x2002 发送心跳失败
            ///        0x2003 收到错误报文
            virtual void MainOnFrontDisconnected(int nReason);

            ///心跳超时警告。当长时间未收到报文时，该方法被调用。
            ///@param nTimeLapse 距离上次接收报文的时间
            virtual void MainOnHeartBeatWarning(int nTimeLapse);

            ///客户端认证响应
            virtual void MainOnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///登录请求响应
            virtual void MainOnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///登出请求响应
            virtual void MainOnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///用户口令更新请求响应
            virtual void MainOnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///资金账户口令更新请求响应
            virtual void MainOnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///报单录入请求响应
            virtual void MainOnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///预埋单录入请求响应
            virtual void MainOnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///预埋撤单录入请求响应
            virtual void MainOnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///报单操作请求响应
            virtual void MainOnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///查询最大报单数量响应
            virtual void MainOnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///投资者结算结果确认响应
            virtual void MainOnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///删除预埋单响应
            virtual void MainOnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///删除预埋撤单响应
            virtual void MainOnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///执行宣告录入请求响应
            virtual void MainOnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///执行宣告操作请求响应
            virtual void MainOnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///询价录入请求响应
            virtual void MainOnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///报价录入请求响应
            virtual void MainOnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///报价操作请求响应
            virtual void MainOnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///批量报单操作请求响应
            virtual void MainOnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            ///请求查询产品组
            virtual void MainOnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            ///请求查询做市商合约手续费率响应
            virtual void MainOnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            ///请求查询做市商期权合约手续费响应
            virtual void MainOnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            ///请求查询报单手续费响应
            virtual void MainOnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
            ///交易所公告通知
            virtual void MainOnRtnBulletin(CThostFtdcBulletinField *pBulletin);
            ///批量报单操作错误回报
            virtual void MainOnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo);
            ///申请组合录入请求响应
            virtual void MainOnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询报单响应
            virtual void MainOnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询成交响应
            virtual void MainOnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询投资者持仓响应
            virtual void MainOnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询资金账户响应
            virtual void MainOnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询投资者响应
            virtual void MainOnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询交易编码响应
            virtual void MainOnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询合约保证金率响应
            virtual void MainOnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询合约手续费率响应
            virtual void MainOnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询交易所响应
            virtual void MainOnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询产品响应
            virtual void MainOnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询合约响应
            virtual void MainOnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询行情响应
            virtual void MainOnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询投资者结算结果响应
            virtual void MainOnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询转帐银行响应
            virtual void MainOnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询投资者持仓明细响应
            virtual void MainOnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询客户通知响应
            virtual void MainOnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询结算信息确认响应
            virtual void MainOnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询投资者持仓明细响应
            virtual void MainOnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///查询保证金监管系统经纪公司资金账户密钥响应
            virtual void MainOnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询仓单折抵信息响应
            virtual void MainOnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询投资者品种/跨品种保证金响应
            virtual void MainOnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询交易所保证金率响应
            virtual void MainOnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询交易所调整保证金率响应
            virtual void MainOnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询汇率响应
            virtual void MainOnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询二级代理操作员银期权限响应
            virtual void MainOnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询产品报价汇率
            virtual void MainOnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询期权交易成本响应
            virtual void MainOnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询期权合约手续费响应
            virtual void MainOnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询执行宣告响应
            virtual void MainOnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询询价响应
            virtual void MainOnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询报价响应
            virtual void MainOnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询组合合约安全系数响应
            virtual void MainOnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询申请组合响应
            virtual void MainOnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询转帐流水响应
            virtual void MainOnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询银期签约关系响应
            virtual void MainOnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///错误应答
            virtual void MainOnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///报单通知
            virtual void MainOnRtnOrder(CThostFtdcOrderField *pOrder);

            ///成交通知
            virtual void MainOnRtnTrade(CThostFtdcTradeField *pTrade);

            ///报单录入错误回报
            virtual void MainOnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);

            ///报单操作错误回报
            virtual void MainOnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

            ///合约交易状态通知
            virtual void MainOnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);

            ///交易通知
            virtual void MainOnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo);

            ///提示条件单校验错误
            virtual void MainOnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder);

            ///执行宣告通知
            virtual void MainOnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder);

            ///执行宣告录入错误回报
            virtual void MainOnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo);

            ///执行宣告操作错误回报
            virtual void MainOnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo);

            ///询价录入错误回报
            virtual void MainOnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo);

            ///报价通知
            virtual void MainOnRtnQuote(CThostFtdcQuoteField *pQuote);

            ///报价录入错误回报
            virtual void MainOnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo);

            ///报价操作错误回报
            virtual void MainOnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo);

            ///询价通知
            virtual void MainOnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

            ///保证金监控中心用户令牌
            virtual void MainOnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken);

            ///申请组合通知
            virtual void MainOnRtnCombAction(CThostFtdcCombActionField *pCombAction);

            ///申请组合录入错误回报
            virtual void MainOnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo);

            ///请求查询签约银行响应
            virtual void MainOnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询预埋单响应
            virtual void MainOnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询预埋撤单响应
            virtual void MainOnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询交易通知响应
            virtual void MainOnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询经纪公司交易参数响应
            virtual void MainOnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询经纪公司交易算法响应
            virtual void MainOnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询监控中心用户令牌
            virtual void MainOnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///银行发起银行资金转期货通知
            virtual void MainOnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer);

            ///银行发起期货资金转银行通知
            virtual void MainOnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer);

            ///银行发起冲正银行转期货通知
            virtual void MainOnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal);

            ///银行发起冲正期货转银行通知
            virtual void MainOnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal);

            ///期货发起银行资金转期货通知
            virtual void MainOnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer);

            ///期货发起期货资金转银行通知
            virtual void MainOnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer);

            ///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
            virtual void MainOnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal);

            ///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
            virtual void MainOnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal);

            ///期货发起查询银行余额通知
            virtual void MainOnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount);

            ///期货发起银行资金转期货错误回报
            virtual void MainOnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);

            ///期货发起期货资金转银行错误回报
            virtual void MainOnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo);

            ///系统运行时期货端手工发起冲正银行转期货错误回报
            virtual void MainOnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);

            ///系统运行时期货端手工发起冲正期货转银行错误回报
            virtual void MainOnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo);

            ///期货发起查询银行余额错误回报
            virtual void MainOnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo);

            ///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
            virtual void MainOnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal);

            ///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
            virtual void MainOnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal);

            ///期货发起银行资金转期货应答
            virtual void MainOnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///期货发起期货资金转银行应答
            virtual void MainOnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///期货发起查询银行余额应答
            virtual void MainOnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///银行发起银期开户通知
            virtual void MainOnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount);

            ///银行发起银期销户通知
            virtual void MainOnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount);

            ///银行发起变更银行账号通知
            virtual void MainOnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount);

            // TODO 穿透式监控新增响应接口

            /// 查询用户当前支持的认证模式的回复
            virtual void MainOnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            /// 获取图形验证码请求的回复
            virtual void MainOnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            /// 获取短信验证码请求的回复
            virtual void MainOnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            /// 请求查询二级代理商信息响应
            virtual void MainOnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询资金账户响应
            virtual void MainOnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            ///请求查询二级代理商资金校验模式响应
            virtual void MainOnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

            bool CanCallback(string event)
            {
                if(callback_map.find(event) != callback_map.end()) return true;
                return false;
            }
            void SetCallback(string event, v8::Local<v8::Function>& cb, v8::Isolate* isolate)
            {
                callback_map[event].Reset(cb, isolate);
            }

        private:
            typedef std::map<string, Nan::Persistent<v8::Function> > __callback_type;
            typedef std::map<string, Nan::Persistent<v8::Function> >::iterator  __callback_iter_type;

            __callback_type callback_map; //回调js name映射回调处理函数

            static set<string>         m_event;                //可以注册的回调事件
            static Nan::Persistent<v8::Function> constructor;           //主动请求函数映射js name

            static void New(const Nan::FunctionCallbackInfo<v8::Value>& args);
            v8::Local<v8::Value> PkgRspInfo(CThostFtdcRspInfoField *pRspInfo)
            {
                v8::Isolate* isolate = v8::Isolate::GetCurrent();
                if (pRspInfo != NULL)
                {
                    //printf("-----%d %s--------\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
                    v8::Local<v8::Object> jsonInfo = v8::Object::New(isolate);
                    jsonInfo->Set(v8::String::NewFromUtf8(isolate, "errorId"), v8::Int32::New(isolate, pRspInfo->ErrorID));
                    jsonInfo->Set(v8::String::NewFromUtf8(isolate, "errorMsg"), v8::String::NewFromUtf8(isolate, CSFunction::GBK2UTF8(pRspInfo->ErrorMsg).c_str()));
                    return jsonInfo;
                }
                else
                {
                    return  v8::Local<v8::Value>::New(isolate, v8::Undefined(isolate));
                }
            }

    };
}


#endif



