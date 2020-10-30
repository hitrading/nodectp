const helper = require('./helper');

class Trade {
  constructor(ctp, { privateTopicMode = 2, publicTopicMode = 2 }, logger) {
    this.ctp = ctp;
    this.logger = logger;
    this._regsiterHandlers();
    //THOST_TERT_RESTART:从本交易日开始重传 0
    //THOST_TERT_RESUME:从上次收到的续传    1
    //THOST_TERT_QUICK:只传送登录后私有流的内容 2
    ctp.td.subscribePrivateTopic(privateTopicMode);
    ctp.td.subscribePublicTopic(publicTopicMode);
  }

  _regsiterHandlers() {
    const td = this.ctp.td;
    const allProps = helper.getAllProperties(this);
    allProps.forEach((prop) => {
      if (/^on[a-zA-Z]+$/.test(prop)) {
        td.on(prop.slice(2), this[prop].bind(this));
      }
    });
  }

  onFrontConnected() {
    this.logger && this.logger.info('OnFrontConnected');
  }

  onFrontDisconnected(nReason) {
    this.logger && this.logger.info('OnFrontDisconnected nReason: %s', nReason);
  }

  onRspAuthenticate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspAuthenticate : %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspUserLogin(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspUserLogin : %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  onRspUserLogout(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspUserLogout : %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 报单通知
  onRtnOrder(data) {
    this.logger && this.logger.info('OnRtnOrder: %j',  data)
  }
  // 成交通知
  onRtnTrade(data) {
    this.logger && this.logger.info('OnRtnTrade:',  data);
  }
  // 报单录入请求响应
  onRspOrderInsert(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspOrderInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 报单操作请求响应
  onRspOrderAction(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 预埋单录入请求响应
  onRspParkedOrderInsert(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspParkedOrderInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 预埋撤单录入请求响应
  onRspParkedOrderAction(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspParkedOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 删除预埋单响应
  onRspRemoveParkedOrder(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspParkedOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 删除预埋撤单响应
  onRspRemoveParkedOrderAction(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspParkedOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 执行宣告录入请求响应
  onRspExecOrderInsert(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspExecOrderInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 执行宣告操作请求响应
  onRspExecOrderAction(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspExecOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 询价录入请求响应
  onRspForQuoteInsert(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspForQuoteInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 报价录入请求响应
  onRspQuoteInsert(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQuoteInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 报价操作请求响应
  onRspQuoteAction(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQuoteAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 批量报单操作请求响应
  onRspBatchOrderAction(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspBatchOrderAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 申请组合录入请求响应
  onRspCombActionInsert(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspCombActionInsert: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询报单响应
  onRspQryOrder(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryOrder: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询成交响应
  onRspQryTrade(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryTrade: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 查询最大报单数量响应
  onRspQueryMaxOrderVolume(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQueryMaxOrderVolume: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 投资者结算结果确认响应
  onRspSettlementInfoConfirm(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspSettlementInfoConfirm: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者持仓响应
  onRspQryInvestorPosition(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryInvestorPosition: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询签约银行响应
  onRspQryContractBank(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryContractBank: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询资金账户响应
  onRspQryTradingAccount(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryTradingAccount: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 期货发起期货资金转银行应答
  onRspFromFutureToBankByFuture(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspFromFutureToBankByFuture: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 期货发起银行资金转期货应答
  onRspFromBankToFutureByFuture(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspFromBankToFutureByFuture: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 用户口令更新请求响应
  onRspUserPasswordUpdate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspUserPasswordUpdate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 资金账户口令更新请求响应
  onRspTradingAccountPasswordUpdate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspTradingAccountPasswordUpdate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者响应
  onRspQryInvestor(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryInvestor: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询交易编码响应
  onRspQryTradingCode(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryTradingCode: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询合约保证金率响应
  onRspQryInstrumentMarginRate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryInstrumentMarginRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询合约手续费率响应
  onRspQryInstrumentCommissionRate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryInstrumentCommissionRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询交易所响应
  onRspQryExchange(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryExchange: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询产品响应
  onRspQryProduct(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryProduct: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询合约响应
  onRspQryInstrument(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryInstrument: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询行情响应
  onRspQryDepthMarketData(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryDepthMarketData: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者结算结果响应
  onRspQrySettlementInfo(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQrySettlementInfo: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询转帐银行响应
  onRspQryTransferBank(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryTransferBank: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者持仓明细响应
  onRspQryInvestorPositionDetail(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryInvestorPositionDetail: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询客户通知响应
  onRspQryNotice(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryNotice: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询结算信息确认响应
  onRspQrySettlementInfoConfirm(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQrySettlementInfoConfirm: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者持仓组合明细响应
  onRspQryInvestorPositionCombineDetail(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryInvestorPositionCombineDetail: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 查询保证金监管系统经纪公司资金账户密钥响应
  onRspQryCFMMCTradingAccountKey(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryCFMMCTradingAccountKey: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询仓单折抵信息响应
  onRspQryEWarrantOffset(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryEWarrantOffset: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询投资者品种/跨品种保证金响应
  onRspQryInvestorProductGroupMargin(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryInvestorProductGroupMargin: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询交易所保证金率响应
  onRspQryExchangeMarginRate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryExchangeMarginRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询交易所调整保证金率响应
  onRspQryExchangeMarginRateAdjust(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryExchangeMarginRateAdjust: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询汇率响应
  onRspQryExchangeRate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryExchangeRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询二级代理操作员银期权限响应
  onRspQrySecAgentACIDMap(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQrySecAgentACIDMap: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询产品报价汇率响应
  onRspQryProductExchRate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryProductExchRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询产品组响应
  onRspQryProductGroup(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryProductGroup: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询做市商合约手续费率响应
  onRspQryMMInstrumentCommissionRate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryMMInstrumentCommissionRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询做市商期权合约手续费响应
  onRspQryMMOptionInstrCommRate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryMMOptionInstrCommRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询报单手续费响应
  onRspQryInstrumentOrderCommRate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryInstrumentOrderCommRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询期权交易成本响应
  onRspQryOptionInstrTradeCost(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryOptionInstrTradeCost: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询期权合约手续费响应
  onRspQryOptionInstrCommRate(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryOptionInstrCommRate: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询执行宣告响应
  onRspQryExecOrder(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryExecOrder: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询询价响应
  onRspQryForQuote(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryForQuote: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询报价响应
  onRspQryQuote(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryQuote: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询组合合约安全系数响应
  onRspQryCombInstrumentGuard(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryCombInstrumentGuard: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询申请组合响应
  onRspQryCombAction(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryCombAction: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询转帐流水响应
  onRspQryTransferSerial(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryTransferSerial: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询银期签约关系响应
  onRspQryAccountregister(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryAccountregister: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 错误应答
  onRspError(rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspError: %j, %s, %s', rsp, nRequestID, bIsLast);
  }
  // 报单录入错误回报
  onErrRtnOrderInsert(data, rsp) {
    this.logger && this.logger.info('OnErrRtnOrderInsert: %j, %j', data, rsp);
  }
  // 报单操作错误回报
  onErrRtnOrderAction(data, rsp) {
    this.logger && this.logger.info('OnErrRtnOrderAction: %j, %j', data, rsp);
  }
  // 合约交易状态通知
  onRtnInstrumentStatus(data) {
    this.logger && this.logger.info('OnRtnInstrumentStatus: %j', data);
  }
  // 交易所公告通知
  onRtnBulletin(data) {
    this.logger && this.logger.info('OnRtnBulletin: %j', data);
  }
  // 交易通知
  onRtnTradingNotice(data) {
    this.logger && this.logger.info('OnRtnTradingNotice: %j', data);
  }
  // 提示条件单校验错误
  onRtnErrorConditionalOrder(data) {
    this.logger && this.logger.info('OnRtnErrorConditionalOrder: %j', data);
  }
  // 执行宣告通知
  onRtnExecOrder(data) {
    this.logger && this.logger.info('OnRtnExecOrder: %j', data);
  }
  // 执行宣告录入错误回报
  onErrRtnExecOrderInsert(data, rsp) {
    this.logger && this.logger.info('OnErrRtnExecOrderInsert: %j, %j', data, rsp);
  }
  // 执行宣告操作错误回报
  onErrRtnExecOrderAction(data, rsp) {
    this.logger && this.logger.info('OnErrRtnExecOrderAction: %j, %j', data, rsp);
  }
  // 询价录入错误回报
  onErrRtnForQuoteInsert(data, rsp) {
    this.logger && this.logger.info('OnErrRtnForQuoteInsert: %j, %j', data, rsp);
  }
  // 报价通知
  onRtnQuote(data) {
    this.logger && this.logger.info('OnRtnQuote: %j', data);
  }
  // 报价录入错误回报
  onErrRtnQuoteInsert(data, rsp) {
    this.logger && this.logger.info('OnErrRtnQuoteInsert: %j, %j', data, rsp);
  }
  // 报价操作错误回报
  onErrRtnQuoteAction(data, rsp) {
    this.logger && this.logger.info('OnErrRtnQuoteAction: %j, %j', data, rsp);
  }
  // 询价通知
  onRtnForQuoteRsp(data) {
    this.logger && this.logger.info('OnRtnForQuoteRsp: %j', data);
  }
  // 保证金监控中心用户令牌
  onRtnCFMMCTradingAccountToken(data) {
    this.logger && this.logger.info('OnRtnCFMMCTradingAccountToken: %j', data);
  }
  // 批量报单操作错误回报
  onErrRtnBatchOrderAction(data, rsp) {
    this.logger && this.logger.info('OnErrRtnBatchOrderAction: %j, %j', data, rsp);
  }
  // 申请组合通知
  onRtnCombAction(data) {
    this.logger && this.logger.info('OnRtnCombAction: %j', data);
  }
  // 申请组合录入错误回报
  onErrRtnCombActionInsert(data, rsp) {
    this.logger && this.logger.info('OnErrRtnCombActionInsert: %j, %j', data, rsp);
  }
  // 请求查询预埋撤单响应
  onRspQryParkedOrder(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryParkedOrder: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询交易通知响应
  onRspQryTradingNotice(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryTradingNotice: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询经纪公司交易参数响应
  onRspQryBrokerTradingParams(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryBrokerTradingParams: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询经纪公司交易算法响应
  onRspQryBrokerTradingAlgos(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQryBrokerTradingAlgos: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 请求查询监控中心用户令牌响应
  onRspQueryCFMMCTradingAccountToken(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQueryCFMMCTradingAccountToken: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 银行发起银行资金转期货通知
  onRtnFromBankToFutureByBank(data) {
    this.logger && this.logger.info('OnRtnFromBankToFutureByBank: %j', data);
  }
  // 银行发起期货资金转银行通知
  onRtnFromFutureToBankByBank(data) {
    this.logger && this.logger.info('OnRtnFromFutureToBankByBank: %j', data);
  }
  // 银行发起冲正银行转期货通知
  onRtnRepealFromBankToFutureByBank(data) {
    this.logger && this.logger.info('OnRtnRepealFromBankToFutureByBank: %j', data);
  }
  // 银行发起冲正期货转银行通知
  onRtnRepealFromFutureToBankByBank(data) {
    this.logger && this.logger.info('OnRtnRepealFromFutureToBankByBank: %j', data);
  }
  // 期货发起银行资金转期货通知
  onRtnFromBankToFutureByFuture(data) {
    this.logger && this.logger.info('OnRtnFromBankToFutureByFuture: %j', data);
  }
  // 期货发起期货资金转银行通知
  onRtnFromFutureToBankByFuture(data) {
    this.logger && this.logger.info('OnRtnFromFutureToBankByFuture: %j', data);
  }
  // 系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
  onRtnRepealFromBankToFutureByFutureManual(data) {
    this.logger && this.logger.info('OnRtnRepealFromBankToFutureByFutureManual: %j', data);
  }
  // 系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
  onRtnRepealFromFutureToBankByFutureManual(data) {
    this.logger && this.logger.info('OnRtnRepealFromFutureToBankByFutureManual: %j', data);
  }
  // 期货发起查询银行余额通知
  onRtnQueryBankBalanceByFuture(data) {
    this.logger && this.logger.info('OnRtnQueryBankBalanceByFuture: %j', data);
  }
  // 期货发起银行资金转期货错误回报
  onErrRtnBankToFutureByFuture(data, rsp) {
    this.logger && this.logger.info('OnErrRtnBankToFutureByFuture: %j, %j', data, rsp);
  }
  // 期货发起期货资金转银行错误回报
  onErrRtnFutureToBankByFuture(data, rsp) {
    this.logger && this.logger.info('OnErrRtnFutureToBankByFuture: %j, %',data, rsp);
  }
  // 系统运行时期货端手工发起冲正银行转期货错误回报
  onErrRtnRepealBankToFutureByFutureManual(data, rsp) {
    this.logger && this.logger.info('OnErrRtnRepealBankToFutureByFutureManual: %j, %j', data, rsp);
  }
  // 系统运行时期货端手工发起冲正期货转银行错误回报
  onErrRtnRepealFutureToBankByFutureManual(data, rsp) {
    this.logger && this.logger.info('OnErrRtnRepealFutureToBankByFutureManual: %j, %j', data, rsp);
  }
  // 期货发起查询银行余额错误回报
  onErrRtnQueryBankBalanceByFuture(data, rsp) {
    this.logger && this.logger.info('OnErrRtnQueryBankBalanceByFuture: %j, %j', data, rsp);
  }
  // 期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
  onRtnRepealFromBankToFutureByFuture(data) {
    this.logger && this.logger.info('OnRtnRepealFromBankToFutureByFuture: %j', data);
  }
  // 期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
  onRtnRepealFromFutureToBankByFuture(data) {
    this.logger && this.logger.info('OnRtnRepealFromFutureToBankByFuture: %j', data);
  }
  // 期货发起查询银行余额应答
  onRspQueryBankAccountMoneyByFuture(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQueryBankAccountMoneyByFuture: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }
  // 银行发起银期开户通知
  onRtnOpenAccountByBank(data) {
    this.logger && this.logger.info('OnRtnOpenAccountByBank: %j', data);
  }
  // 银行发起银期销户通知
  onRtnCancelAccountByBank(data) {
    this.logger && this.logger.info('OnRtnCancelAccountByBank: %j', data);
  }
  // 银行发起变更银行账号通知
  onRtnChangeAccountByBank(data) {
    this.logger && this.logger.info('OnRtnChangeAccountByBank: %j', data);
  }

  // 查询用户当前支持的认证模式的回复
  onRspUserAuthMethod(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspUserAuthMethod: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  // 获取图形验证码请求的回复
  onRspGenUserCaptcha(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspGenUserCaptcha: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  // 获取短信验证码请求的回复
  onRspGenUserText(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspGenUserText: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  // 请求查询二级代理商信息响应
  onRspQrySecAgentTradeInfo(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQrySecAgentTradeInfo: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  // 请求查询资金账户响应
  onRspQrySecAgentTradingAccount(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQrySecAgentTradingAccount: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

  // 请求查询二级代理商资金校验模式响应
  onRspQrySecAgentCheckMode(data, rsp, nRequestID, bIsLast) {
    this.logger && this.logger.info('OnRspQrySecAgentCheckMode: %j, %j, %s, %s', data, rsp, nRequestID, bIsLast);
  }

}

module.exports = Trade;
