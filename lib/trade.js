const _ = require('lodash');
const logger = require('./logger').getLogger('trade');
const helper = require('./helper');

class Trade {
  constructor(ctp, { privateTopicMode, publicTopicMode } = { privateTopicMode: 2, publicTopicMode: 2 }) {
    this.ctp = ctp;
    _.isUndefined(privateTopicMode) && (privateTopicMode = 2);
    _.isUndefined(publicTopicMode) && (publicTopicMode = 2);
    this._init({ privateTopicMode, publicTopicMode });
  }

  _init({ privateTopicMode, publicTopicMode }) {
    this.createApi();
    this._regsiterHandlers();
    //THOST_TERT_RESTART:从本交易日开始重传 0
    //THOST_TERT_RESUME:从上次收到的续传    1
    //THOST_TERT_QUICK:只传送登录后私有流的内容 2
    this.subscribeTopic({ privateTopicMode, publicTopicMode });
    this.registerFront();
  }

  _regsiterHandlers() {
    let td = this.ctp.td;
    let allProps = helper.getAllProperties(this);
    allProps.forEach((prop) => {
      if (/^On[a-zA-Z]+$/.test(prop)) {
        td.On(prop, this[prop].bind(this));
      }
    });
  }

  createApi() {
    this.ctp.createTdApi();
  }

  registerFront() {
    this.ctp.registerTdFront();
  }

  subscribeTopic({ privateTopicMode, publicTopicMode }) {
    let td = this.ctp.td;
    _.isNumber(privateTopicMode) && td.SubscribePrivateTopic(privateTopicMode);
    _.isNumber(publicTopicMode) && td.SubscribePublicTopic(publicTopicMode);
  }

  OnFrontConnected() {
    logger.info('OnFrontConnected');
  }

  OnFrontDisconnected(nReason) {
    logger.info('OnFrontDisconnected nReason: %s', nReason);
  }

