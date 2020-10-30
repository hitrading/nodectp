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
适配看穿式监管库, 适配的库版本: 6.3.15_20190220、v6.3.15_P2_mdapi_se_20190403 (实现了ctp所有的接口, 其中包含客户端认证及组播接口)

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

