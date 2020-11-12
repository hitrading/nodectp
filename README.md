# xyctp_test
此分支为了做穿透式API测试而存在
向期货公司递交程序化软件认证申请表之后，需使用该分支代码进行穿透式API测试，测试通过后期货公司会下发生产系统的认证码，然后方可用于实盘

# warning
目前仅支持linux64和win64平台(win32平台未测试，理论上支持)

支持的nodejs版本: 8.x.x, 如: 8.16.1  ***(8以上版本不被支持)***

# compile
windows平台需要安装编译工具：`npm install --global --production windows-build-tools`

执行脚本：
```
npm run rebuild 或 yarn rebuild
```

# execute
run example
```
node ./example/ctpapp.js
```

# Example
请参看[example](https://github.com/iamweilee/nodectp/tree/develop/example)

# version
适配看穿式监管库, 适配的库版本: 6.3.19_T1 (实现了ctp所有的接口, 其中包含客户端认证及组播接口)

### 可能遇到的报错问题
执行 `yarn build` 命令时可能会遇到node.lib文件损坏的情况, 此时可去官网下载node.lib文件替换, 下载地址：[https://nodejs.org/dist/latest-v8.x/win-x64/node.lib]

### API

```
  WrapTd {}:
      - getApiVersion
      - init
      - release
      - dispose
      - createFtdcTraderApi
      - getTradingDay
      - registerFront
      - registerNameServer
      - registerFensUserInfo
      - subscribePrivateTopic
      - subscribePublicTopic
      - reqAuthenticate
      - reqUserLogin
      - reqUserLogout
      - reqUserPasswordUpdate
      - reqTradingAccountPasswordUpdate
      - reqOrderInsert
      - reqParkedOrderInsert
      - reqParkedOrderAction
      - reqOrderAction
      - reqQueryMaxOrderVolume
      - reqSettlementInfoConfirm
      - reqRemoveParkedOrder
      - reqRemoveParkedOrderAction
      - reqExecOrderInsert
      - reqExecOrderAction
      - reqForQuoteInsert
      - reqQuoteInsert
      - reqQuoteAction
      - reqBatchOrderAction
      - reqCombActionInsert
      - reqQryOrder
      - reqQryTrade
      - reqQryInvestorPosition
      - reqQryTradingAccount
      - reqQryInvestor
      - reqQryTradingCode
      - reqQryInstrumentMarginRate
      - reqQryInstrumentCommissionRate
      - reqQryExchange
      - reqQryProduct
      - reqQryInstrument
      - reqQryDepthMarketData
      - reqQrySettlementInfo
      - reqQryTransferBank
      - reqQryInvestorPositionDetail
      - reqQryNotice
      - reqQrySettlementInfoConfirm
      - reqQryCFMMCTradingAccountKey
      - reqQryEWarrantOffset
      - reqQryInvestorProductGroupMargin
      - reqQryExchangeMarginRate
      - reqQryExchangeMarginRateAdjust
      - reqQryExchangeRate
      - reqQrySecAgentACIDMap
      - reqQryProductExchRate
      - reqQryProductGroup
      - reqQryMMInstrumentCommissionRate
      - reqQryMMOptionInstrCommRate
      - reqQryInstrumentOrderCommRate
      - reqQryOptionInstrTradeCost
      - reqQryOptionInstrCommRate
      - reqQryExecOrder
      - reqQryForQuote
      - reqQryQuote
      - reqQryCombInstrumentGuard
      - reqQryCombAction
      - reqQryTransferSerial
      - reqQryAccountregister
      - reqQryContractBank
      - reqQryParkedOrder
      - reqQryParkedOrderAction
      - reqQryTradingNotice
      - reqQryBrokerTradingParams
      - reqQryBrokerTradingAlgos
      - reqQueryCFMMCTradingAccountToken
      - reqFromBankToFutureByFuture
      - reqFromFutureToBankByFuture
      - reqQueryBankAccountMoneyByFuture
      - reqQryInvestorPositionCombineDetail
      - registerUserSystemInfo
      - submitUserSystemInfo
      - reqUserAuthMethod
      - reqGenUserCaptcha
      - reqGenUserText
      - reqUserLoginWithCaptcha
      - reqUserLoginWithText
      - reqUserLoginWithOTP
      - reqQrySecAgentTradeInfo
      - reqQrySecAgentTradingAccount
      - reqQrySecAgentCheckMode
      - on
    
    callback events:
      - FrontConnected
      - FrontDisconnected
      - HeartBeatWarning
      - RspAuthenticate
      - RspUserLogin
      - RspUserLogout
      - RspUserPasswordUpdate
      - RspTradingAccountPasswordUpdate
      - RspOrderInsert
      - RspParkedOrderInsert
      - RspParkedOrderAction
      - RspOrderAction
      - RspQueryMaxOrderVolume
      - RspSettlementInfoConfirm
      - RspRemoveParkedOrder
      - RspRemoveParkedOrderAction
      - RspExecOrderInsert
      - RspExecOrderAction
      - RspForQuoteInsert
      - RspQuoteInsert
      - RspQuoteAction
      - RspBatchOrderAction
      - RspCombActionInsert
      - RspQryOrder
      - RspQryTrade
      - RspQryInvestorPosition
      - RspQryTradingAccount
      - RspQryInvestor
      - RspQryTradingCode
      - RspQryInstrumentMarginRate
      - RspQryInstrumentCommissionRate
      - RspQryExchange
      - RspQryProduct
      - RspQryInstrument
      - RspQryDepthMarketData
      - RspQrySettlementInfo
      - RspQryTransferBank
      - RspQryInvestorPositionDetail
      - RspQryNotice
      - RspQrySettlementInfoConfirm
      - RspQryInvestorPositionCombineDetail
      - RspQryCFMMCTradingAccountKey
      - RspQryEWarrantOffset
      - RspQryInvestorProductGroupMargin
      - RspQryExchangeMarginRate
      - RspQryExchangeMarginRateAdjust
      - RspQryExchangeRate
      - RspQrySecAgentACIDMap
      - RspQryProductExchRate
      - RspQryProductGroup
      - RspQryMMInstrumentCommissionRate
      - RspQryMMOptionInstrCommRate
      - RspQryInstrumentOrderCommRate
      - RspQryOptionInstrTradeCost
      - RspQryOptionInstrCommRate
      - RspQryExecOrder
      - RspQryForQuote
      - RspQryQuote
      - RspQryCombInstrumentGuard
      - RspQryCombAction
      - RspQryTransferSerial
      - RspQryAccountregister
      - RspError
      - RtnOrder
      - RtnTrade
      - ErrRtnOrderInsert
      - ErrRtnOrderAction
      - RtnInstrumentStatus
      - RtnBulletin
      - RtnTradingNotice
      - RtnErrorConditionalOrder
      - RtnExecOrder
      - ErrRtnExecOrderInsert
      - ErrRtnExecOrderAction
      - ErrRtnForQuoteInsert
      - RtnQuote
      - ErrRtnQuoteInsert
      - ErrRtnQuoteAction
      - RtnForQuoteRsp
      - RtnCFMMCTradingAccountToken
      - ErrRtnBatchOrderAction
      - RtnCombAction
      - ErrRtnCombActionInsert
      - RspQryContractBank
      - RspQryParkedOrder
      - RspQryParkedOrderAction
      - RspQryTradingNotice
      - RspQryBrokerTradingParams
      - RspQryBrokerTradingAlgos
      - RspQueryCFMMCTradingAccountToken
      - RtnFromBankToFutureByBank
      - RtnFromFutureToBankByBank
      - RtnRepealFromBankToFutureByBank
      - RtnRepealFromFutureToBankByBank
      - RtnFromBankToFutureByFuture
      - RtnFromFutureToBankByFuture
      - RtnRepealFromBankToFutureByFutureManual
      - RtnRepealFromFutureToBankByFutureManual
      - RtnQueryBankBalanceByFuture
      - ErrRtnBankToFutureByFuture
      - ErrRtnFutureToBankByFuture
      - ErrRtnRepealBankToFutureByFutureManual
      - ErrRtnRepealFutureToBankByFutureManual
      - ErrRtnQueryBankBalanceByFuture
      - RtnRepealFromBankToFutureByFuture
      - RtnRepealFromFutureToBankByFuture
      - RspFromBankToFutureByFuture
      - RspFromFutureToBankByFuture
      - RspQueryBankAccountMoneyByFuture
      - RtnOpenAccountByBank
      - RtnCancelAccountByBank
      - RtnChangeAccountByBank
      // 穿透式监管新增响应事件
      - RspUserAuthMethod
      - RspGenUserCaptcha
      - RspGenUserText
      - RspQrySecAgentTradeInfo
      - RspQrySecAgentTradingAccount
      - RspQrySecAgentCheckMode

  WrapMd {}:
      - init
      - release
      - dispose
      - createFtdcMdApi
      - getApiVersion
      - getTradingDay
      - registerFront
      - registerNameServer
      - registerFensUserInfo
      - reqUserLogin
      - reqUserLogout
      - subscribeMarketData
      - unSubscribeMarketData
      - subscribeForQuoteRsp
      - unSubscribeForQuoteRsp
      - reqQryMulticastInstrument
      - on
  
    callback events:
      - FrontConnected
      - FrontDisconnected
      - HeartBeatWarning
      - RspUserLogin
      - RspUserLogout
      - RspQryMulticastInstrument
      - RspError
      - RspSubMarketData
      - RspUnSubMarketData
      - RspSubForQuoteRsp
      - RspUnSubForQuoteRsp
      - RtnDepthMarketData
      - RtnForQuoteRsp
```

### Rsp params
**trade**
```
  onFrontConnected() {

  }

  onFrontDisconnected(nReason) {

  }

  onRspAuthenticate(data, rsp, nReqId, bIsLast) {

  }

  onRspUserLogin(data, rsp, nReqId, bIsLast) {

  }

  onRspUserLogout(data, rsp, nReqId, bIsLast) {

  }
  // 报单通知
  onRtnOrder(data) {

  }
  // 成交通知
  onRtnTrade(data) {

  }
  // 报单录入请求响应
  onRspOrderInsert(data, rsp, nReqId, bIsLast) {

  }
  // 报单操作请求响应
  onRspOrderAction(data, rsp, nReqId, bIsLast) {

  }
  // 预埋单录入请求响应
  onRspParkedOrderInsert(data, rsp, nReqId, bIsLast) {

  }
  // 预埋撤单录入请求响应
  onRspParkedOrderAction(data, rsp, nReqId, bIsLast) {

  }
  // 删除预埋单响应
  onRspRemoveParkedOrder(data, rsp, nReqId, bIsLast) {

  }
  // 删除预埋撤单响应
  onRspRemoveParkedOrderAction(data, rsp, nReqId, bIsLast) {

  }
  // 执行宣告录入请求响应
  onRspExecOrderInsert(data, rsp, nReqId, bIsLast) {

  }
  // 执行宣告操作请求响应
  onRspExecOrderAction(data, rsp, nReqId, bIsLast) {

  }
  // 询价录入请求响应
  onRspForQuoteInsert(data, rsp, nReqId, bIsLast) {

  }
  // 报价录入请求响应
  onRspQuoteInsert(data, rsp, nReqId, bIsLast) {

  }
  // 报价操作请求响应
  onRspQuoteAction(data, rsp, nReqId, bIsLast) {

  }
  // 批量报单操作请求响应
  onRspBatchOrderAction(data, rsp, nReqId, bIsLast) {

  }
  // 申请组合录入请求响应
  onRspCombActionInsert(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询报单响应
  onRspQryOrder(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询成交响应
  onRspQryTrade(data, rsp, nReqId, bIsLast) {

  }
  // 查询最大报单数量响应
  onRspQueryMaxOrderVolume(data, rsp, nReqId, bIsLast) {

  }
  // 投资者结算结果确认响应
  onRspSettlementInfoConfirm(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询投资者持仓响应
  onRspQryInvestorPosition(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询签约银行响应
  onRspQryContractBank(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询资金账户响应
  onRspQryTradingAccount(data, rsp, nReqId, bIsLast) {

  }
  // 期货发起期货资金转银行应答
  onRspFromFutureToBankByFuture(data, rsp, nReqId, bIsLast) {

  }
  // 期货发起银行资金转期货应答
  onRspFromBankToFutureByFuture(data, rsp, nReqId, bIsLast) {

  }
  // 用户口令更新请求响应
  onRspUserPasswordUpdate(data, rsp, nReqId, bIsLast) {

  }
  // 资金账户口令更新请求响应
  onRspTradingAccountPasswordUpdate(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询投资者响应
  onRspQryInvestor(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询交易编码响应
  onRspQryTradingCode(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询合约保证金率响应
  onRspQryInstrumentMarginRate(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询合约手续费率响应
  onRspQryInstrumentCommissionRate(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询交易所响应
  onRspQryExchange(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询产品响应
  onRspQryProduct(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询合约响应
  onRspQryInstrument(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询行情响应
  onRspQryDepthMarketData(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询投资者结算结果响应
  onRspQrySettlementInfo(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询转帐银行响应
  onRspQryTransferBank(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询投资者持仓明细响应
  onRspQryInvestorPositionDetail(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询客户通知响应
  onRspQryNotice(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询结算信息确认响应
  onRspQrySettlementInfoConfirm(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询投资者持仓组合明细响应
  onRspQryInvestorPositionCombineDetail(data, rsp, nReqId, bIsLast) {

  }
  // 查询保证金监管系统经纪公司资金账户密钥响应
  onRspQryCFMMCTradingAccountKey(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询仓单折抵信息响应
  onRspQryEWarrantOffset(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询投资者品种/跨品种保证金响应
  onRspQryInvestorProductGroupMargin(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询交易所保证金率响应
  onRspQryExchangeMarginRate(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询交易所调整保证金率响应
  onRspQryExchangeMarginRateAdjust(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询汇率响应
  onRspQryExchangeRate(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询二级代理操作员银期权限响应
  onRspQrySecAgentACIDMap(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询产品报价汇率响应
  onRspQryProductExchRate(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询产品组响应
  onRspQryProductGroup(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询做市商合约手续费率响应
  onRspQryMMInstrumentCommissionRate(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询做市商期权合约手续费响应
  onRspQryMMOptionInstrCommRate(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询报单手续费响应
  onRspQryInstrumentOrderCommRate(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询期权交易成本响应
  onRspQryOptionInstrTradeCost(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询期权合约手续费响应
  onRspQryOptionInstrCommRate(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询执行宣告响应
  onRspQryExecOrder(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询询价响应
  onRspQryForQuote(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询报价响应
  onRspQryQuote(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询组合合约安全系数响应
  onRspQryCombInstrumentGuard(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询申请组合响应
  onRspQryCombAction(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询转帐流水响应
  onRspQryTransferSerial(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询银期签约关系响应
  onRspQryAccountregister(data, rsp, nReqId, bIsLast) {

  }
  // 错误应答
  onRspError(rsp, nReqId, bIsLast) {

  }
  // 报单录入错误回报
  onErrRtnOrderInsert(data, rsp) {

  }
  // 报单操作错误回报
  onErrRtnOrderAction(data, rsp) {

  }
  // 合约交易状态通知
  onRtnInstrumentStatus(data) {

  }
  // 交易所公告通知
  onRtnBulletin(data) {

  }
  // 交易通知
  onRtnTradingNotice(data) {

  }
  // 提示条件单校验错误
  onRtnErrorConditionalOrder(data) {

  }
  // 执行宣告通知
  onRtnExecOrder(data) {

  }
  // 执行宣告录入错误回报
  onErrRtnExecOrderInsert(data, rsp) {

  }
  // 执行宣告操作错误回报
  onErrRtnExecOrderAction(data, rsp) {

  }
  // 询价录入错误回报
  onErrRtnForQuoteInsert(data, rsp) {

  }
  // 报价通知
  onRtnQuote(data) {

  }
  // 报价录入错误回报
  onErrRtnQuoteInsert(data, rsp) {

  }
  // 报价操作错误回报
  onErrRtnQuoteAction(data, rsp) {

  }
  // 询价通知
  onRtnForQuoteRsp(data) {

  }
  // 保证金监控中心用户令牌
  onRtnCFMMCTradingAccountToken(data) {

  }
  // 批量报单操作错误回报
  onErrRtnBatchOrderAction(data, rsp) {

  }
  // 申请组合通知
  onRtnCombAction(data) {

  }
  // 申请组合录入错误回报
  onErrRtnCombActionInsert(data, rsp) {

  }
  // 请求查询预埋撤单响应
  onRspQryParkedOrder(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询交易通知响应
  onRspQryTradingNotice(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询经纪公司交易参数响应
  onRspQryBrokerTradingParams(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询经纪公司交易算法响应
  onRspQryBrokerTradingAlgos(data, rsp, nReqId, bIsLast) {

  }
  // 请求查询监控中心用户令牌响应
  onRspQueryCFMMCTradingAccountToken(data, rsp, nReqId, bIsLast) {

  }
  // 银行发起银行资金转期货通知
  onRtnFromBankToFutureByBank(data) {

  }
  // 银行发起期货资金转银行通知
  onRtnFromFutureToBankByBank(data) {

  }
  // 银行发起冲正银行转期货通知
  onRtnRepealFromBankToFutureByBank(data) {

  }
  // 银行发起冲正期货转银行通知
  onRtnRepealFromFutureToBankByBank(data) {

  }
  // 期货发起银行资金转期货通知
  onRtnFromBankToFutureByFuture(data) {

  }
  // 期货发起期货资金转银行通知
  onRtnFromFutureToBankByFuture(data) {

  }
  // 系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
  onRtnRepealFromBankToFutureByFutureManual(data) {

  }
  // 系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
  onRtnRepealFromFutureToBankByFutureManual(data) {

  }
  // 期货发起查询银行余额通知
  onRtnQueryBankBalanceByFuture(data) {

  }
  // 期货发起银行资金转期货错误回报
  onErrRtnBankToFutureByFuture(data, rsp) {

  }
  // 期货发起期货资金转银行错误回报
  onErrRtnFutureToBankByFuture(data, rsp) {

  }
  // 系统运行时期货端手工发起冲正银行转期货错误回报
  onErrRtnRepealBankToFutureByFutureManual(data, rsp) {

  }
  // 系统运行时期货端手工发起冲正期货转银行错误回报
  onErrRtnRepealFutureToBankByFutureManual(data, rsp) {

  }
  // 期货发起查询银行余额错误回报
  onErrRtnQueryBankBalanceByFuture(data, rsp) {

  }
  // 期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
  onRtnRepealFromBankToFutureByFuture(data) {

  }
  // 期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
  onRtnRepealFromFutureToBankByFuture(data) {

  }
  // 期货发起查询银行余额应答
  onRspQueryBankAccountMoneyByFuture(data, rsp, nReqId, bIsLast) {

  }
  // 银行发起银期开户通知
  onRtnOpenAccountByBank(data) {

  }
  // 银行发起银期销户通知
  onRtnCancelAccountByBank(data) {

  }
  // 银行发起变更银行账号通知
  onRtnChangeAccountByBank(data) {

  }

  // 查询用户当前支持的认证模式的回复
  onRspUserAuthMethod(data, rsp, nReqId, bIsLast) {

  }

  // 获取图形验证码请求的回复
  onRspGenUserCaptcha(data, rsp, nReqId, bIsLast) {

  }

  // 获取短信验证码请求的回复
  onRspGenUserText(data, rsp, nReqId, bIsLast) {

  }

  // 请求查询二级代理商信息响应
  onRspQrySecAgentTradeInfo(data, rsp, nReqId, bIsLast) {

  }

  // 请求查询资金账户响应
  onRspQrySecAgentTradingAccount(data, rsp, nReqId, bIsLast) {

  }

  // 请求查询二级代理商资金校验模式响应
  onRspQrySecAgentCheckMode(data, rsp, nReqId, bIsLast) {

  }
```

**market**
```
  onFrontConnected() {

  }

  onFrontDisconnected(nReason) {

  }

  onRspUserLogin(data, rsp, nReqId, bIsLast) {

  }

  onRspUserLogout(data, rsp, nReqId, bIsLast) {

  }

  onRspError(rsp, nReqId, bIsLast) {

  }

  onRspSubMarketData(data, rsp, nReqId, bIsLast) {

  }

  onRspUnSubMarketData(data, rsp, nReqId, bIsLast) {

  }

  onRspSubForQuoteRsp(data, rsp, nReqId, bIsLast) {

  }

  onRspUnSubForQuoteRsp(data, rsp, nReqId, bIsLast) {

  }

  onRtnForQuoteRsp(data) {

  }

  onRtnDepthMarketData(data) {

  }

  onRspQryMulticastInstrument(data, rsp, nReqId, bIsLast) {

  }
```