  OnRspAuthenticate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspAuthenticate : %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  OnRspUserLogin(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspUserLogin : %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  OnRspUserLogout(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspUserLogout : %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 报单通知
  OnRtnOrder(data) {
    logger.info('OnRtnOrder: %j',  data)
  }
  // 成交通知
  OnRtnTrade(data) {
    logger.info('OnRtnTrade:',  data);
  }
  // 报单录入请求响应
  OnRspOrderInsert(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspOrderInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 报单操作请求响应
  OnRspOrderAction(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 预埋单录入请求响应
  OnRspParkedOrderInsert(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspParkedOrderInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 预埋撤单录入请求响应
  OnRspParkedOrderAction(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspParkedOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 删除预埋单响应
  OnRspRemoveParkedOrder(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspParkedOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 删除预埋撤单响应
  OnRspRemoveParkedOrderAction(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspParkedOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 执行宣告录入请求响应
  OnRspExecOrderInsert(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspExecOrderInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 执行宣告操作请求响应
  OnRspExecOrderAction(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspExecOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 询价录入请求响应
  OnRspForQuoteInsert(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspForQuoteInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 报价录入请求响应
  OnRspQuoteInsert(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQuoteInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 报价操作请求响应
  OnRspQuoteAction(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQuoteAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 批量报单操作请求响应
  OnRspBatchOrderAction(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspBatchOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 申请组合录入请求响应
  OnRspCombActionInsert(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspCombActionInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询报单响应
  OnRspQryOrder(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryOrder: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询成交响应
  OnRspQryTrade(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryTrade: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 查询最大报单数量响应
  OnRspQueryMaxOrderVolume(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQueryMaxOrderVolume: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 投资者结算结果确认响应
  OnRspSettlementInfoConfirm(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspSettlementInfoConfirm: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者持仓响应
  OnRspQryInvestorPosition(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryInvestorPosition: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询签约银行响应
  OnRspQryContractBank(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryContractBank: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询资金账户响应
  OnRspQryTradingAccount(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryTradingAccount: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 期货发起期货资金转银行应答
  OnRspFromFutureToBankByFuture(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspFromFutureToBankByFuture: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 期货发起银行资金转期货应答
  OnRspFromBankToFutureByFuture(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspFromBankToFutureByFuture: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 用户口令更新请求响应
  OnRspUserPasswordUpdate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspUserPasswordUpdate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 资金账户口令更新请求响应
  OnRspTradingAccountPasswordUpdate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspTradingAccountPasswordUpdate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者响应
  OnRspQryInvestor(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryInvestor: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询交易编码响应
  OnRspQryTradingCode(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryTradingCode: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询合约保证金率响应
  OnRspQryInstrumentMarginRate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryInstrumentMarginRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询合约手续费率响应 
  OnRspQryInstrumentCommissionRate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryInstrumentCommissionRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询交易所响应
  OnRspQryExchange(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryExchange: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询产品响应
  OnRspQryProduct(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryProduct: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询合约响应
  OnRspQryInstrument(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryInstrument: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询行情响应
  OnRspQryDepthMarketData(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryDepthMarketData: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者结算结果响应
  OnRspQrySettlementInfo(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQrySettlementInfo: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询转帐银行响应
  OnRspQryTransferBank(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryTransferBank: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者持仓明细响应
  OnRspQryInvestorPositionDetail(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryInvestorPositionDetail: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询客户通知响应
  OnRspQryNotice(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryNotice: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询结算信息确认响应
  OnRspQrySettlementInfoConfirm(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQrySettlementInfoConfirm: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者持仓组合明细响应
  OnRspQryInvestorPositionCombineDetail(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryInvestorPositionCombineDetail: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 查询保证金监管系统经纪公司资金账户密钥响应
  OnRspQryCFMMCTradingAccountKey(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryCFMMCTradingAccountKey: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询仓单折抵信息响应
  OnRspQryEWarrantOffset(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryEWarrantOffset: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者品种/跨品种保证金响应
  OnRspQryInvestorProductGroupMargin(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryInvestorProductGroupMargin: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询交易所保证金率响应
  OnRspQryExchangeMarginRate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryExchangeMarginRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询交易所调整保证金率响应
  OnRspQryExchangeMarginRateAdjust(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryExchangeMarginRateAdjust: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询汇率响应
  OnRspQryExchangeRate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryExchangeRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询二级代理操作员银期权限响应
  OnRspQrySecAgentACIDMap(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQrySecAgentACIDMap: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询产品报价汇率响应
  OnRspQryProductExchRate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryProductExchRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询产品组响应
  OnRspQryProductGroup(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryProductGroup: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询做市商合约手续费率响应
  OnRspQryMMInstrumentCommissionRate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryMMInstrumentCommissionRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询做市商期权合约手续费响应
  OnRspQryMMOptionInstrCommRate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryMMOptionInstrCommRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询报单手续费响应
  OnRspQryInstrumentOrderCommRate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryInstrumentOrderCommRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询期权交易成本响应
  OnRspQryOptionInstrTradeCost(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryOptionInstrTradeCost: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询期权合约手续费响应
  OnRspQryOptionInstrCommRate(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryOptionInstrCommRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询执行宣告响应
  OnRspQryExecOrder(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryExecOrder: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询询价响应
  OnRspQryForQuote(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryForQuote: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询报价响应
  OnRspQryQuote(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryQuote: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询组合合约安全系数响应
  OnRspQryCombInstrumentGuard(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryCombInstrumentGuard: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询申请组合响应
  OnRspQryCombAction(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryCombAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询转帐流水响应
  OnRspQryTransferSerial(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryTransferSerial: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询银期签约关系响应
  OnRspQryAccountregister(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryAccountregister: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 错误应答
  OnRspError(rsp, nRequestID, bIsLast) {
    logger.info('OnRspError: %j, %s, %s', rsp, nRequestID, bIsLast);
  }
  // 报单录入错误回报
  OnErrRtnOrderInsert(data, rsp) {
    logger.info('OnErrRtnOrderInsert: %j, %j', data, rsp);
  }
  // 报单操作错误回报
  OnErrRtnOrderAction(data, rsp) {
    logger.info('OnErrRtnOrderAction: %j, %j', data, rsp);
  }
  // 合约交易状态通知
  OnRtnInstrumentStatus(data) {
    logger.info('OnRtnInstrumentStatus: %j', data);
  }
  // 交易所公告通知
  OnRtnBulletin(data) {
    logger.info('OnRtnBulletin: %j', data);
  }
  // 交易通知
  OnRtnTradingNotice(data) {
    logger.info('OnRtnTradingNotice: %j', data);
  }
  // 提示条件单校验错误
  OnRtnErrorConditionalOrder(data) {
    logger.info('OnRtnErrorConditionalOrder: %j', data);
  }
  // 执行宣告通知
  OnRtnExecOrder(data) {
    logger.info('OnRtnExecOrder: %j', data);
  }
  // 执行宣告录入错误回报
  OnErrRtnExecOrderInsert(data, rsp) {
    logger.info('OnErrRtnExecOrderInsert: %j, %j', data, rsp);
  }
  // 执行宣告操作错误回报
  OnErrRtnExecOrderAction(data, rsp) {
    logger.info('OnErrRtnExecOrderAction: %j, %j', data, rsp);
  }
  // 询价录入错误回报
  OnErrRtnForQuoteInsert(data, rsp) {
    logger.info('OnErrRtnForQuoteInsert: %j, %j', data, rsp);
  }
  // 报价通知
  OnRtnQuote(data) {
    logger.info('OnRtnQuote: %j', data);
  }
  // 报价录入错误回报
  OnErrRtnQuoteInsert(data, rsp) {
    logger.info('OnErrRtnQuoteInsert: %j, %j', data, rsp);
  }
  // 报价操作错误回报
  OnErrRtnQuoteAction(data, rsp) {
    logger.info('OnErrRtnQuoteAction: %j, %j', data, rsp);
  }
  // 询价通知
  OnRtnForQuoteRsp(data) {
    logger.info('OnRtnForQuoteRsp: %j', data);
  }
  // 保证金监控中心用户令牌
  OnRtnCFMMCTradingAccountToken(data) {
    logger.info('OnRtnCFMMCTradingAccountToken: %j', data);
  }
  // 批量报单操作错误回报
  OnErrRtnBatchOrderAction(data, rsp) {
    logger.info('OnErrRtnBatchOrderAction: %j, %j', data, rsp);
  }
  // 申请组合通知
  OnRtnCombAction(data) {
    logger.info('OnRtnCombAction: %j', data);
  }
  // 申请组合录入错误回报
  OnErrRtnCombActionInsert(data, rsp) {
    logger.info('OnErrRtnCombActionInsert: %j, %j', data, rsp);
  }
  // 请求查询预埋撤单响应
  OnRspQryParkedOrder(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryParkedOrder: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询交易通知响应
  OnRspQryTradingNotice(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryTradingNotice: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询经纪公司交易参数响应
  OnRspQryBrokerTradingParams(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryBrokerTradingParams: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询经纪公司交易算法响应
  OnRspQryBrokerTradingAlgos(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQryBrokerTradingAlgos: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询监控中心用户令牌响应
  OnRspQueryCFMMCTradingAccountToken(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQueryCFMMCTradingAccountToken: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 银行发起银行资金转期货通知
  OnRtnFromBankToFutureByBank(data) {
    logger.info('OnRtnFromBankToFutureByBank: %j', data);
  }
  // 银行发起期货资金转银行通知
  OnRtnFromFutureToBankByBank(data) {
    logger.info('OnRtnFromFutureToBankByBank: %j', data);
  }
  // 银行发起冲正银行转期货通知
  OnRtnRepealFromBankToFutureByBank(data) {
    logger.info('OnRtnRepealFromBankToFutureByBank: %j', data);
  }
  // 银行发起冲正期货转银行通知
  OnRtnRepealFromFutureToBankByBank(data) {
    logger.info('OnRtnRepealFromFutureToBankByBank: %j', data);
  }
  // 期货发起银行资金转期货通知
  OnRtnFromBankToFutureByFuture(data) {
    logger.info('OnRtnFromBankToFutureByFuture: %j', data);
  }
  // 期货发起期货资金转银行通知
  OnRtnFromFutureToBankByFuture(data) {
    logger.info('OnRtnFromFutureToBankByFuture: %j', data);
  }
  // 系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
  OnRtnRepealFromBankToFutureByFutureManual(data) {
    logger.info('OnRtnRepealFromBankToFutureByFutureManual: %j', data);
  }
  // 系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
  OnRtnRepealFromFutureToBankByFutureManual(data) {
    logger.info('OnRtnRepealFromFutureToBankByFutureManual: %j', data);
  }
  // 期货发起查询银行余额通知
  OnRtnQueryBankBalanceByFuture(data) {
    logger.info('OnRtnQueryBankBalanceByFuture: %j', data);
  }
  // 期货发起银行资金转期货错误回报
  OnErrRtnBankToFutureByFuture(data, rsp) {
    logger.info('OnErrRtnBankToFutureByFuture: %j, %j', data, rsp);
  }
  // 期货发起期货资金转银行错误回报
  OnErrRtnFutureToBankByFuture(data, rsp) {
    logger.info('OnErrRtnFutureToBankByFuture: %j, %',data, rsp);
  }
  // 系统运行时期货端手工发起冲正银行转期货错误回报
  OnErrRtnRepealBankToFutureByFutureManual(data, rsp) {
    logger.info('OnErrRtnRepealBankToFutureByFutureManual: %j, %j', data, rsp);
  }
  // 系统运行时期货端手工发起冲正期货转银行错误回报
  OnErrRtnRepealFutureToBankByFutureManual(data, rsp) {
    logger.info('OnErrRtnRepealFutureToBankByFutureManual: %j, %j', data, rsp);
  }
  // 期货发起查询银行余额错误回报
  OnErrRtnQueryBankBalanceByFuture(data, rsp) {
    logger.info('OnErrRtnQueryBankBalanceByFuture: %j, %j', data, rsp);
  }
  // 期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
  OnRtnRepealFromBankToFutureByFuture(data) {
    logger.info('OnRtnRepealFromBankToFutureByFuture: %j', data);
  }
  // 期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
  OnRtnRepealFromFutureToBankByFuture(data) {
    logger.info('OnRtnRepealFromFutureToBankByFuture: %j', data);
  }
  // 期货发起查询银行余额应答 
  OnRspQueryBankAccountMoneyByFuture(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQueryBankAccountMoneyByFuture: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 银行发起银期开户通知
  OnRtnOpenAccountByBank(data) {
    logger.info('OnRtnOpenAccountByBank: %j', data);
  }
  // 银行发起银期销户通知
  OnRtnCancelAccountByBank(data) {
    logger.info('OnRtnCancelAccountByBank: %j', data);
  }
  // 银行发起变更银行账号通知
  OnRtnChangeAccountByBank(data) {
    logger.info('OnRtnChangeAccountByBank: %j', data);
  }

  // 查询用户当前支持的认证模式的回复 
  OnRspUserAuthMethod(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspUserAuthMethod: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  // 获取图形验证码请求的回复 
  OnRspGenUserCaptcha(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspGenUserCaptcha: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  // 获取短信验证码请求的回复 
  OnRspGenUserText(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspGenUserText: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  // 请求查询二级代理商信息响应 
  OnRspQrySecAgentTradeInfo(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQrySecAgentTradeInfo: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  // 请求查询资金账户响应 
  OnRspQrySecAgentTradingAccount(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQrySecAgentTradingAccount: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  // 请求查询二级代理商资金校验模式响应 
  OnRspQrySecAgentCheckMode(data, rsp, nRequestID, bIsLast) {
    logger.info('OnRspQrySecAgentCheckMode: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

}

module.exports = Trade;